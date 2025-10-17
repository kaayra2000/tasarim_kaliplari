#include <iostream>
#include <memory>
#include <string>

// Basit (tembel) Singleton - Thread-safe DEĞİL
class Logger {
private:
    static std::unique_ptr<Logger> instance; // bellek güvenli ancak thread-unsafe başlatma
    std::string prefix;

    // Kurucu private
    Logger() : prefix("[LazyLogger]") {}

    // Kopyalama engelli
    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

public:
    static Logger* getInstance() {
        if (!instance) {
            // Çoklu thread altında yarış olabilir!
            instance = std::unique_ptr<Logger>(new Logger());
        }
        return instance.get();
    }

    void setPrefix(const std::string& p) { prefix = p; }

    void log(const std::string& msg) {
        std::cout << prefix << " " << msg << "\n";
    }
};

// Statik alan tanımı
std::unique_ptr<Logger> Logger::instance = nullptr;

int main() {
    auto* l1 = Logger::getInstance();
    auto* l2 = Logger::getInstance();

    l1->log("Merhaba dünya");

    // Aynı instance
    std::cout << "Aynı mı? " << std::boolalpha << (l1 == l2) << "\n";

    l2->setPrefix("[APP]");
    l1->log("Prefix değişti mi?");

    return 0;
}
