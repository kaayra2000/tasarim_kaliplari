# gui

Platforma göre (windows/mac/linux) buton/checkbox ailesi oluşturan Abstract Factory örneği.

# Derleyip Çalıştırma

Bu klasördeyken:

```bash
g++ -std=c++17 code.cpp -o app
# Örnek giriş: linux
printf "linux\n" | ./app
```

# Beklenen Çıktı

```text
Platform seçin (windows/mac/linux): 
=== Arayüz Çiziliyor ===
Linux stili buton çiziliyor
Linux stili checkbox çiziliyor

=== Kullanıcı Etkileşimi ===
Linux butonu tıklandı!
Linux checkbox durumu değişti
```