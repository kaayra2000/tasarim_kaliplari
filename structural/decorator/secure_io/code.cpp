#include <iostream>
#include <memory>
#include <string>
#include <algorithm>

// Decorator kalıbı: Veri kaynağına (dosya/soket) şifreleme ve sıkıştırma gibi sorumlulukları
// çalışma zamanında eklemek.

// Bileşen arayüzü
class DataSource {
public:
    virtual ~DataSource() = default;
    virtual void write(const std::string& data) = 0;
    virtual std::string read() const = 0;
};

// Somut bileşen: Basit bellek içi kaynak (örnek basitlik için dosya yerine)
class MemoryDataSource : public DataSource {
private:
    std::string buffer;

public:
    void write(const std::string& data) override {
        buffer = data;
        std::cout << "MemoryDataSource: Veri yazıldı (" << buffer.size() << " bayt)\n";
    }

    std::string read() const override {
        std::cout << "MemoryDataSource: Veri okunuyor\n";
        return buffer;
    }
};

// Decorator temel sınıfı
class DataSourceDecorator : public DataSource {
protected:
    std::unique_ptr<DataSource> wrappee;

public:
    explicit DataSourceDecorator(std::unique_ptr<DataSource> src)
        : wrappee(std::move(src)) {}
};

// Basit (temsili) sıkıştırma: tekrar eden karakterleri sayarak kısalt (RLE benzeri)
class CompressionDecorator : public DataSourceDecorator {
    static std::string compress(const std::string& raw) {
        if (raw.empty()) return {};
        std::string out;
        out.reserve(raw.size());
        char current = raw[0];
        int count = 1;
        for (size_t i = 1; i < raw.size(); ++i) {
            if (raw[i] == current) {
                ++count;
            } else {
                out += current;
                out += std::to_string(count);
                current = raw[i];
                count = 1;
            }
        }
        out += current;
        out += std::to_string(count);
        return out;
    }

    static std::string decompress(const std::string& rle) {
        std::string out;
        out.reserve(rle.size());
        size_t i = 0;
        while (i < rle.size()) {
            char c = rle[i++];
            std::string num;
            while (i < rle.size() && std::isdigit(static_cast<unsigned char>(rle[i]))) {
                num.push_back(rle[i]);
                ++i;
            }
            int count = num.empty() ? 1 : std::stoi(num);
            out.append(static_cast<size_t>(count), c);
        }
        return out;
    }

public:
    explicit CompressionDecorator(std::unique_ptr<DataSource> src)
        : DataSourceDecorator(std::move(src)) {}

    void write(const std::string& data) override {
        auto zipped = compress(data);
        std::cout << "CompressionDecorator: " << data.size() << " -> "
                  << zipped.size() << " bayt\n";
        wrappee->write(zipped);
    }

    std::string read() const override {
        auto zipped = wrappee->read();
        auto unzipped = decompress(zipped);
        std::cout << "CompressionDecorator: açılıyor (" << zipped.size() << " bayt)\n";
        return unzipped;
    }
};

// Basit (temsili) şifreleme: XOR + ters çevirme
class EncryptionDecorator : public DataSourceDecorator {
    static std::string encrypt(const std::string& plain, char key = '\x5A') {
        std::string out = plain;
        for (char& ch : out) ch ^= key;
        std::reverse(out.begin(), out.end());
        return out;
    }

    static std::string decrypt(const std::string& cipher, char key = '\x5A') {
        std::string out = cipher;
        std::reverse(out.begin(), out.end());
        for (char& ch : out) ch ^= key;
        return out;
    }

public:
    explicit EncryptionDecorator(std::unique_ptr<DataSource> src)
        : DataSourceDecorator(std::move(src)) {}

    void write(const std::string& data) override {
        auto enc = encrypt(data);
        std::cout << "EncryptionDecorator: şifreleniyor\n";
        wrappee->write(enc);
    }

    std::string read() const override {
        auto enc = wrappee->read();
        std::cout << "EncryptionDecorator: çözülüyor\n";
        return decrypt(enc);
    }
};

int main() {
    std::cout << "=== Decorator: Secure I/O ===\n";

    // Kaynak: Memory
    std::unique_ptr<DataSource> source = std::make_unique<MemoryDataSource>();

    // Sadece sıkıştırma
    std::unique_ptr<DataSource> compressed = std::make_unique<CompressionDecorator>(std::make_unique<MemoryDataSource>());
    compressed->write("aaaaabbbbccccccccccdd");
    std::cout << "Okunan (compress->decompress): " << compressed->read() << "\n\n";

    // Sadece şifreleme
    std::unique_ptr<DataSource> encrypted = std::make_unique<EncryptionDecorator>(std::make_unique<MemoryDataSource>());
    encrypted->write("Sifreli veri ici");
    std::cout << "Okunan (encrypt->decrypt): " << encrypted->read() << "\n\n";

    // Zincir: Sıkıştırma + Şifreleme (genelde tercih edilen sıra)
    std::unique_ptr<DataSource> pipeline = std::make_unique<CompressionDecorator>(
        std::make_unique<EncryptionDecorator>(
            std::make_unique<MemoryDataSource>()));

    const std::string payload = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz_top_secret_zzzzzzzzzzzz";
    pipeline->write(payload);
    auto restored = pipeline->read();

    std::cout << "Orijinal == Okunan ? " << (payload == restored ? "EVET" : "HAYIR") << "\n";

    // Basit: Kaynağa doğrudan yaz
    source->write("raw-data");
    std::cout << "Doğrudan okunan: " << source->read() << "\n";

    return 0;
}
