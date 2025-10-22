#include <iostream>
#include <string>

// Gerçekleştirme (Implementation) hiyerarşisi
struct Color {
    virtual ~Color() = default;
    virtual const char* name() const = 0;
};

struct Red : Color { const char* name() const override { return "kırmızı"; } };
struct Blue : Color { const char* name() const override { return "mavi"; } };

// Soyutlama (Abstraction) hiyerarşisi
class Shape {
protected:
    const Color& color_;
public:
    explicit Shape(const Color& c) : color_(c) {}
    virtual ~Shape() = default;
    virtual void draw() const = 0;
};

class Circle : public Shape {
    int r_;
public:
    Circle(const Color& c, int r) : Shape(c), r_(r) {}
    void draw() const override {
        std::cout << color_.name() << " daire çiziliyor (r=" << r_ << ")\n";
    }
};

class Square : public Shape {
    int a_;
public:
    Square(const Color& c, int a) : Shape(c), a_(a) {}
    void draw() const override {
        std::cout << color_.name() << " kare çiziliyor (a=" << a_ << ")\n";
    }
};

int main() {
    std::cout << "=== Köprü (Bridge): Şekil <-> Renk ===\n";

    Red kirmizi;
    Blue mavi;

    Circle c1(kirmizi, 5);
    c1.draw();

    Square s1(mavi, 3);
    s1.draw();

    // Aynı şekil farklı renk gerçekleştirmesiyle
    Circle c2(mavi, 7);
    c2.draw();

    return 0;
}
