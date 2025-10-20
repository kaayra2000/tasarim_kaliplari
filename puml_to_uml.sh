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
FILTER="${1:-.}"
ROOT="${2:-}"

# PlantUML var mı?
if ! command -v plantuml >/dev/null 2>&1; then
  echo "Hata: plantuml bulunamadı. Lütfen yükleyin (apt/brew vs.)." >&2
  exit 1
fi

process_file() {
  local puml="$1"
  local dir base tmp tmpbase

  dir="$(dirname "$puml")"
  base="$(basename "$puml" .puml)"

  # Aynı klasörde geçici .puml oluştur (başlıktaki ismi temizle)
  if ! tmp="$(mktemp -p "$dir" ".__tmp_${base}_XXXXXX.puml")"; then
    echo "mktemp hatası: $puml" >&2
    return
  fi

  # Dosyada @startuml varsa isim temizle; yoksa sarmala
  if grep -q '^@startuml' "$puml"; then
    # Dosyadaki tüm @startuml ... satırlarını sade '@startuml' yap
    sed 's/^@startuml.*/@startuml/' "$puml" > "$tmp"
  else
    { printf '@startuml\n'; cat "$puml"; printf '\n@enduml\n'; } > "$tmp"
  fi

  tmpbase="$(basename "$tmp" .puml)"

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
}

# Tüm .puml dosyalarını say (filtreye göre)
echo "🔍 .puml dosyaları aranıyor..."

if [[ -n "$FILTER" ]]; then
    echo "📌 Filtre aktif: '$FILTER' içeren yollar"
    total=$(find "$ROOT" -type f -name "*.puml" -path "*${FILTER}*" | wc -l)
else
    echo "📌 Filtre yok, tüm dosyalar işlenecek"
    total=$(find "$ROOT" -type f -name "*.puml" | wc -l)
fi

echo "✅ Toplam $total adet .puml dosyası bulundu."
echo ""

# Dosyaları işle ve ilerlemeyi göster
count=0

if [[ -n "$FILTER" ]]; then
    # Filtreli işleme
    find "$ROOT" -type f -name "*.puml" -path "*${FILTER}*" -print0 \
      | while IFS= read -r -d '' file; do
          ((count++))
          echo "[$count/$total] İşleniyor: $file"
          process_file "$file"
        done
else
    # Filtresiz işleme (orijinal hali)
    find "$ROOT" -type f -name "*.puml" -print0 \
      | while IFS= read -r -d '' file; do
          ((count++))
          echo "[$count/$total] İşleniyor: $file"
          process_file "$file"
        done
fi
