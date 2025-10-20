#include <iostream>
#include <memory>
#include <string>

// Hedef arayüz: istemci yerel dosya oynatıcıları bu sözleşme ile çalışıyor
class MediaPlayer {
public:
    virtual ~MediaPlayer() = default;
    virtual void play(const std::string& resource) = 0;
};

class LocalAudioPlayer : public MediaPlayer {
public:
    void play(const std::string& resource) override {
        std::cout << "LocalAudioPlayer: '" << resource << "' dosyası çalınıyor\n";
    }
};

// Uyumsuz üçüncü parti servis (adaptee)
class CloudStreamingService {
public:
    void connect(const std::string& region) {
        std::cout << "CloudStreamingService: " << region << " sunucusuna bağlanılıyor\n";
    }

    void authenticate(const std::string& token) {
        std::cout << "CloudStreamingService: Kullanıcı kimliği doğrulandı -> " << token << "\n";
    }

    void startStream(const std::string& trackId) {
        std::cout << "CloudStreamingService: '" << trackId << "' adlı parça yayınlanıyor\n";
    }

    void stopStream() {
        std::cout << "CloudStreamingService: Akış durduruldu\n";
    }
};

// Adapter hedef arayüzü uygulayarak üçüncü parti servisi gizler
class StreamingAdapter : public MediaPlayer {
private:
    std::unique_ptr<CloudStreamingService> service;
    std::string regionEndpoint;
    std::string authToken;

public:
    StreamingAdapter(std::string region, std::string token)
        : service(std::make_unique<CloudStreamingService>()),
          regionEndpoint(std::move(region)),
          authToken(std::move(token)) {}

    void play(const std::string& resource) override {
        std::cout << "StreamingAdapter: Bulut akışına hazırlanılıyor\n";
        service->connect(regionEndpoint);
        service->authenticate(authToken);
        service->startStream(resource);
        service->stopStream();
    }
};

int main() {
    std::cout << "=== Yerel Şarkı ===\n";
    std::unique_ptr<MediaPlayer> player = std::make_unique<LocalAudioPlayer>();
    player->play("lofi-beats.mp3");

    std::cout << "\n=== Çevrimiçi Şarkı ===\n";
    player = std::make_unique<StreamingAdapter>("eu-central-1", "token-42");
    player->play("uptempo-sax");

    std::cout << "\n=== Paylaşılan Arayüz ===\n";
    player->play("lofi-beats.mp3");

    return 0;
}
