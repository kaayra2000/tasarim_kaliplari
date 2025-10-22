# coffee_shop

İçeceklere (espresso/house blend) dinamik olarak süsleyiciler (mocha/whip/süt) ekleyen Decorator örneği.

# Derleyip Çalıştırma

Bu klasördeyken:

```bash
g++ -std=c++17 code.cpp -o app
./app
```

# Beklenen Çıktı

```text
=== Decorator: Coffee Shop ===
Espresso -> $2.5

Espresso, Mocha, Milk -> $3.3

House Blend Coffee, Mocha, Mocha, Whip -> $3.2
```