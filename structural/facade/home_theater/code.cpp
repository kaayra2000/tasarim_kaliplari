#include <iostream>
#include <string>

// Alt sistem bileşenleri - Karmaşık arayüzler
class DVDPlayer {
public:
    void on() {
        std::cout << "DVD Player açılıyor...\n";
    }
    
    void play(const std::string& movie) {
        std::cout << "DVD Player: '" << movie << "' oynatılıyor\n";
    }
    
    void stop() {
        std::cout << "DVD Player durduruluyor\n";
    }
    
    void off() {
        std::cout << "DVD Player kapatılıyor\n";
    }
};

class Amplifier {
public:
    void on() {
        std::cout << "Amplifikatör açılıyor...\n";
    }
    
    void setVolume(int level) {
        std::cout << "Amplifikatör ses seviyesi: " << level << "\n";
    }
    
    void setSurroundSound() {
        std::cout << "Amplifikatör: Surround Sound modu aktif\n";
    }
    
    void off() {
        std::cout << "Amplifikatör kapatılıyor\n";
    }
};

class Projector {
public:
    void on() {
        std::cout << "Projektör açılıyor...\n";
    }
    
    void wideScreenMode() {
        std::cout << "Projektör: Geniş ekran modu (16:9)\n";
    }
    
    void off() {
        std::cout << "Projektör kapatılıyor\n";
    }
};

class Lights {
public:
    void dim(int level) {
        std::cout << "Işıklar kısılıyor: %" << level << "\n";
    }
    
    void on() {
        std::cout << "Işıklar açılıyor\n";
    }
};

class Screen {
public:
    void down() {
        std::cout << "Projeksiyon perdesi indiriliyor\n";
    }
    
    void up() {
        std::cout << "Projeksiyon perdesi kaldırılıyor\n";
    }
};

// Facade sınıfı - Basit arayüz
class HomeTheaterFacade {
private:
    DVDPlayer* dvd;
    Amplifier* amp;
    Projector* projector;
    Lights* lights;
    Screen* screen;
    
public:
    HomeTheaterFacade(DVDPlayer* d, Amplifier* a, Projector* p, Lights* l, Screen* s)
        : dvd(d), amp(a), projector(p), lights(l), screen(s) {}
    
    void watchMovie(const std::string& movie) {
        std::cout << "\n=== Film izlemeye hazırlanılıyor... ===\n";
        lights->dim(10);
        screen->down();
        projector->on();
        projector->wideScreenMode();
        amp->on();
        amp->setSurroundSound();
        amp->setVolume(15);
        dvd->on();
        dvd->play(movie);
        std::cout << "=== Keyfini çıkarın! ===\n\n";
    }
    
    void endMovie() {
        std::cout << "\n=== Film sistemi kapatılıyor... ===\n";
        dvd->stop();
        dvd->off();
        amp->off();
        projector->off();
        screen->up();
        lights->on();
        std::cout << "=== Sistem kapatıldı ===\n\n";
    }
};

// Kullanım
int main() {
    // Alt sistem bileşenlerini oluştur
    DVDPlayer dvd;
    Amplifier amp;
    Projector projector;
    Lights lights;
    Screen screen;
    
    // Facade'i oluştur
    HomeTheaterFacade homeTheater(&dvd, &amp, &projector, &lights, &screen);
    
    // Facade ile basit kullanım
    homeTheater.watchMovie("The Matrix");
    
    // Film bitti
    homeTheater.endMovie();
    
    return 0;
}
