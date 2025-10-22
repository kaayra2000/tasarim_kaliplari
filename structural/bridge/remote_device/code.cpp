#include <iostream>
#include <algorithm>
#include <string>

// Gerçekleştirme (Implementation) hiyerarşisi
struct Device {
    virtual ~Device() = default;
    virtual bool isEnabled() const = 0;
    virtual void enable() = 0;
    virtual void disable() = 0;
    virtual int getVolume() const = 0;
    virtual void setVolume(int v) = 0;
    virtual int getChannel() const = 0;
    virtual void setChannel(int c) = 0;
};

class TV : public Device {
    bool on_ {false};
    int volume_ {30};
    int channel_ {1};
public:
    bool isEnabled() const override { return on_; }
    void enable() override { on_ = true; std::cout << "TV: Güç AÇIK\n"; }
    void disable() override { on_ = false; std::cout << "TV: Güç KAPALI\n"; }
    int getVolume() const override { return volume_; }
    void setVolume(int v) override {
        volume_ = std::clamp(v, 0, 100);
        std::cout << "TV: ses -> " << volume_ << "\n";
    }
    int getChannel() const override { return channel_; }
    void setChannel(int c) override {
        channel_ = std::max(1, c);
        std::cout << "TV: kanal -> " << channel_ << "\n";
    }
};

class Radio : public Device {
    bool on_ {false};
    int volume_ {20};
    int channel_ {101};
public:
    bool isEnabled() const override { return on_; }
    void enable() override { on_ = true; std::cout << "Radyo: Güç AÇIK\n"; }
    void disable() override { on_ = false; std::cout << "Radyo: Güç KAPALI\n"; }
    int getVolume() const override { return volume_; }
    void setVolume(int v) override {
        volume_ = std::clamp(v, 0, 100);
        std::cout << "Radyo: ses -> " << volume_ << "\n";
    }
    int getChannel() const override { return channel_; }
    void setChannel(int c) override {
        channel_ = std::max(1, c);
        std::cout << "Radyo: kanal -> " << channel_ << "\n";
    }
};

// Soyutlama (Abstraction) hiyerarşisi
class Remote {
protected:
    Device& device_;
public:
    explicit Remote(Device& d) : device_(d) {}
    virtual ~Remote() = default;

    void togglePower() {
        if (device_.isEnabled()) device_.disable();
        else device_.enable();
    }
    void volumeDown() { device_.setVolume(device_.getVolume() - 10); }
    void volumeUp()   { device_.setVolume(device_.getVolume() + 10); }
    void channelDown(){ device_.setChannel(device_.getChannel() - 1); }
    void channelUp()  { device_.setChannel(device_.getChannel() + 1); }
};

class AdvancedRemote : public Remote {
public:
    using Remote::Remote; // kurucu devral
    void mute() { device_.setVolume(0); }
};

int main() {
    std::cout << "=== Köprü (Bridge): Kumanda <-> Cihaz ===\n";

    TV tv;
    AdvancedRemote akilliKumanda(tv);
    akilliKumanda.togglePower();
    akilliKumanda.volumeUp();
    akilliKumanda.channelUp();
    akilliKumanda.mute();
    akilliKumanda.togglePower();

    std::cout << "\nAynı kumanda SOYUTLAMASINI kullanarak cihazı Radyo'ya değiştiriyoruz...\n";
    Radio radyo;
    Remote basitKumanda(radyo);
    basitKumanda.togglePower();
    basitKumanda.volumeUp();
    basitKumanda.channelDown();

    return 0;
}
