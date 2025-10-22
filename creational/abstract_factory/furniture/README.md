# abstract_factory/furniture

Kısa, çalıştırılabilir Abstract Factory örneği (mobilya ailesi).

## Derleme ve çalıştırma (Ubuntu)

Bu klasördeyken:

```bash
g++ -std=c++17 code.cpp -o app
./app
```

Program etkileşimlidir. Örnek olarak Modern (1) seçildiğinde beklenen çıktı:

```text
Hangi tarz mobilya istersiniz?
1. Modern
2. Klasik
1

*** Modern Mobilya Seçildi ***

=== Oda Döşeniyor ===
Modern sandalyeye oturuyorsunuz - Şık ve rahat!
Modern masayı kullanıyorsunuz - Minimalist tasarım!
```