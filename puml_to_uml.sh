#!/usr/bin/env bash
# Kullanım:
#   ./puml_to_images.sh         # Bulunduğun dizinden itibaren
#   ./puml_to_images.sh /yol    # Verilen kök dizinden itibaren
ROOT="${1:-.}"

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

# Tüm .puml dosyalarını say
echo "🔍 .puml dosyaları aranıyor..."
total=$(find "$ROOT" -type f -name "*.puml" | wc -l)
echo "✅ Toplam $total adet .puml dosyası bulundu."
echo ""

# Dosyaları işle ve ilerlemeyi göster
count=0
find "$ROOT" -type f -name "*.puml" -print0 \
  | while IFS= read -r -d '' file; do
      ((count++))
      echo "[$count/$total] İşleniyor: $file"
      process_file "$file"
    done
