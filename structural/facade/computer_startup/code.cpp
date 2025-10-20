#include <iostream>
#include <string>
#include <memory>

// Alt sistem bileşenleri
class CPU {
public:
    void freeze() {
        std::cout << "CPU: İşlemci donduruldu\n";
    }
    
    void jump(long position) {
        std::cout << "CPU: " << position << " adresine atlanıyor\n";
    }
    
    void execute() {
        std::cout << "CPU: Komutlar çalıştırılıyor\n";
    }
};

class Memory {
public:
    void load(long position, const std::string& data) {
        std::cout << "Memory: " << position << " adresine '" 
                  << data << "' yükleniyor\n";
    }
    
    void initialize() {
        std::cout << "Memory: Bellek başlatılıyor\n";
    }
};

class HardDrive {
public:
    std::string read(long lba, int size) {
        std::cout << "HardDrive: " << lba << " sektöründen " 
                  << size << " byte okunuyor\n";
        return "BOOT_DATA";
    }
    
    void spinUp() {
        std::cout << "HardDrive: Disk başlatılıyor\n";
    }
};

class BIOS {
public:
    void powerOnSelfTest() {
        std::cout << "BIOS: POST (Power-On Self Test) yapılıyor\n";
    }
    
    void loadBootloader() {
        std::cout << "BIOS: Bootloader yükleniyor\n";
    }
};

class OperatingSystem {
public:
    void loadKernel() {
        std::cout << "OS: Kernel yükleniyor\n";
    }
    
    void startServices() {
        std::cout << "OS: Sistem servisleri başlatılıyor\n";
    }
    
    void showDesktop() {
        std::cout << "OS: Masaüstü görüntüleniyor\n";
    }
};

// Facade sınıfı
class ComputerFacade {
private:
    std::unique_ptr<CPU> cpu;
    std::unique_ptr<Memory> memory;
    std::unique_ptr<HardDrive> hardDrive;
    std::unique_ptr<BIOS> bios;
    std::unique_ptr<OperatingSystem> os;
    
public:
    ComputerFacade() 
        : cpu(std::make_unique<CPU>()),
          memory(std::make_unique<Memory>()),
          hardDrive(std::make_unique<HardDrive>()),
          bios(std::make_unique<BIOS>()),
          os(std::make_unique<OperatingSystem>()) {}
    
    void start() {
        std::cout << "\n=== Bilgisayar başlatılıyor... ===\n";
        
        // BIOS aşaması
        bios->powerOnSelfTest();
        cpu->freeze();
        
        // Donanım başlatma
        memory->initialize();
        hardDrive->spinUp();
        
        // Boot işlemi
        bios->loadBootloader();
        memory->load(0x00000000, "BOOTLOADER");
        cpu->jump(0x00000000);
        
        // İşletim sistemi yükleme
        std::string bootData = hardDrive->read(100, 1024);
        memory->load(0x00001000, bootData);
        os->loadKernel();
        
        // Sistem başlatma
        cpu->execute();
        os->startServices();
        os->showDesktop();
        
        std::cout << "=== Sistem hazır! ===\n\n";
    }
    
    void restart() {
        std::cout << "\n=== Bilgisayar yeniden başlatılıyor... ===\n";
        std::cout << "Servisler durduruluyor...\n";
        std::cout << "Sistem kapatılıyor...\n";
        start();
    }
};

// Kullanım
int main() {
    // Facade ile basit kullanım
    ComputerFacade computer;
    
    // Tek bir metod çağrısıyla karmaşık başlatma işlemi
    computer.start();
    
    // Yeniden başlatma da kolay
    computer.restart();
    
    return 0;
}
