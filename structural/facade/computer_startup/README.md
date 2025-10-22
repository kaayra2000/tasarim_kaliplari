# computer_startup

Bilgisayarın başlatılmasını tek bir arayüz üzerinden kolaylaştıran Facade örneği.

# Derleyip Çalıştırma

Bu klasördeyken:

```bash
g++ -std=c++17 code.cpp -o app
./app
```

# Beklenen Çıktı

```text

=== Bilgisayar başlatılıyor... ===
BIOS: POST (Power-On Self Test) yapılıyor
CPU: İşlemci donduruldu
Memory: Bellek başlatılıyor
HardDrive: Disk başlatılıyor
BIOS: Bootloader yükleniyor
Memory: 0 adresine 'BOOTLOADER' yükleniyor
CPU: 0 adresine atlanıyor
HardDrive: 100 sektöründen 1024 byte okunuyor
Memory: 4096 adresine 'BOOT_DATA' yükleniyor
OS: Kernel yükleniyor
CPU: Komutlar çalıştırılıyor
OS: Sistem servisleri başlatılıyor
OS: Masaüstü görüntüleniyor
=== Sistem hazır! ===


=== Bilgisayar yeniden başlatılıyor... ===
Servisler durduruluyor...
Sistem kapatılıyor...

=== Bilgisayar başlatılıyor... ===
BIOS: POST (Power-On Self Test) yapılıyor
CPU: İşlemci donduruldu
Memory: Bellek başlatılıyor
HardDrive: Disk başlatılıyor
BIOS: Bootloader yükleniyor
Memory: 0 adresine 'BOOTLOADER' yükleniyor
CPU: 0 adresine atlanıyor
HardDrive: 100 sektöründen 1024 byte okunuyor
Memory: 4096 adresine 'BOOT_DATA' yükleniyor
OS: Kernel yükleniyor
CPU: Komutlar çalıştırılıyor
OS: Sistem servisleri başlatılıyor
OS: Masaüstü görüntüleniyor
=== Sistem hazır! ===
```