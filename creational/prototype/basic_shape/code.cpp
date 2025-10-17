#include <iostream>
#include <string>
#include <memory>

// Prototype soyut sınıfı
class Shape {
protected:
    std::string type;
    int x, y;
public:
    virtual ~Shape() {}
    virtual std::unique_ptr<Shape> clone() = 0;
    virtual void draw() = 0;
    
    void setPosition(int xPos, int yPos) {
        x = xPos;
        y = yPos;
    }
};

// Concrete Prototype 1
class Circle : public Shape {
private:
    int radius;
public:
    Circle(int r) : radius(r) {
        type = "Circle";
        x = 0;
        y = 0;
    }
    
    std::unique_ptr<Shape> clone() override {
        return std::make_unique<Circle>(*this);
    }
    
    void draw() override {
        std::cout << "Çiziliyor: " << type 
                  << " - Pozisyon: (" << x << "," << y << ")"
                  << " - Yarıçap: " << radius << std::endl;
    }
};

// Concrete Prototype 2
class Rectangle : public Shape {
private:
    int width, height;
public:
    Rectangle(int w, int h) : width(w), height(h) {
        type = "Rectangle";
        x = 0;
        y = 0;
    }
    
    std::unique_ptr<Shape> clone() override {
        return std::make_unique<Rectangle>(*this);
    }
    
    void draw() override {
        std::cout << "Çiziliyor: " << type 
                  << " - Pozisyon: (" << x << "," << y << ")"
                  << " - Boyut: " << width << "x" << height << std::endl;
    }
};

int main() {
    // Orijinal nesneler
    auto circle1 = std::make_unique<Circle>(10);
    circle1->setPosition(5, 5);
    
    // Klonlama
    auto circle2 = circle1->clone();
    circle2->setPosition(20, 20);
    
    circle1->draw();
    circle2->draw();
    
    return 0;
}
