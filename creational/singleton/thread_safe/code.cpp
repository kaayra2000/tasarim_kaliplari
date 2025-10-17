#include <iostream>
#include <memory>
#include <mutex>
#include <string>

// Thread-safe Singleton (Meyers Singleton + call_once örneği)
class SafeLogger {
private:
    std::string prefix;

    SafeLogger() : prefix("[SafeLogger]") {}
    SafeLogger(const SafeLogger&) = delete;
    SafeLogger& operator=(const SafeLogger&) = delete;

public:
    static SafeLogger& instance() {
        // Meyers Singleton: C++11 ve sonrası için thread-safe statik yerel değişken başlatma
        static SafeLogger inst;
        return inst;
    }

    void setPrefix(const std::string& p) { prefix = p; }

    void log(const std::string& msg) {
        // Örnek basitlik için log'u kilitlemedik; çıktı karışabilir.
        // Gerçekte ayrı bir mutex ile koruma yapılabilir.
        std::cout << prefix << " " << msg << "\n";
    }
};

int main() {
    auto& l1 = SafeLogger::instance();
    auto& l2 = SafeLogger::instance();

    l1.log("Merhaba güvenli dünya");

    std::cout << "Aynı mı? " << std::boolalpha << (&l1 == &l2) << "\n";

    l2.setPrefix("[SAFE-APP]");
    l1.log("Prefix değişti mi?");

    return 0;
}
