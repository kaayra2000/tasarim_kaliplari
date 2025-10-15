#include <iostream>
#include <memory>
#include <string>
#include <map>
using namespace std;

// Ürün türleri için enum
enum class VehicleType {
    CAR,
    MOTORCYCLE,
    TRUCK
};

// Soyut ürün sınıfı
class Vehicle {
protected:
    string brand;
    int year;
    double price;
    
public:
    Vehicle(const string& b, int y, double p) 
        : brand(b), year(y), price(p) {}
    
    virtual ~Vehicle() = default;
    
    virtual void displayInfo() const = 0;
    virtual void start() const = 0;
    virtual double calculateTax() const = 0;
    
    // Getter metodları
    string getBrand() const { return brand; }
    int getYear() const { return year; }
    double getPrice() const { return price; }
};

// Somut ürün 1: Araba
class Car : public Vehicle {
private:
    int doorCount;
    
public:
    Car(const string& brand, int year, double price, int doors)
        : Vehicle(brand, year, price), doorCount(doors) {}
    
    void displayInfo() const override {
        cout << "\n=== ARABA BİLGİLERİ ===" << endl;
        cout << "Marka: " << brand << endl;
        cout << "Yıl: " << year << endl;
        cout << "Fiyat: " << price << " TL" << endl;
        cout << "Kapı Sayısı: " << doorCount << endl;
    }
    
    void start() const override {
        cout << brand << " marka araba çalıştırılıyor... Vroom!" << endl;
    }
    
    double calculateTax() const override {
        return price * 0.18; // %18 ÖTV
    }
};

// Somut ürün 2: Motosiklet
class Motorcycle : public Vehicle {
private:
    int engineCC;
    
public:
    Motorcycle(const string& brand, int year, double price, int cc)
        : Vehicle(brand, year, price), engineCC(cc) {}
    
    void displayInfo() const override {
        cout << "\n=== MOTOSİKLET BİLGİLERİ ===" << endl;
        cout << "Marka: " << brand << endl;
        cout << "Yıl: " << year << endl;
        cout << "Fiyat: " << price << " TL" << endl;
        cout << "Motor Hacmi: " << engineCC << " cc" << endl;
    }
    
    void start() const override {
        cout << brand << " marka motosiklet çalıştırılıyor... Brrr!" << endl;
    }
    
    double calculateTax() const override {
        return price * 0.08; // %8 ÖTV
    }
};

// Somut ürün 3: Kamyon
class Truck : public Vehicle {
private:
    double loadCapacity;
    
public:
    Truck(const string& brand, int year, double price, double capacity)
        : Vehicle(brand, year, price), loadCapacity(capacity) {}
    
    void displayInfo() const override {
        cout << "\n=== KAMYON BİLGİLERİ ===" << endl;
        cout << "Marka: " << brand << endl;
        cout << "Yıl: " << year << endl;
        cout << "Fiyat: " << price << " TL" << endl;
        cout << "Yük Kapasitesi: " << loadCapacity << " ton" << endl;
    }
    
    void start() const override {
        cout << brand << " marka kamyon çalıştırılıyor... Grrrr!" << endl;
    }
    
    double calculateTax() const override {
        return price * 0.05; // %5 ÖTV
    }
};

// Factory sınıfı (Akıllı işaretçiler ile)
class VehicleFactory {
public:
    static unique_ptr<Vehicle> createVehicle(
        VehicleType type,
        const string& brand,
        int year,
        double price,
        double extraParam = 0
    ) {
        switch (type) {
            case VehicleType::CAR:
                return make_unique<Car>(brand, year, price, 
                                       static_cast<int>(extraParam));
            
            case VehicleType::MOTORCYCLE:
                return make_unique<Motorcycle>(brand, year, price, 
                                              static_cast<int>(extraParam));
            
            case VehicleType::TRUCK:
                return make_unique<Truck>(brand, year, price, extraParam);
            
            default:
                throw invalid_argument("Geçersiz araç tipi!");
        }
    }
    
    // String tabanlı oluşturma (opsiyonel)
    static unique_ptr<Vehicle> createVehicleByName(
        const string& typeName,
        const string& brand,
        int year,
        double price,
        double extraParam = 0
    ) {
        static map<string, VehicleType> typeMap = {
            {"car", VehicleType::CAR},
            {"motorcycle", VehicleType::MOTORCYCLE},
            {"truck", VehicleType::TRUCK}
        };
        
        auto it = typeMap.find(typeName);
        if (it == typeMap.end()) {
            throw invalid_argument("Bilinmeyen araç tipi: " + typeName);
        }
        
        return createVehicle(it->second, brand, year, price, extraParam);
    }
};

// Ana program
int main() {
    try {
        // Enum kullanarak araç oluşturma
        auto car = VehicleFactory::createVehicle(
            VehicleType::CAR, "BMW", 2023, 1500000, 4
        );
        car->displayInfo();
        car->start();
        cout << "Vergi: " << car->calculateTax() << " TL" << endl;
        
        // String kullanarak araç oluşturma
        auto motorcycle = VehicleFactory::createVehicleByName(
            "motorcycle", "Yamaha", 2024, 250000, 600
        );
        motorcycle->displayInfo();
        motorcycle->start();
        cout << "Vergi: " << motorcycle->calculateTax() << " TL" << endl;
        
        auto truck = VehicleFactory::createVehicle(
            VehicleType::TRUCK, "Mercedes", 2022, 3000000, 18.5
        );
        truck->displayInfo();
        truck->start();
        cout << "Vergi: " << truck->calculateTax() << " TL" << endl;
        
        // Araçlar otomatik olarak temizlenir (unique_ptr sayesinde)
        
    } catch (const exception& e) {
        cerr << "Hata: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}
