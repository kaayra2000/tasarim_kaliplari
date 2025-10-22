# decorator/secure_io

Bellekteki veri kaynağına sıkıştırma ve/veya şifreleme katmanları ekleyen Decorator örneği.

## Derleme ve çalıştırma (Ubuntu)

Bu klasördeyken:

```bash
g++ -std=c++17 code.cpp -o app
./app
```

Beklenen çıktı:

```text
=== Decorator: Secure I/O ===
CompressionDecorator: 21 -> 9 bayt
MemoryDataSource: Veri yazıldı (9 bayt)
Okunan (compress->decompress): MemoryDataSource: Veri okunuyor
CompressionDecorator: açılıyor (9 bayt)
aaaaabbbbccccccccccdd

EncryptionDecorator: şifreleniyor
MemoryDataSource: Veri yazıldı (16 bayt)
Okunan (encrypt->decrypt): MemoryDataSource: Veri okunuyor
EncryptionDecorator: çözülüyor
Sifreli veri ici

CompressionDecorator: 56 -> 30 bayt
EncryptionDecorator: şifreleniyor
MemoryDataSource: Veri yazıldı (30 bayt)
MemoryDataSource: Veri okunuyor
EncryptionDecorator: çözülüyor
CompressionDecorator: açılıyor (30 bayt)
Orijinal == Okunan ? EVET
MemoryDataSource: Veri yazıldı (8 bayt)
Doğrudan okunan: MemoryDataSource: Veri okunuyor
raw-data
```