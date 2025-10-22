# bridge/remote_device

Kumanda soyutlamasını TV ve Radyo cihazları üzerinde köprüleyen Bridge örneği.

## Derleme ve çalıştırma (Ubuntu)

Bu klasördeyken:

```bash
g++ -std=c++17 code.cpp -o app
./app
```

Beklenen çıktı:

```text
=== Köprü (Bridge): Kumanda <-> Cihaz ===
TV: Güç AÇIK
TV: ses -> 40
TV: kanal -> 2
TV: ses -> 0
TV: Güç KAPALI

Aynı kumanda SOYUTLAMASINI kullanarak cihazı Radyo'ya değiştiriyoruz...
Radyo: Güç AÇIK
Radyo: ses -> 30
Radyo: kanal -> 100
```