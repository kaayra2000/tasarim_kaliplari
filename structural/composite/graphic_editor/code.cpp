#include <iostream>
#include <memory>
#include <string>
#include <vector>

// Composite pattern: treat shapes and groups uniformly

struct Graphic {
    virtual ~Graphic() = default;
    virtual void draw(int indent = 0) const = 0;
};

namespace detail {
static void printIndent(int n) {
    for (int i = 0; i < n; ++i) std::cout << ' ';
}
}

class Circle : public Graphic {
public:
    Circle(std::string name, int radius) : name_(std::move(name)), radius_(radius) {}
    void draw(int indent = 0) const override {
        detail::printIndent(indent);
        std::cout << "Circle(" << name_ << ", r=" << radius_ << ")\n";
    }
private:
    std::string name_;
    int radius_{};
};

class Rectangle : public Graphic {
public:
    Rectangle(std::string name, int w, int h) : name_(std::move(name)), w_(w), h_(h) {}
    void draw(int indent = 0) const override {
        detail::printIndent(indent);
        std::cout << "Rectangle(" << name_ << ", w=" << w_ << ", h=" << h_ << ")\n";
    }
private:
    std::string name_;
    int w_{};
    int h_{};
};

class Group : public Graphic {
public:
    explicit Group(std::string name) : name_(std::move(name)) {}

    void add(std::unique_ptr<Graphic> g) {
        children_.emplace_back(std::move(g));
    }

    void draw(int indent = 0) const override {
        detail::printIndent(indent);
        std::cout << "Group: " << name_ << "\n";
        for (const auto &c : children_) {
            c->draw(indent + 2);
        }
    }
private:
    std::string name_;
    std::vector<std::unique_ptr<Graphic>> children_{};
};

int main() {
    auto scene = std::make_unique<Group>("Scene");

    scene->add(std::make_unique<Circle>("sun", 5));
    scene->add(std::make_unique<Rectangle>("ground", 20, 3));

    auto layer1 = std::make_unique<Group>("Layer1");
    layer1->add(std::make_unique<Circle>("ball", 2));
    layer1->add(std::make_unique<Rectangle>("box", 2, 2));

    scene->add(std::move(layer1));

    scene->draw();
    return 0;
}
