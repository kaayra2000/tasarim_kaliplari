# bridge/shape_color

Şekil (daire/kare) soyutlamasını renk (kırmızı/mavi) uygulamalarıyla köprüleyen Bridge örneği.

## Derleme ve çalıştırma (Ubuntu)

Bu klasördeyken:

```bash
g++ -std=c++17 code.cpp -o app
./app
```

Beklenen çıktı:

```text
=== Köprü (Bridge): Şekil <-> Renk ===
kırmızı daire çiziliyor (r=5)
mavi kare çiziliyor (a=3)
mavi daire çiziliyor (r=7)
```