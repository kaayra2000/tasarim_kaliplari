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
    
    // Construction sürecini builder'ın kendisi yönetir
    std::unique_ptr<Computer> build() {
        buildCPU();
        buildRAM();
        buildStorage();
        buildGPU();
        return std::move(computer);
    }
};

class GamingComputerBuilder : public ComputerBuilder {
public:
    void buildCPU() override {
        computer->CPU = "Intel i9-13900K";
    }
    
    void buildRAM() override {
        computer->RAM = "32GB DDR5";
    }
    
    void buildStorage() override {
        computer->storage = "2TB NVMe SSD";
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
        computer->storage = "512GB SSD";
    }
    
    void buildGPU() override {
        computer->GPU = "Integrated Graphics";
    }
};

// Kullanım - Çok daha basit!
int main() {
    GamingComputerBuilder gamingBuilder;
    auto gamingPC = gamingBuilder.build();
    std::cout << "=== Gaming PC ===\n";
    gamingPC->show();
    
    std::cout << "\n";
    
    OfficeComputerBuilder officeBuilder;
    auto officePC = officeBuilder.build();
    std::cout << "=== Office PC ===\n";
    officePC->show();
    
    return 0;
}
