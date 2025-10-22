# singleton/thread_safe

thread-safe (çok iş parçacıklı güvenli) Singleton örneği.

## Derleme ve çalıştırma (Ubuntu)

Bu klasördeyken:

```bash
g++ -std=c++17 code.cpp -o app
./app
```

Beklenen çıktı:

```text
[SafeLogger] Merhaba güvenli dünya
Aynı mı? true
[SAFE-APP] Prefix değişti mi?
```