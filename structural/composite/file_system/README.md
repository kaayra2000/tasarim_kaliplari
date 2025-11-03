# file_system

`Node` arayüzü üzerinden dosyaları ve dizinleri aynı şekilde ele alan minimal bir Composite örneği. `Directory`, alt öğeleri (`File` veya `Directory`) bir araya getirir.

# Derleyip Çalıştırma

```bash
g++ -std=c++17 structural/composite/file_system/code.cpp -o file_system && ./file_system
```

# Beklenen Çıktı

```
Dir: root (total=452)
  File: notes.txt (12)
  Dir: docs (total=376)
    File: report.pdf (120)
    File: data.bin (256)
  File: picture.jpg (64)
Total size: 452 bytes
```