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
