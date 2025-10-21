#include <iostream>
#include <memory>
#include <string>

// Decorator kalıbı: İçecek ve süslemeler (espresso + mocha + süt ...)

// Bileşen arayüzü
class Beverage {
public:
    virtual ~Beverage() = default;
    virtual std::string description() const = 0;
    virtual double cost() const = 0;
};

// Somut bileşenler
class Espresso : public Beverage {
public:
    std::string description() const override { return "Espresso"; }
    double cost() const override { return 2.50; }
};

class HouseBlend : public Beverage {
public:
    std::string description() const override { return "House Blend Coffee"; }
    double cost() const override { return 1.80; }
};

// Decorator temel sınıfı (Beverage arayüzünü uygular ve bir Beverage tutar)
class CondimentDecorator : public Beverage {
protected:
    std::unique_ptr<Beverage> beverage;

public:
    explicit CondimentDecorator(std::unique_ptr<Beverage> bev)
        : beverage(std::move(bev)) {}
};

class Milk : public CondimentDecorator {
public:
    explicit Milk(std::unique_ptr<Beverage> bev)
        : CondimentDecorator(std::move(bev)) {}

    std::string description() const override {
        return beverage->description() + ", Milk";
    }

    double cost() const override {
        return beverage->cost() + 0.30; // süt ücreti
    }
};

class Mocha : public CondimentDecorator {
public:
    explicit Mocha(std::unique_ptr<Beverage> bev)
        : CondimentDecorator(std::move(bev)) {}

    std::string description() const override {
        return beverage->description() + ", Mocha";
    }

    double cost() const override {
        return beverage->cost() + 0.50; // mocha ücreti
    }
};

class Whip : public CondimentDecorator {
public:
    explicit Whip(std::unique_ptr<Beverage> bev)
        : CondimentDecorator(std::move(bev)) {}

    std::string description() const override {
        return beverage->description() + ", Whip";
    }

    double cost() const override {
        return beverage->cost() + 0.40; // krema ücreti
    }
};

int main() {
    std::cout << "=== Decorator: Coffee Shop ===\n";

    // Basit espresso
    std::unique_ptr<Beverage> order1 = std::make_unique<Espresso>();
    std::cout << order1->description() << " -> $" << order1->cost() << "\n";

    std::cout << "\n";

    // Espresso + Mocha + Süt
    std::unique_ptr<Beverage> order2 = std::make_unique<Espresso>();
    order2 = std::make_unique<Mocha>(std::move(order2));
    order2 = std::make_unique<Milk>(std::move(order2));
    std::cout << order2->description() << " -> $" << order2->cost() << "\n";

    std::cout << "\n";

    // House Blend + Mocha + Mocha + Whip
    std::unique_ptr<Beverage> order3 = std::make_unique<HouseBlend>();
    order3 = std::make_unique<Mocha>(std::move(order3));
    order3 = std::make_unique<Mocha>(std::move(order3));
    order3 = std::make_unique<Whip>(std::move(order3));
    std::cout << order3->description() << " -> $" << order3->cost() << "\n";

    return 0;
}
