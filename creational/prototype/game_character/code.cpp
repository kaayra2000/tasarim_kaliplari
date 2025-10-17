#include <iostream>
#include <string>
#include <memory>
#include <map>

// Prototype interface
class GameCharacter {
protected:
    std::string name;
    int health;
    int attackPower;
public:
    virtual ~GameCharacter() {}
    virtual std::unique_ptr<GameCharacter> clone() = 0;
    virtual void display() = 0;
    
    void setName(const std::string& n) { name = n; }
};

// Concrete Prototype: Warrior
class Warrior : public GameCharacter {
private:
    int armor;
public:
    Warrior(int hp, int attack, int arm) : armor(arm) {
        health = hp;
        attackPower = attack;
        name = "Warrior";
    }
    
    std::unique_ptr<GameCharacter> clone() override {
        return std::make_unique<Warrior>(*this);
    }
    
    void display() override {
        std::cout << "Karakter: " << name 
                  << " | Can: " << health 
                  << " | Saldırı: " << attackPower 
                  << " | Zırh: " << armor << std::endl;
    }
};

// Concrete Prototype: Mage
class Mage : public GameCharacter {
private:
    int mana;
public:
    Mage(int hp, int attack, int m) : mana(m) {
        health = hp;
        attackPower = attack;
        name = "Mage";
    }
    
    std::unique_ptr<GameCharacter> clone() override {
        return std::make_unique<Mage>(*this);
    }
    
    void display() override {
        std::cout << "Karakter: " << name 
                  << " | Can: " << health 
                  << " | Saldırı: " << attackPower 
                  << " | Mana: " << mana << std::endl;
    }
};

// Character Registry (Prototype Manager)
class CharacterRegistry {
private:
    std::map<std::string, std::unique_ptr<GameCharacter>> prototypes;
public:
    void addPrototype(const std::string& key, std::unique_ptr<GameCharacter> prototype) {
        prototypes[key] = std::move(prototype);
    }
    
    std::unique_ptr<GameCharacter> createCharacter(const std::string& key) {
        if (prototypes.find(key) != prototypes.end()) {
            return prototypes[key]->clone();
        }
        return nullptr;
    }
};

int main() {
    CharacterRegistry registry;
    
    // Prototipleri kaydet
    registry.addPrototype("warrior", std::make_unique<Warrior>(100, 50, 30));
    registry.addPrototype("mage", std::make_unique<Mage>(70, 80, 100));
    
    // Klonlayarak yeni karakterler oluştur
    auto player1 = registry.createCharacter("warrior");
    player1->setName("Ahmet Savaşçı");
    
    auto player2 = registry.createCharacter("mage");
    player2->setName("Ayşe Büyücü");
    
    auto player3 = registry.createCharacter("warrior");
    player3->setName("Mehmet Savaşçı");
    
    player1->display();
    player2->display();
    player3->display();
    
    return 0;
}
