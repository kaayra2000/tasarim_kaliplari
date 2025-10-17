# Oluşum Kalıpları (Creational Patterns)

**Oluşum kalıpları (Creational Patterns)**, nesne oluşturma mekanizmalarını soyutlayan ve bu süreci daha esnek, yeniden kullanılabilir hale getiren tasarım kalıplarıdır. Kalıplar arasında Singleton, Factory Method, Abstract Factory, Builder ve Prototype bulunur. Temel amaçları, nesne oluşturma sürecini istemciden ayırmak ve kodun bağımlılığını azaltmaktır.

## Kalıp Türleri

### 1. [Singleton Pattern](./singleton/README.md)
Bir sınıfın yalnızca tek bir örneğinin olmasını garanti eder ve global erişim noktası sağlar.

**Kullanım Alanları**:
- Logger sınıfları
- Veritabanı bağlantı havuzları
- Konfigürasyon yöneticileri
- Cache mekanizmaları

**Örnek**: Bir uygulamada tek bir log dosyasına yazım yapılması gerekiyorsa, Logger sınıfının Singleton olarak tasarlanması tutarlı log kaydı sağlar.

### 2. [Factory Method Pattern](./factory_method/README.md)
Nesne oluşturma sorumluluğunu merkezi bir fabrikaya devreder. Hangi sınıfın oluşturulacağı runtime'da belirlenir.

**Kullanım Alanları**:
- Farklı dosya formatları için parser'lar (XML, JSON, CSV)
- Farklı veritabanı bağlantıları (MySQL, PostgreSQL, MongoDB)
- Farklı ödeme yöntemleri (Kredi Kartı, PayPal, Kripto)
- Platform bağımsız bileşenler

**Örnek**: Bir çizim uygulamasında "circle", "rectangle", "triangle" gibi string parametrelerine göre ilgili şekil nesnesini üreten `ShapeFactory`.

### 3. [Abstract Factory Pattern](./abstract_factory/README.md)
Ürün aileleri (birbiriyle uyumlu nesneler grubu) oluşturmak için fabrika ailesi sağlar.

**Kullanım Alanları**:
- Çoklu platform GUI bileşenleri (Windows/Mac/Linux button, checkbox, window)
- Tema sistemleri (Modern/Klasik mobilya takımları)
- Veritabanı bağlantı ve sorgu nesneleri ailesi
- Oyun karakteri ekipman setleri (Savaşçı zırhı, kılıcı, kalkanı)

**Örnek**: Bir mobilya mağazası uygulamasında `ModernFurnitureFactory` modern sandalye ve masa üretirken, `ClassicFurnitureFactory` klasik sandalye ve masa üretir; karışık kombinasyon oluşmaz.

### 4. [Builder Pattern](./builder/README.md)
Karmaşık nesneleri adım adım oluşturmayı sağlar. Opsiyonel parametreler için esnek ve okunabilir bir API sunar.

**Kullanım Alanları**:
- Karmaşık yapılandırma nesneleri (sunucu konfigürasyonu)
- HTML/XML belge oluşturma
- Bilgisayar konfigürasyonu (CPU, RAM, Storage, GPU seçimi)
- SQL sorgu oluşturma
- HTTP request oluşturma

**Örnek**: Bir bilgisayar oluştururken `ComputerBuilder().setCPU("i7").setRAM(16).setStorage(512).build()` şeklinde zincirleme çağrılarla okunabilir kod yazma.

### 5. [Prototype Pattern](./prototype/README.md)
Mevcut nesneleri klonlayarak yeni nesneler üretir. Pahalı başlatma işlemlerini tekrar yapmadan kopya oluşturur.

**Kullanım Alanları**:
- Oyun karakteri kopyalama (aynı seviye, ekipman)
- Belge şablonları (Word, Excel şablonlarından yeni döküman)
- Grafik editörlerinde nesneleri kopyala-yapıştır
- Test verisi oluşturma (şablon veriden çoğaltma)
- Ağır I/O işlemi sonucu oluşan nesnelerin çoğaltılması

**Örnek**: Bir oyunda "Ork Savaşçı" şablon karakteri oluşturup, bu şablonu klonlayarak hızlıca birçok düşman ork oluşturma.

## Kalıplar Arası Farklar ve Seçim Rehberi

### Factory Method vs Abstract Factory
- **Factory Method**: Tek bir ürün türü için (sadece şekiller veya sadece araçlar)
- **Abstract Factory**: Ürün aileleri için (Modern mobilya seti: sandalye + masa + dolap)

### Builder vs Constructor
- **Constructor**: Sabit parametreli, basit nesneler
- **Builder**: Çok parametreli, opsiyonel özellikli, karmaşık nesneler

### Prototype vs New
- **New**: Nesne oluşturma hızlı ve maliyetsizse
- **Prototype**: Nesne oluşturma pahalıysa veya şablon kullanımı gerekiyorsa

### Singleton vs Static Class
- **Singleton**: Interface implementasyonu, geç başlatma (lazy), polimorfizm gerekirse
- **Static Class**: Sadece utility fonksiyonlar, durum tutmuyorsa

## Sık Yapılan Hatalar

### ❌ Singleton'ı Her Yerde Kullanmak
**Hata**: Her sınıfı Singleton yapmak (global state anti-pattern)
```cpp
// YANLIŞ: Gereksiz Singleton kullanımı
class Calculator {
    static Calculator* instance;
    // ...
};
```
**Doğru**: Sadece gerçekten tek örnek olması gereken sınıflar için kullanın.

### ❌ Factory'yi Basit Nesneler İçin Kullanmak
**Hata**: 2-3 parametreli basit nesneler için factory yazmak (over-engineering)
```cpp
// YANLIŞ: Gereksiz factory
UserFactory::createUser(name, email); // Sadece new User(name, email) yeterli
```
**Doğru**: Karmaşık oluşturma mantığı veya runtime tip belirleme gerektiğinde kullanın.

### ❌ Builder'da Zorunlu Parametreleri Kontrol Etmemek
**Hata**: `build()` çağrıldığında gerekli alanların eksik olması
```cpp
// YANLIŞ: CPU olmadan Computer oluşturulabilir
Computer* pc = ComputerBuilder().setRAM(16).build(); // CPU yok!
```
**Doğru**: Zorunlu parametreleri constructor'da alın veya `build()` metodunda kontrol edin.

### ❌ Prototype'da Derin Kopyayı Unutmak
**Hata**: Shallow copy yaparak pointer'ları paylaşmak
```cpp
// YANLIŞ: Shallow copy
Character* clone() {
    return new Character(*this); // inventory pointer'ı paylaşılıyor!
}
```
**Doğru**: Deep copy yaparak bağımsız nesneler oluşturun.

### ❌ Abstract Factory'de Ürün Uyumluluğunu Sağlamamak
**Hata**: Farklı fabrikalardan gelen uyumsuz ürünleri karıştırmak
```cpp
// YANLIŞ: Modern sandalye + Klasik masa
Chair* chair = modernFactory->createChair();
Table* table = classicFactory->createTable(); // Uyumsuz!
```
**Doğru**: Aynı fabrikadan tüm ürünleri alın.

### ❌ Thread-Safety'yi Göz Ardı Etmek (Singleton)
**Hata**: Multi-threaded ortamda thread-safe olmayan Singleton
```cpp
// YANLIŞ: Race condition var
Singleton* Singleton::getInstance() {
    if (!instance) instance = new Singleton(); // Tehlikeli!
    return instance;
}
```
**Doğru**: Double-checked locking veya C++11 static initialization kullanın.

## Gerçek Dünya Örnekleri

### Singleton: Spring Framework ApplicationContext
Spring'de ApplicationContext, Singleton olarak tasarlanmıştır. Tüm uygulama boyunca tek bir context instance'ı kullanılır.

### Factory Method: JDBC DriverManager
`DriverManager.getConnection()` farklı veritabanı sürücüleri için Connection nesneleri üretir.

### Abstract Factory: Java Swing UIManager
Farklı Look and Feel'ler için tutarlı GUI bileşenleri sağlar (Metal, Windows, Motif).

### Builder: StringBuilder, HttpClient
Java'daki `StringBuilder` ve modern `HttpClient` builder pattern kullanır.

### Prototype: Object.clone() / Copy Constructor
Java'nın `Cloneable` interface'i ve `clone()` metodu prototype pattern'in uygulamasıdır.
