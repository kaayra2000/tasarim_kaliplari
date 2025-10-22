# builder/classic_computer

Klasik Builder (Director + Concrete Builder ayrımı) örneği. Director farklı inşa stratejileri uygular: full, minimal ve storage-optimized.

## Derleme ve çalıştırma (Ubuntu)

Bu klasördeyken:

```bash
g++ -std=c++17 code.cpp -o app
./app
```

## Beklenen çıktı

```text
=== Gaming (Full) ===
Computer Configuration:
CPU: Intel i9-13900K
RAM: 32GB DDR5
Storage: 2TB NVMe SSD
GPU: NVIDIA RTX 4090

=== Office (Minimal) ===
Computer Configuration:
CPU: Intel i5-12400
RAM: 16GB DDR4
Storage: 
GPU: 

=== Office (Storage-Optimized) ===
Computer Configuration:
CPU: Intel i5-12400
RAM: 16GB DDR4
Storage: 512GB SSD + 512GB SSD
GPU: 
```