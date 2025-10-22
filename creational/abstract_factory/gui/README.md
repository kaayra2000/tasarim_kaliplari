# abstract_factory/gui

Platforma göre (windows/mac/linux) buton/checkbox ailesi oluşturan Abstract Factory örneği.

## Derleme ve çalıştırma (Ubuntu)

Bu klasördeyken:

```bash
g++ -std=c++17 code.cpp -o app
# Örnek giriş: linux
printf "linux\n" | ./app
```

Örnek çıktı (linux seçildiğinde):

```text
Platform seçin (windows/mac/linux): 
=== Arayüz Çiziliyor ===
Linux stili buton çiziliyor
Linux stili checkbox çiziliyor

=== Kullanıcı Etkileşimi ===
Linux butonu tıklandı!
Linux checkbox durumu değişti
```