# Builder Pattern Nedir?

**Builder Pattern**, karmaşık nesneleri adım adım oluşturmak için kullanılan bir **creational (oluşum) tasarım kalıbıdır** Nesnenin tüm opsiyonları belirlendikten sonra inşa edilmesini sağlar .

## Ne İşe Yarar?

- **Karmaşık construction'ları basitleştirir** - Çok parametreli constructor'lardan kurtarır **Adım adım nesne oluşturma** - CPU, RAM, Storage gibi bileşenleri tek tek ekleyebilirsiniz
- **Farklı temsiller** - Aynı construction süreciyle farklı nesne tipleri üretebilirsiniz (Gaming PC, Office PC) **Okunabilir kod** - `builder.buildCPU().buildRAM().build()` şeklinde zincirleme çağrılar Örneklere Göre:

### 1. Basit Yaklaşım (Director Yok)

![Basit Builder Pattern](./basic_computer/diagram.png)

```cpp
ComputerBuilder builder;
auto pc = builder.build()
```
**%90 durumda yeterli** - Doğrudan builder kullanımı, modern C++ yaklaşımı.

### 2. Klasik Yaklaşım (Yönlendirici Var)

![Klasik Builder Pattern](./classic_computer/diagram.png)

```cpp
ComputerDirector director;
GamingComputerBuilder builder;
director.setBuilder(&builder);
auto pc = director.buildFullComputer();
```
**%10 durumda gerekli** - Farklı construction stratejileri için Director sınıfı eklenmiş.

### 3. **basic_classic_diff/** - İki Yaklaşımın Karşılaştırması

![Builder Pattern Karşılaştırma](./basic_classic_diff/diagram.png)

İki yöntemin avantaj/dezavantajlarını görsel olarak gösterir:
- **Basit:** Daha az kod, client için kolay
- **Klasik:** Farklı construction senaryoları için Director kullanımı

**Sonuç:** Bilgisayar gibi çok bileşenli nesneler için idealdir Kodunuz daha temiz ve bakımı kolay olur.