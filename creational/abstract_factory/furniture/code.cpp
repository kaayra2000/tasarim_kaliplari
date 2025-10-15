#include <iostream>
#include <memory>
#include <string>

// ========== Soyut Ürünler ==========

// Soyut Sandalye
class Chair {
public:
    virtual ~Chair() = default;
    virtual void sitOn() const = 0;
};

// Soyut Masa
class Table {
public:
    virtual ~Table() = default;
    virtual void use() const = 0;
};

// ========== Modern Mobilyalar ==========

class ModernChair : public Chair {
public:
    void sitOn() const override {
        std::cout << "Modern sandalyeye oturuyorsunuz - Şık ve rahat!" << std::endl;
    }
};

class ModernTable : public Table {
public:
    void use() const override {
        std::cout << "Modern masayı kullanıyorsunuz - Minimalist tasarım!" << std::endl;
    }
};

// ========== Klasik Mobilyalar ==========

class ClassicChair : public Chair {
public:
    void sitOn() const override {
        std::cout << "Klasik sandalyeye oturuyorsunuz - Ahşap ve zarif!" << std::endl;
    }
};

class ClassicTable : public Table {
public:
    void use() const override {
        std::cout << "Klasik masayı kullanıyorsunuz - Geleneksel tarz!" << std::endl;
    }
};

// ========== Soyut Fabrika ==========

class FurnitureFactory {
public:
    virtual ~FurnitureFactory() = default;
    virtual std::unique_ptr<Chair> createChair() const = 0;
    virtual std::unique_ptr<Table> createTable() const = 0;
};

// ========== Somut Fabrikalar ==========

class ModernFurnitureFactory : public FurnitureFactory {
public:
    std::unique_ptr<Chair> createChair() const override {
        return std::make_unique<ModernChair>();
    }
    
    std::unique_ptr<Table> createTable() const override {
        return std::make_unique<ModernTable>();
    }
};

class ClassicFurnitureFactory : public FurnitureFactory {
public:
    std::unique_ptr<Chair> createChair() const override {
        return std::make_unique<ClassicChair>();
    }
    
    std::unique_ptr<Table> createTable() const override {
        return std::make_unique<ClassicTable>();
    }
};

// ========== Kullanım ==========

void furnishRoom(const FurnitureFactory& factory) {
    auto chair = factory.createChair();
    auto table = factory.createTable();
    
    std::cout << "\n=== Oda Döşeniyor ===" << std::endl;
    chair->sitOn();
    table->use();
}

int main() {
    std::cout << "Hangi tarz mobilya istersiniz?" << std::endl;
    std::cout << "1. Modern" << std::endl;
    std::cout << "2. Klasik" << std::endl;
    
    int choice;
    std::cin >> choice;
    
    std::unique_ptr<FurnitureFactory> factory;
    
    if (choice == 1) {
        factory = std::make_unique<ModernFurnitureFactory>();
        std::cout << "\n*** Modern Mobilya Seçildi ***" << std::endl;
    } else {
        factory = std::make_unique<ClassicFurnitureFactory>();
        std::cout << "\n*** Klasik Mobilya Seçildi ***" << std::endl;
    }
    
    furnishRoom(*factory);
    
    return 0;
}
