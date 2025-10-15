# Builder Pattern Nedir?

**Builder Pattern**, karmaşık nesneleri adım adım oluşturmak için kullanılan bir **oluşum kalıbıdır (creational pattern)**. Nesnenin tüm opsiyonları belirlendikten sonra inşa edilmesini sağlar. Çok sayıda seçimli parametre alan nesneler oluşturulurken kullanılır. Mesela, bir araba nesnesi oluştururken renk, motor türü, iç döşeme gibi birçok özellik seçilebilir.

## Ne İşe Yarar?

- **Karmaşık nesne oluşturma işini basitleştirir** - Çok parametreli constructor'lardan kurtarır
- **Adım adım nesne oluşturma** - CPU, RAM, Storage gibi bileşenleri tek tek ekleyebilirsiniz
- **Farklı temsiller** - Aynı yapım süreciyle farklı nesne türleri üretebilirsiniz (Gaming PC, Office PC)
- **Okunabilir kod** - `builder.buildCPU().buildRAM().build()` şeklinde zincirleme çağrılar vesilesiyle daha anlaşılır kod yazılır.

Örnekler

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
- **Basit:** Daha az kod, istemci (client) için kolay
- **Klasik:** Farklı sınıf oluşturma vakaları için Director kullanımı

Bilgisayar gibi çok bileşenli nesneler için idealdir. Kodunuz daha temiz ve bakımı kolay olur.