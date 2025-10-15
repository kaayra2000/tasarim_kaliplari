# Abstract Factory Pattern Nedir?

**Abstract Factory Pattern**, birbiriyle ilişkili veya bağımlı nesneler ailesi oluşturmak için kullanılan bir **oluşum kalıbıdır (creational pattern)**. İstemci kodu somut sınıflara bağlı kalmadan ürün aileleri (mesela Modern mobilya takımı, Windows GUI bileşenleri) oluşturabilir. Farklı platformlar veya temalar için tutarlı ürün takımları üretilmesi gereken durumlarda idealdir.

## Ne İşe Yarar?

- **Ürün ailelerini bir arada yönetir** - Birbirleriyle uyumlu birden fazla nesne (örn. sandalye + masa, buton + checkbox) aynı fabrika üzerinden üretilir
- **Platform bağımsızlığı** - Windows, Mac veya Linux gibi farklı platformlar için GUI bileşenleri üretirken istemci kodu değişmez
- **Tutarlılık garantisi** - Aynı fabrikadan üretilen tüm ürünler birbiriyle uyumludur (Modern fabrikadan klasik ürün çıkmaz)
- **Genişletilebilirlik** - Yeni bir ürün ailesi eklemek için sadece yeni bir fabrika sınıfı oluşturulur

## Örnekler

### 1. Mobilya Fabrikası

![Furniture Factory](./furniture/diagram.png)

Bu örnekte `ModernFurnitureFactory` ve `ClassicFurnitureFactory` kullanılarak Modern veya Klasik mobilya takımları oluşturulur. Her fabrika kendi takımında sandalye ve masa üretir.

```cpp
// Kullanım
std::unique_ptr<FurnitureFactory> factory = std::make_unique<ModernFurnitureFactory>();
auto chair = factory->createChair();
auto table = factory->createTable();
chair->sitOn();
table->use();
```

### 2. GUI Bileşenleri Fabrikası

![GUI Factory](./gui/diagram.png)

Bu örnek, `WindowsFactory`, `MacFactory` ve `LinuxFactory` ile farklı platformlar için GUI bileşenleri (Button, Checkbox) oluşturur. Her platform kendi görsel tarzına sahip bileşenler üretir.

```cpp
// Örnek
std::unique_ptr<GUIFactory> factory = std::make_unique<WindowsFactory>();
Application app(*factory);
app.render();
app.interact();
```

### 3. İki Örneğin Karşılaştırması

![Abstract Factory Comparison](./gui_furniture_diff/diagram.png)

GUI ve Mobilya örneklerinin farklı kullanım senaryolarını ve benzerliklerini görsel olarak gösterir:
- **GUI:** Platform bağımsız arayüz bileşenleri
- **Mobilya:** Stil tutarlılığı gerektiren ürün takımları

## Nasıl Çalışır

1. **Soyut Fabrika Arayüzü:** Tüm ürünleri oluşturacak metotları tanımlar
2. **Somut Fabrikalar:** Her ürün ailesi için özel fabrika (ModernFactory, WindowsFactory vb.)
3. **Soyut Ürünler:** Ürün ailelerinin ortak arayüzleri (Chair, Button vb.)
4. **Somut Ürünler:** Her fabrikaya özgü ürün implementasyonları (ModernChair, WindowsButton vb.)

İstemci kodu sadece soyut fabrika ve soyut ürünlerle çalışır. Bu sayede somut sınıflara bağımlılık olmaz ve runtime'da farklı ürün aileleri kolayca değiştirilebilir.

## Factory Method ile Farkı

- **Factory Method:** Tek bir ürün türü oluşturur (örn. sadece Button)
- **Abstract Factory:** Birbirleriyle ilişkili birden fazla ürün oluşturur (Button + Checkbox + TextField)

Abstract Factory, aslında birden fazla Factory Method'un bir araya getirilmiş halidir. Her ürün türü için bir factory method içerir ve tüm ürünlerin tutarlı bir aileden olmasını temin eder.
