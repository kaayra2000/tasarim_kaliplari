# graphic_editor

Şekillerin (Circle, Rectangle) ve grupların (Group) aynı `Graphic` arayüzünü paylaştığı minimal bir Composite örneği. İstemci, tekil şekilleri ve grupları aynı şekilde ele alır.

# Derleyip Çalıştırma

```bash
g++ -std=c++17 structural/composite/graphic_editor/code.cpp -o graphic_editor && ./graphic_editor
```

# Beklenen Çıktı

```
Group: Scene
  Circle(sun, r=5)
  Rectangle(ground, w=20, h=3)
  Group: Layer1
    Circle(ball, r=2)
    Rectangle(box, w=2, h=2)
```