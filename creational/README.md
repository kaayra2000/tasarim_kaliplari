# Oluşum Kalıpları (Creational Patterns)

**Oluşum kalıpları (Creational Patterns)**, nesne oluşturma mekanizmalarını soyutlayan ve bu süreci daha esnek ve yeniden kullanılabilir hale getiren tasarım kalıplarıdır. Bu kalıplar, "new" anahtar kelimesiyle doğrudan nesne oluşturmanın yerine geçen, daha kontrollü ve bakımı kolay muadiller sunar.

## Hangi Sorunları Çözer?

Oluşum kalıpları, yazılım geliştirme sürecinde karşılaşılan şu temel sorunlara çözüm getirir:

### 1. Karmaşık Nesne Oluşturma
Çok sayıda parametre alan veya karmaşık başlatma gerektiren nesnelerin oluşturulması kodun okunabilirliğini düşürür. Oluşum kalıpları bu süreci basitleştirir ve adım adım nesne inşa etmeyi sağlar.

### 2. Somut Sınıflara Bağımlılık
İstemci kodunun hangi somut sınıfın kullanılacağına karar vermesi, kodun esnek olmamasına ve değişikliklere karşı hassas hale gelmesine neden olur. Oluşum kalıpları, soyut arayüzler üzerinden çalışarak bu bağımlılığı azaltır.

### 3. Nesne Oluşturma Maliyeti
Bazı nesneler oluşturulurken yoğun kaynak tüketir (veritabanı bağlantısı, ağ bağlantısı, büyük veri yapıları). Oluşum kalıpları bu maliyeti optimize eder.

### 4. Tek Örnek Garantisi
Bazı durumlarda bir sınıfın birden fazla örneğinin olması mantık hatalarına veya kaynak israfına yol açabilir. Oluşum kalıpları bu kontrolü sağlar.

### 5. Ürün Ailelerinin Tutarlılığı
Birbiriyle uyumlu nesneler grubu oluşturulması gerektiğinde, uyumsuz nesnelerin bir arada kullanılması riskini önler.

## Oluşum Kalıplarının Türleri

### 1. [Singleton Pattern](./singleton/README.md)
**Sorun**: Bir sınıfın birden fazla örneğinin oluşturulması kaynak israfına veya tutarsızlığa yol açıyor.

**Çözüm**: Bir sınıfın yalnızca tek bir örneğinin olmasını garanti eder ve bu örneğe global erişim noktası sağlar.

**Kullanım Alanları**:
- Logger sınıfları
- Veritabanı bağlantı havuzları
- Konfigürasyon yöneticileri
- Cache mekanizmaları

**Örnek**: Bir uygulamada tek bir log dosyasına yazım yapılması gerekiyorsa, Logger sınıfının Singleton olarak tasarlanması tutarlı log kaydı sağlar.

### 2. [Factory Method Pattern](./factory_method/README.md)
**Sorun**: İstemci kodu, hangi somut sınıfın oluşturulacağına doğrudan karar veriyor ve bu da esnekliği azaltıyor.

**Çözüm**: Nesne oluşturma sorumluluğunu merkezi bir fabrikaya devreder. Hangi sınıfın oluşturulacağı runtime'da belirlenir.

**Kullanım Alanları**:
- Farklı dosya formatları için parser'lar (XML, JSON, CSV)
- Farklı veritabanı bağlantıları (MySQL, PostgreSQL, MongoDB)
- Farklı ödeme yöntemleri (Kredi Kartı, PayPal, Kripto)
- Platform bağımsız bileşenler

**Örnek**: Bir çizim uygulamasında "circle", "rectangle", "triangle" gibi string parametrelerine göre ilgili şekil nesnesini üreten ShapeFactory.

### 3. [Abstract Factory Pattern](./abstract_factory/README.md)
**Sorun**: Birbiriyle ilişkili nesneler grubu oluşturulurken uyumsuz kombinasyonlar oluşabilir.

**Çözüm**: Ürün aileleri (birbiriyle uyumlu nesneler grubu) oluşturmak için fabrika ailesi sağlar.

**Kullanım Alanları**:
- Çoklu platform GUI bileşenleri (Windows/Mac/Linux button, checkbox, window)
- Tema sistemleri (Modern/Klasik mobilya takımları)
- Veritabanı bağlantı ve sorgu nesneleri ailesi
- Oyun karakteri ekipman setleri (Savaşçı zırhı, kılıcı, kalkanı)

**Örnek**: Bir mobilya mağazası uygulamasında ModernFurnitureFactory modern sandalye ve masa üretirken, ClassicFurnitureFactory klasik sandalye ve masa üretir; karışık kombinasyon oluşmaz.

### 4. [Builder Pattern](./builder/README.md)
**Sorun**: Çok sayıda parametreli constructor'lar okunaksız ve hata yapmaya açık hale geliyor.

**Çözüm**: Karmaşık nesneleri adım adım oluşturmayı sağlar. Opsiyonel parametreler için esnek ve okunabilir bir API sunar.

**Kullanım Alanları**:
- Karmaşık yapılandırma nesneleri (sunucu konfigürasyonu)
- HTML/XML belge oluşturma
- Bilgisayar konfigürasyonu (CPU, RAM, Storage, GPU seçimi)
- SQL sorgu oluşturma
- HTTP request oluşturma

**Örnek**: Bir bilgisayar oluştururken `ComputerBuilder().setCPU("i7").setRAM(16).setStorage(512).build()` şeklinde zincirleme çağrılarla okunabilir kod yazma.

### 5. [Prototype Pattern](./prototype/README.md)
**Sorun**: Nesne oluşturma maliyeti yüksek veya çok sayıda benzer yapılandırma gerekiyor.

**Çözüm**: Mevcut nesneleri klonlayarak yeni nesneler üretir. Pahalı başlatma işlemlerini tekrar yapmadan kopya oluşturur.

**Kullanım Alanları**:
- Oyun karakteri kopyalama (aynı seviye, ekipman)
- Belge şablonları (Word, Excel şablonlarından yeni döküman)
- Grafik editörlerinde nesneleri kopyala-yapıştır
- Test verisi oluşturma (şablon veriden çoğaltma)
- Ağır I/O işlemi sonucu oluşan nesnelerin çoğaltılması

**Örnek**: Bir oyunda "Ork Savaşçı" şablon karakteri oluşturup, bu şablonu klonlayarak hızlıca birçok düşman ork oluşturma.

## Kalıplar Arası Farklar ve Seçim Rehberi

### Factory Method vs Abstract Factory
- **Factory Method**: Tek bir ürün türü için kullanılır (sadece şekiller veya sadece araçlar)
- **Abstract Factory**: Ürün aileleri için kullanılır (Modern mobilya seti: sandalye + masa + dolap)

### Builder vs Constructor
- **Constructor**: Sabit parametreli, basit nesneler için
- **Builder**: Çok parametreli, opsiyonel özellikli, karmaşık nesneler için

### Prototype vs New
- **New**: Nesne oluşturma hızlı ve maliyetsizse
- **Prototype**: Nesne oluşturma pahalıysa veya şablon kullanımı gerekiyorsa

### Singleton vs Static Class
- **Singleton**: Interface implementasyonu, geç başlatma (lazy), polimorfizm gerekirse
- **Static Class**: Sadece utility fonksiyonlar, durum tutmuyorsa

## En İyi Uygulamalar

### Ne Zaman Kullanmalı?

✅ **Kullan**:
- Nesne oluşturma süreci karmaşıksa
- İstemci kodunu somut sınıflardan izole etmek istiyorsanız
- Nesne oluşturma maliyeti yüksekse
- Çalışma zamanında hangi sınıfın kullanılacağı belirliyorsa
- Ürün aileleri tutarlılığı gerekiyorsa

❌ **Kullanma**:
- Basit nesneler için (over-engineering)
- Sadece 2-3 parametre alan basit constructor'lar için
- Performans kritik ve nesne sayısı çok fazla değilse (Singleton hariç)

### Dikkat Edilmesi Gerekenler

⚠️ **Singleton**:
- Thread-safety düşünülmeli
- Test edilebilirliği düşürebilir (DI kullanımı tercih edilebilir)
- Global state bağımlılığı oluşturabilir

⚠️ **Factory**:
- Yeni ürün tipi eklemek factory'nin değişmesini gerektirir
- Çok fazla ürün tipi varsa if-else veya switch karmaşıklaşabilir (registry pattern kullanılabilir)

⚠️ **Builder**:
- Basit nesneler için gereksiz karmaşıklık oluşturabilir
- Her nesne türü için ayrı builder sınıfı gerekebilir

⚠️ **Prototype**:
- Derin/sığ kopya farkını iyi anlamak gerekir
- Circular reference durumunda klonlama zorlaşır

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

## Özet

Oluşum kalıpları, yazılımın en temel işlemlerinden biri olan **nesne oluşturma** sürecini sistematik hale getirir. Doğru kullanıldığında:

- 📦 Kodun bakımını kolaylaştırır
- 🔧 Esnekliği artırır
- 🎯 Sorumlulukları net ayırır
- 🚀 Performansı optimize eder
- 🧪 Test edilebilirliği iyileştirir

Her kalıbın kendine özgü kullanım senaryosu vardır. Önemli olan doğru sorunu doğru kalıpla çözmek ve gereksiz komplekslikten kaçınmaktır.

## İleri Okuma

Tüm oluşum kalıpları için detaylı örnekler, diyagramlar ve çalıştırılabilir C++ kodlarına yukarıdaki bağlantılardan erişebilirsiniz. Her kalıbın kendi README'sinde:
- Detaylı açıklamalar
- Çalıştırılabilir kod örnekleri
- UML diyagramları
- Kullanım senaryoları
- Karşılaştırmalı analizler

bulunmaktadır.
