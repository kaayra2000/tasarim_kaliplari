#include <iostream>
#include <memory>
#include <numeric>
#include <string>
#include <vector>

// Composite pattern: files and directories share a common interface

struct Node {
    virtual ~Node() = default;
    virtual std::size_t size() const = 0;
    virtual void ls(int indent = 0) const = 0;
};

namespace detail {
static void printIndent(int n) {
    for (int i = 0; i < n; ++i) std::cout << ' ';
}
}

class File : public Node {
public:
    File(std::string name, std::size_t bytes) : name_(std::move(name)), bytes_(bytes) {}
    std::size_t size() const override { return bytes_; }
    void ls(int indent = 0) const override {
        detail::printIndent(indent);
        std::cout << "File: " << name_ << " (" << bytes_ << ")\n";
    }
private:
    std::string name_;
    std::size_t bytes_{};
};

class Directory : public Node {
public:
    explicit Directory(std::string name) : name_(std::move(name)) {}

    void add(std::unique_ptr<Node> n) {
        children_.emplace_back(std::move(n));
    }

    std::size_t size() const override {
        std::size_t total = 0;
        for (const auto &c : children_) total += c->size();
        return total;
    }

    void ls(int indent = 0) const override {
        detail::printIndent(indent);
        std::cout << "Dir: " << name_ << " (total=" << size() << ")\n";
        for (const auto &c : children_) c->ls(indent + 2);
    }
private:
    std::string name_;
    std::vector<std::unique_ptr<Node>> children_{};
};

int main() {
    auto root = std::make_unique<Directory>("root");
    root->add(std::make_unique<File>("notes.txt", 12));

    auto docs = std::make_unique<Directory>("docs");
    docs->add(std::make_unique<File>("report.pdf", 120));
    docs->add(std::make_unique<File>("data.bin", 256));

    root->add(std::move(docs));
    root->add(std::make_unique<File>("picture.jpg", 64));

    root->ls();
    std::cout << "Total size: " << root->size() << " bytes\n";
    return 0;
}
