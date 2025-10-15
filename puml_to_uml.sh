# Aynı klasörde geçici bir .puml oluştur, @startuml satırındaki ismi kaldır
tmp="$(mktemp -p . tmpXXXXXX.puml)"
sed 's/^@startuml.*/@startuml/' diagram.puml > "$tmp"

# PNG ve SVG üret, sonra kesin isimlere taşı
plantuml -tpng "$tmp" -o . && mv "${tmp%.puml}.png" diagram.png
plantuml -tsvg "$tmp" -o . && mv "${tmp%.puml}.svg" diagram.svg

# Geçici dosyayı temizle
rm -f "$tmp"