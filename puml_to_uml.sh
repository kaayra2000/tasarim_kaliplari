#!/usr/bin/env bash
# Kullanım:
#   ./puml_to_uml.sh         # Bulunduğun dizinden itibaren
#   ./puml_to_uml.sh <filtre>    # Filtreli (yolunda <filtre> geçen dosyalar)
#   ./puml_to_uml.sh <filtre> <kök_dizin> # Belirtilen kök dizinden itibaren
# Açıklama:
#   Belirtilen dizin ve alt dizinlerdeki tüm .puml dosyalarını bulur,
#   her dosya için PNG ve SVG çıktıları üretir.
#   Eğer dosyada @startuml yoksa, geçici olarak sarar.
#   İlerleme durumu ve hata mesajları gösterir.
FILTER="${1:-}"
ROOT="${2:-.}"

CURRENT_FILE=""
CURRENT_TMP=""
CURRENT_DIR=""
CURRENT_TMPBASE=""

remove_matches() {
  local pattern="$1"
  local match
  while IFS= read -r match; do
    rm -f "$match"
  done < <(compgen -G "$pattern" 2>/dev/null || true)
}

cleanup_outputs() {
  if [[ -z "$CURRENT_DIR" ]]; then
    return
  fi

  if [[ -n "$CURRENT_TMPBASE" ]]; then
    remove_matches "$CURRENT_DIR/$CURRENT_TMPBASE.png"
    remove_matches "$CURRENT_DIR/${CURRENT_TMPBASE}"_*.png
    remove_matches "$CURRENT_DIR/$CURRENT_TMPBASE.svg"
    remove_matches "$CURRENT_DIR/${CURRENT_TMPBASE}"_*.svg
  fi
}

cleanup_temp() {
  if [[ -n "$CURRENT_TMP" && -f "$CURRENT_TMP" ]]; then
    rm -f "$CURRENT_TMP"
    CURRENT_TMP=""
  fi

  cleanup_outputs
}

cleanup_on_exit() {
  cleanup_temp
}

handle_interrupt() {
  trap - INT TERM
  echo -e "\n🛑 Ctrl+C algılandı. İşlem sonlandırılıyor..."
  if [[ -n "$CURRENT_FILE" ]]; then
    echo "⏹️  Yarım kalan dosya: $CURRENT_FILE"
  fi
  cleanup_temp
  CURRENT_FILE=""
  CURRENT_DIR=""
  CURRENT_BASE=""
  CURRENT_TMPBASE=""
  exit 130
}

trap 'handle_interrupt' INT TERM
trap 'cleanup_on_exit' EXIT

ensure_root_exists() {
  if [[ ! -d "$ROOT" ]]; then
    echo "Hata: '$ROOT' geçerli bir dizin değil." >&2
    exit 1
  fi
}

# PlantUML var mı?
if ! command -v plantuml >/dev/null 2>&1; then
  echo "Hata: plantuml bulunamadı. Lütfen yükleyin (apt/brew vs.)." >&2
  exit 1
fi

find_puml_files() {
  find "$ROOT" -type f -name "*.puml" -print0 2>/dev/null
}

summarize_selection() {
  local total_all total_filtered

  echo "🔍 .puml dosyaları aranıyor..."

  if [[ -n "$FILTER" ]]; then
    echo "📌 Filtre aktif: '$FILTER' içeren yollar"
  else
    echo "📌 Filtre yok, tüm dosyalar işlenecek"
  fi

  total_all=${#ALL_PUML_FILES[@]}
  total_filtered=${#FILTERED_FILES[@]}

  if (( total_all == 0 )); then
    echo "⚠️  Hiç .puml dosyası bulunamadı." >&2
  fi

  if [[ -n "$FILTER" ]]; then
    echo "✅ Toplam $total_filtered / $total_all adet .puml dosyası filtreye uydu."
    if (( total_filtered == 0 )); then
      echo "⚠️  Filtre ile eşleşen dosya bulunamadı." >&2
    fi
  else
    echo "✅ Toplam $total_filtered adet .puml dosyası bulundu."
  fi

  echo
}

declare -a ALL_PUML_FILES=()
declare -a FILTERED_FILES=()

collect_puml_files() {
  # Tek seferde tüm .puml dosyalarını topla ve gerekiyorsa filtre uygula
  mapfile -d '' -t ALL_PUML_FILES < <(find_puml_files)

  FILTERED_FILES=()
  if [[ -n "$FILTER" ]]; then
    local file
    for file in "${ALL_PUML_FILES[@]}"; do
      [[ "$file" == *"$FILTER"* ]] && FILTERED_FILES+=("$file")
    done
  else
    FILTERED_FILES=("${ALL_PUML_FILES[@]}")
  fi
}

process_file() {
  local puml="$1"
  local dir base tmp tmpbase

  CURRENT_FILE="$puml"
  dir="$(dirname "$puml")"
  base="$(basename "$puml" .puml)"
  CURRENT_DIR="$dir"

  # Aynı klasörde geçici .puml oluştur (başlıktaki ismi temizle)
  if ! tmp="$(mktemp -p "$dir" ".__tmp_${base}_XXXXXX.puml")"; then
    echo "mktemp hatası: $puml" >&2
    return
  fi

  CURRENT_TMP="$tmp"

  # Dosyada @startuml varsa isim temizle; yoksa sarmala
  if grep -q '^@startuml' "$puml"; then
    # Dosyadaki tüm @startuml ... satırlarını sade '@startuml' yap
    sed 's/^@startuml.*/@startuml/' "$puml" > "$tmp"
  else
    { printf '@startuml\n'; cat "$puml"; printf '\n@enduml\n'; } > "$tmp"
  fi

  tmpbase="$(basename "$tmp" .puml)"
  CURRENT_TMPBASE="$tmpbase"

  # PNG üret
  if plantuml -tpng "$tmp" >/dev/null 2>&1; then
    echo "PNG üretildi: $tmp"
    # Tekli ya da çoklu çıktı (…_001 vb.) durumunu kapsayacak şekilde yeniden adlandır
    for out in "$dir/$tmpbase.png" "$dir/${tmpbase}"_*.png; do
      [ -e "$out" ] || continue
      mv -f "$out" "${out/$tmpbase/$base}"
    done
  else
    echo "PNG üretim hatası: $puml" >&2
  fi

  # SVG üret
  if plantuml -tsvg "$tmp" >/dev/null 2>&1; then
    # Tekli ya da çoklu çıktı (…_001 vb.) durumunu kapsayacak şekilde yeniden adlandır
    echo "SVG üretildi: $tmp"
    for out in "$dir/$tmpbase.svg" "$dir/${tmpbase}"_*.svg; do
      [ -e "$out" ] || continue
      mv -f "$out" "${out/$tmpbase/$base}"
    done
  else
    echo "SVG üretim hatası: $puml" >&2
  fi

  rm -f "$tmp"
  CURRENT_TMP=""
  CURRENT_FILE=""
  CURRENT_DIR=""
  CURRENT_TMPBASE=""
}

process_filtered_files() {
  local total=${#FILTERED_FILES[@]}
  local index=0

  if (( total == 0 )); then
    echo "⏭️  İşlenecek dosya yok."
    return
  fi

  local file
  for file in "${FILTERED_FILES[@]}"; do
    ((index++))
    echo "[$index/$total] İşleniyor: $file"
    process_file "$file"
  done
}

ensure_root_exists
collect_puml_files
summarize_selection
process_filtered_files
