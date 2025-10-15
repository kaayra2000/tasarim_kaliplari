#include <iostream>
#include <memory>
#include <string>

// ========== Soyut Ürünler ==========

// Soyut Buton arayüzü
class Button {
public:
    virtual ~Button() = default;
    virtual void render() const = 0;
    virtual void onClick() const = 0;
};

// Soyut Checkbox arayüzü
class Checkbox {
public:
    virtual ~Checkbox() = default;
    virtual void render() const = 0;
    virtual void toggle() const = 0;
};

// ========== Windows Ürünleri ==========

class WindowsButton : public Button {
public:
    void render() const override {
        std::cout << "Windows stili buton çiziliyor" << std::endl;
    }
    
    void onClick() const override {
        std::cout << "Windows butonu tıklandı!" << std::endl;
    }
};

class WindowsCheckbox : public Checkbox {
public:
    void render() const override {
        std::cout << "Windows stili checkbox çiziliyor" << std::endl;
    }
    
    void toggle() const override {
        std::cout << "Windows checkbox durumu değişti" << std::endl;
    }
};

// ========== MacOS Ürünleri ==========

class MacButton : public Button {
public:
    void render() const override {
        std::cout << "MacOS stili buton çiziliyor" << std::endl;
    }
    
    void onClick() const override {
        std::cout << "Mac butonu tıklandı!" << std::endl;
    }
};

class MacCheckbox : public Checkbox {
public:
    void render() const override {
        std::cout << "MacOS stili checkbox çiziliyor" << std::endl;
    }
    
    void toggle() const override {
        std::cout << "Mac checkbox durumu değişti" << std::endl;
    }
};

// ========== Linux Ürünleri ==========

class LinuxButton : public Button {
public:
    void render() const override {
        std::cout << "Linux stili buton çiziliyor" << std::endl;
    }
    
    void onClick() const override {
        std::cout << "Linux butonu tıklandı!" << std::endl;
    }
};

class LinuxCheckbox : public Checkbox {
public:
    void render() const override {
        std::cout << "Linux stili checkbox çiziliyor" << std::endl;
    }
    
    void toggle() const override {
        std::cout << "Linux checkbox durumu değişti" << std::endl;
    }
};

// ========== Soyut Fabrika ==========

class GUIFactory {
public:
    virtual ~GUIFactory() = default;
    virtual std::unique_ptr<Button> createButton() const = 0;
    virtual std::unique_ptr<Checkbox> createCheckbox() const = 0;
};

// ========== Somut Fabrikalar ==========

class WindowsFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<WindowsButton>();
    }
    
    std::unique_ptr<Checkbox> createCheckbox() const override {
        return std::make_unique<WindowsCheckbox>();
    }
};

class MacFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<MacButton>();
    }
    
    std::unique_ptr<Checkbox> createCheckbox() const override {
        return std::make_unique<MacCheckbox>();
    }
};

class LinuxFactory : public GUIFactory {
public:
    std::unique_ptr<Button> createButton() const override {
        return std::make_unique<LinuxButton>();
    }
    
    std::unique_ptr<Checkbox> createCheckbox() const override {
        return std::make_unique<LinuxCheckbox>();
    }
};

// ========== İstemci Kodu ==========

class Application {
private:
    std::unique_ptr<Button> button;
    std::unique_ptr<Checkbox> checkbox;
    
public:
    Application(const GUIFactory& factory) {
        button = factory.createButton();
        checkbox = factory.createCheckbox();
    }
    
    void render() const {
        button->render();
        checkbox->render();
    }
    
    void interact() const {
        button->onClick();
        checkbox->toggle();
    }
};

// ========== Ana Program ==========

int main() {
    std::string platform;
    std::cout << "Platform seçin (windows/mac/linux): ";
    std::cin >> platform;
    
    std::unique_ptr<GUIFactory> factory;
    
    if (platform == "windows") {
        factory = std::make_unique<WindowsFactory>();
    } else if (platform == "mac") {
        factory = std::make_unique<MacFactory>();
    } else if (platform == "linux") {
        factory = std::make_unique<LinuxFactory>();
    } else {
        std::cout << "Geçersiz platform!" << std::endl;
        return 1;
    }
    
    Application app(*factory);
    
    std::cout << "\n=== Arayüz Çiziliyor ===" << std::endl;
    app.render();
    
    std::cout << "\n=== Kullanıcı Etkileşimi ===" << std::endl;
    app.interact();
    
    return 0;
}
