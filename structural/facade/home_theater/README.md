# facade/home_theater

Ev sinema sistemini tek bir arayüzle kontrol eden Facade örneği.

## Derleme ve çalıştırma (Ubuntu)

Bu klasördeyken:

```bash
g++ -std=c++17 code.cpp -o app
./app
```

Beklenen çıktı:

```text

=== Film izlemeye hazırlanılıyor... ===
Işıklar kısılıyor: %10
Projeksiyon perdesi indiriliyor
Projektör açılıyor...
Projektör: Geniş ekran modu (16:9)
Amplifikatör açılıyor...
Amplifikatör: Surround Sound modu aktif
Amplifikatör ses seviyesi: 15
DVD Player açılıyor...
DVD Player: 'The Matrix' oynatılıyor
=== Keyfini çıkarın! ===


=== Film sistemi kapatılıyor... ===
DVD Player durduruluyor
DVD Player kapatılıyor
Amplifikatör kapatılıyor
Projektör kapatılıyor
Projeksiyon perdesi kaldırılıyor
Işıklar açılıyor
=== Sistem kapatıldı ===
```