# legacy_audio

Modern cihazın (USB Type-C) eski analog kulaklık girişine (3.5mm) uyarlanması örneği.

# Derleyip Çalıştırma

Bu klasördeyken:

```bash
g++ -std=c++17 code.cpp -o app
./app
```

# Beklenen Çıktı

```text
=== Eski Sistem ===
StudioHeadphones: Sol=7.5db Sağ=7.4db analog sinyal çalınıyor

=== Modern Telefon ile Uyumluluk ===
UsbToJackAdapter: Dijital akış analog sinyale dönüştürülüyor
UsbTypeCPhone: 'analog-dreams.aac' dijital PCM akışı gönderiliyor
UsbToJackAdapter: Manuel analog değerler gönderiliyor
Adapter analog çıkış -> Sol=11.65 Sağ=11.65

=== Aynı Arayüz ===
UsbToJackAdapter: Manuel analog değerler gönderiliyor
Adapter analog çıkış -> Sol=6 Sağ=6
```