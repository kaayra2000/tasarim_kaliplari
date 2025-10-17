# Factory Pattern Nedir?

**Factory Pattern**, nesne oluşturma sorumluluğunu merkezi bir fabrikaya (factory) vererek istemci kodunun somut sınıflara doğrudan bağlılığını azaltan bir **oluşum kalıbıdır (creational pattern)**. Hangi tür nesne oluşturulacağı runtime'da belirlendiğinde kullanılır. Mesela, farklı veritabanı bağlantıları veya farklı ödeme yöntemleri oluşturmak için idealdir.

## Ne İşe Yarar?

- **Sınıf oluşturmayı soyutlar** - İstemci sadece bir tür veya isimle nesne ister, hangi somut sınıfın üretileceğini bilmez.
- **Yeni ürün tipi eklemeyi kolaylaştırır** - Yeni bir somut ürün eklemek genellikle fabrikanın güncellenmesiyle sınırlıdır.
- **Bellek yönetimi ve akıllı işaretçilerle uyumlu** - Fabrika, ownership kurallarını merkezi olarak uygulayabilir.

## Örnekler

### 1. Basit string-tabanlı fabrika

![Basic Shape Factory](./basic_shape/diagram.png)

Bu örnekte `ShapeFactory::createShape("circle")` gibi çağrılar somut `Circle`, `Rectangle`, `Triangle` nesnelerini döndürür.

```cpp
// Kullanım
Shape* shape = ShapeFactory::createShape("circle");
shape->draw();
```

### 2. Daha gelişmiş fabrika

![Vehicle Factory](./vehicle/diagram.png)

Bu örnek, `VehicleFactory` ile `Car`, `Motorcycle`, `Truck` gibi somut sınıfları güvenli şekilde üretir. Hem enum hem de string tabanlı oluşturucu gösterilmiştir.

```cpp
// Örnek
auto car = VehicleFactory::createVehicle(VehicleType::CAR, "BMW", 2023, 1500000, 4);
car->displayInfo();
```

### İki yaklaşımın karşılaştırması

![Factory Comparison](./vehicle_shape_diff/diagram.png)

Farklı factory yaklaşımlarının fayda/zararlarını gösterir.

## Nasıl Çalışır?

Fabrika, istemciden aldığı bir anahtar (string, enum veya yapılandırma) ile hangi somut sınıfın üretileceğine karar verir ve nesneyi soyut bir sınıf olarak döndürür. Böylece istemci, somut sınıfın ayrıntılarına bağlı kalmadan davranışları kullanabilir.

1. **Factory metodu:** Bir anahtar (string, enum) alır ve uygun somut sınıfı üretir
2. **Soyut ürün:** Tüm somut ürünlerin paylaştığı arayüz veya taban sınıf
3. **Somut ürünler:** Factory'nin ürettiği gerçek sınıflar (Circle, Car, vb.)
4. **İstemci:** Sadece factory ve soyut ürünle çalışır, somut sınıfları bilmez

## Ne Zaman Kullanılır?

- **Hangi sınıfın oluşturulacağı runtime'da belli oluyorsa** – Kullanıcı girişi, config dosyası, veritabanı
- **Yeni ürün tipleri sık ekleniyorsa** – Sadece factory'yi güncellemeniz yeterli
- **İstemci kodunu somut sınıflardan ayırmak istiyorsanız** – Bağımlılığı azaltır
- **Nesne yaratma mantığı merkezi olmalıysa** – Tekrar kullanım ve tutarlılık

## Ne Zaman Kullanılmaz?

- **Sadece bir veya iki somut sınıf varsa** – Gereksiz soyutlama oluşturur
- **Ürün tipleri hiç değişmiyorsa** – Doğrudan `new Circle()` daha basittir
- **Performans çok kritikse** – Factory ekstra indirection getirir
- **Ürünler arası ilişki varsa** – O zaman Abstract Factory kullanın

## Diğer Oluşturma Kalıplarıyla Farkları

- **Abstract Factory:** Factory Method tek bir ürün türü oluşturur. Abstract Factory ise birbirleriyle ilişkili birden fazla ürünü bir arada üretir (ürün ailesi). Abstract Factory içinde birden fazla Factory Method bulunur.

- **Builder:** Factory Method hangi sınıfın üretileceğine karar verir. Builder ise tek bir karmaşık nesneyi adım adım nasıl inşa edeceğini belirler. Factory tür seçimi, Builder bileşen kombinasyonu içindir.

- **Prototype:** Factory Method her seferinde sıfırdan yeni nesne üretir. Prototype ise mevcut bir nesneyi klonlar. Factory "yarat", Prototype "kopyala" mantığıyla çalışır.

- **Singleton:** Factory Method her çağrıda yeni nesne döndürebilir. Singleton ise her zaman aynı tek örneği döndürür. Factory çeşitlilik, Singleton teklik içindir.