#include <iostream>
#include <string>
using namespace std;

// Ürün arayüzü
class Shape {
public:
    virtual void draw() = 0;
    virtual ~Shape() {}
};

// Somut ürünler
class Circle : public Shape {
public:
    void draw() override {
        cout << "Daire çiziliyor" << endl;
    }
};

class Rectangle : public Shape {
public:
    void draw() override {
        cout << "Dikdörtgen çiziliyor" << endl;
    }
};

class Triangle : public Shape {
public:
    void draw() override {
        cout << "Üçgen çiziliyor" << endl;
    }
};

// Factory sınıfı
class ShapeFactory {
public:
    static Shape* createShape(const string& type) {
        if (type == "circle") {
            return new Circle();
        }
        else if (type == "rectangle") {
            return new Rectangle();
        }
        else if (type == "triangle") {
            return new Triangle();
        }
        return nullptr;
    }
};

// Kullanım
int main() {
    Shape* shape1 = ShapeFactory::createShape("circle");
    shape1->draw();
    
    Shape* shape2 = ShapeFactory::createShape("rectangle");
    shape2->draw();
    
    Shape* shape3 = ShapeFactory::createShape("triangle");
    shape3->draw();
    
    // Bellek temizliği
    delete shape1;
    delete shape2;
    delete shape3;
    
    return 0;
}
