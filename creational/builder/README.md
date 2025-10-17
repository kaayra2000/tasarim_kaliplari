# Builder Pattern Nedir?

**Builder Pattern**, karmaşık nesneleri adım adım oluşturmak için kullanılan bir **oluşum kalıbıdır (creational pattern)**. Nesnenin tüm seçenekleri belirlendikten sonra inşa edilmesini sağlar. Çok sayıda seçimli parametre alan nesneler oluşturulurken kullanılır. Mesela, bir araba nesnesi oluştururken renk, motor türü, iç döşeme gibi birçok özellik seçilebilir.

## Ne İşe Yarar?

- **Karmaşık nesne oluşturma işini basitleştirir** - Çok parametreli yapıcılardan kurtarır
- **Adım adım nesne oluşturma** - CPU, RAM, Depolama gibi bileşenleri tek tek ekleyebilirsiniz
- **Farklı temsiller** - Aynı yapım süreciyle farklı nesne türleri üretebilirsiniz (Oyun PC'si, Ofis PC'si)
- **Okunabilir kod** - `builder.buildCPU().buildRAM().build()` şeklinde zincirleme çağrılar vesilesiyle daha anlaşılır kod yazılır.

## Örnekler

### 1. Basit Yaklaşım (Yönlendirici Yok)

![Basit Builder Pattern](./basic_computer/diagram.png)

```cpp
ComputerBuilder builder;
auto pc = builder.build()
```
**%90 durumda yeterli** - Doğrudan builder kullanımı, çağdaş C++ yaklaşımı.

### 2. Klasik Yaklaşım (Yönlendirici Var)

![Klasik Builder Pattern](./classic_computer/diagram.png)

```cpp
ComputerDirector director;
GamingComputerBuilder builder;
director.setBuilder(&builder);
auto pc = director.buildFullComputer();
```
**%10 durumda gerekli** - Farklı sınıf oluşturma durumları için `Director` sınıfı eklenmiş.

### 3. İki Yaklaşımın Karşılaştırması

![Builder Pattern Karşılaştırma](./basic_classic_diff/diagram.png)

İki yöntemin fayda/zararlarını görsel olarak gösterir:
- **Basit:** Daha az kod, istemci için kolay
- **Klasik:** Farklı sınıf oluşturma vakaları için Yönetici kullanımı

Bilgisayar gibi çok bileşenli nesneler için idealdir. Kodunuz daha temiz ve bakımı kolay olur.

## Nasıl Çalışır?

1. **Builder sınıfı:** Nesnenin bileşenlerini adım adım ekleyen yöntemler sunar
2. **Ürün (Product):** Oluşturulan karmaşık nesne (örn. Computer)
3. **Yönetici (opsiyonel):** Belirli bir yapım sırasını düzenler ve yönetir
4. **İstemci:** Builder'ı kullanarak ihtiyacı olan bileşenleri seçer ve nesneyi inşa eder

Builder genellikle zincirleme yöntemi (method chaining) ile kullanılır: `builder.setCPU("Intel").setRAM(16).build()`

## Ne Zaman Kullanılır?

- **Çok sayıda seçimli parametre varsa** – Yapıcıda 10+ parametre yerine builder kullanın
- **Nesne oluşturma adımları karmaşıksa** – Her bileşenin ayrı mantığı varsa
- **Farklı temsiller/yapılandırmalar üretilecekse** – Oyun PC'si, Ofis PC'si gibi varyasyonlar
- **Okunabilir ve bakımı kolay kod istiyorsanız** – Zincirleme çağrılar kodu anlaşılır yapar

## Ne Zaman Kullanılmaz?

- **Basit nesneler için** – Sadece 2-3 parametreli basit bir sınıfsa gereksizdir
- **Nesne yapısı nadiren değişiyorsa** – Statik bir yapıcı yeterli olabilir
- **Tek bir doğru yapım sırası varsa** – Normal yapıcı daha uygun
- **Performans kritikse** – Builder ekstra nesne oluşturma maliyeti getirir

## Diğer Oluşturma Kalıplarıyla Farkları

- **Factory Method / Abstract Factory:** Fabrikalar hangi nesnenin üretileceğine odaklanır. Builder ise tek bir karmaşık nesneyi nasıl inşa edeceğine odaklanır. Factory sınıf seçimi yapar, Builder adım adım bileşenleri birleştirir.

- **Prototype:** Mevcut bir nesneyi çoğaltıp değiştirir. Builder ise sıfırdan başlayarak adım adım yeni bir nesne inşa eder. Prototype varolan durumu kopyalar, Builder yeni durumu oluşturur.

- **Singleton:** Tek bir örnek temin eder. Builder ise her çağrıda farklı yapılandırmalarda yeni örnekler üretir. Singleton evrensel tek nesne için, Builder çok parametreli farklı nesneler için kullanılır.