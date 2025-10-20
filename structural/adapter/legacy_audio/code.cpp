#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Hedef arayüz: 3.5mm jak üzerinden ses alan eski kulaklıklar
class AnalogHeadset {
public:
    virtual ~AnalogHeadset() = default;
    virtual void playAnalog(float left, float right) = 0;
};

class StudioHeadphones : public AnalogHeadset {
public:
    void playAnalog(float left, float right) override {
        std::cout << "StudioHeadphones: Sol=" << left
                  << "db Sağ=" << right << "db analog sinyal çalınıyor\n";
    }
};

// Uyumsuz sınıf: yalnızca dijital USB-C çıkış sağlayan modern telefon
class UsbTypeCPhone {
public:
    std::vector<int> streamDigital(const std::string& track) {
        std::cout << "UsbTypeCPhone: '" << track << "' dijital PCM akışı gönderiliyor\n";
        return {120, 118, 115, 113}; // örneklenmiş amplitude
    }
};

// Adapter: dijital veriyi analog sinyale çevirerek eski kulaklığa uyarlar
class UsbToJackAdapter : public AnalogHeadset {
private:
    std::unique_ptr<UsbTypeCPhone> phone;

    static std::pair<float, float> convertToStereo(const std::vector<int>& pcm) {
        if (pcm.empty()) {
            return {0.0f, 0.0f};
        }

        float sum = 0.0f;
        for (int sample : pcm) {
            sum += static_cast<float>(sample);
        }
        float avg = sum / static_cast<float>(pcm.size());
        return {avg / 10.0f, avg / 10.0f};
    }

public:
    UsbToJackAdapter() : phone(std::make_unique<UsbTypeCPhone>()) {}

    void playAnalog(float left, float right) override {
        std::cout << "UsbToJackAdapter: Manuel analog değerler gönderiliyor\n";
        std::cout << "Adapter analog çıkış -> Sol=" << left << " Sağ=" << right << "\n";
    }

    void playFromPhone(const std::string& track) {
        std::cout << "UsbToJackAdapter: Dijital akış analog sinyale dönüştürülüyor\n";
        auto pcm = phone->streamDigital(track);
        auto [left, right] = convertToStereo(pcm);
        playAnalog(left, right);
    }
};

int main() {
    std::cout << "=== Eski Sistem ===\n";
    std::unique_ptr<AnalogHeadset> headset = std::make_unique<StudioHeadphones>();
    headset->playAnalog(7.5f, 7.4f);

    std::cout << "\n=== Modern Telefon ile Uyumluluk ===\n";
    auto usbAdapter = std::make_unique<UsbToJackAdapter>();
    usbAdapter->playFromPhone("analog-dreams.aac");

    std::cout << "\n=== Aynı Arayüz ===\n";
    headset = std::move(usbAdapter);
    headset->playAnalog(6.0f, 6.0f);

    return 0;
}
