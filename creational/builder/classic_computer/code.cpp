#include <iostream>
#include <string>
#include <memory>

class Computer {
public:
    std::string CPU;
    std::string RAM;
    std::string storage;
    std::string GPU;
    
    void show() const {
        std::cout << "Computer Configuration:\n"
                  << "CPU: " << CPU << "\n"
                  << "RAM: " << RAM << "\n"
                  << "Storage: " << storage << "\n"
                  << "GPU: " << GPU << "\n";
    }
};

// Abstract Builder
class ComputerBuilder {
protected:
    std::unique_ptr<Computer> computer;
    
public:
    ComputerBuilder() { computer = std::make_unique<Computer>(); }
    virtual ~ComputerBuilder() = default;
    
    virtual void buildCPU() = 0;
    virtual void buildRAM() = 0;
    virtual void buildStorage() = 0;
    virtual void buildGPU() = 0;
    
    std::unique_ptr<Computer> getComputer() {
        return std::move(computer);
    }
};
class ComputerDirector {
private:
    ComputerBuilder* builder;
    
public:
    void setBuilder(ComputerBuilder* b) {
        builder = b;
    }
    
    // Farklı construction stratejileri
    std::unique_ptr<Computer> buildFullComputer() {
        builder->buildCPU();
        builder->buildRAM();
        builder->buildStorage();
        builder->buildGPU();
        return builder->getComputer();
    }
    
    std::unique_ptr<Computer> buildMinimalComputer() {
        builder->buildCPU();
        builder->buildRAM();
        // Storage ve GPU yok - minimal konfigürasyon
        return builder->getComputer();
    }
    
    std::unique_ptr<Computer> buildStorageOptimized() {
        builder->buildCPU();
        builder->buildRAM();
        builder->buildStorage();
        builder->buildStorage(); // Ekstra storage
        // GPU yok
        return builder->getComputer();
    }
};

// Concrete Builders
class GamingComputerBuilder : public ComputerBuilder {
public:
    void buildCPU() override {
        computer->CPU = "Intel i9-13900K";
    }

    void buildRAM() override {
        computer->RAM = "32GB DDR5";
    }

    void buildStorage() override {
        if (computer->storage.empty()) {
            computer->storage = "2TB NVMe SSD";
        } else {
            computer->storage += " + 2TB NVMe SSD"; // ikinci çağrıda ek depolama
        }
    }

    void buildGPU() override {
        computer->GPU = "NVIDIA RTX 4090";
    }
};

class OfficeComputerBuilder : public ComputerBuilder {
public:
    void buildCPU() override {
        computer->CPU = "Intel i5-12400";
    }

    void buildRAM() override {
        computer->RAM = "16GB DDR4";
    }

    void buildStorage() override {
        if (computer->storage.empty()) {
            computer->storage = "512GB SSD";
        } else {
            computer->storage += " + 512GB SSD"; // ikinci çağrıda ek depolama
        }
    }

    void buildGPU() override {
        computer->GPU = "Integrated Graphics";
    }
};

int main() {
    ComputerDirector director;

    // 1) Gaming - Full yapılandırma
    GamingComputerBuilder gamingBuilder1;
    director.setBuilder(&gamingBuilder1);
    auto gamingFull = director.buildFullComputer();
    std::cout << "=== Gaming (Full) ===\n";
    gamingFull->show();

    std::cout << "\n";

    // 2) Office - Minimal yapılandırma (Storage ve GPU yok)
    OfficeComputerBuilder officeBuilder1;
    director.setBuilder(&officeBuilder1);
    auto officeMinimal = director.buildMinimalComputer();
    std::cout << "=== Office (Minimal) ===\n";
    officeMinimal->show();

    std::cout << "\n";

    // 3) Office - Depolama odaklı (storage iki kez)
    OfficeComputerBuilder officeBuilder2;
    director.setBuilder(&officeBuilder2);
    auto officeStorage = director.buildStorageOptimized();
    std::cout << "=== Office (Storage-Optimized) ===\n";
    officeStorage->show();

    return 0;
}
