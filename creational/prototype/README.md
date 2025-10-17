# Prototype Pattern Nedir?

**Prototype Pattern**, mevcut bir nesnenin kopyalanması (cloning) yoluyla yeni nesneler üretmeyi sağlayan bir **oluşum kalıbıdır (creational pattern)**. Yeni bir nesnenin oluşturulması pahalıysa veya çok sayıda kombinasyon/konfigürasyon varsa, mevcut bir örneği klonlayıp küçük değişikliklerle yeniden kullanmak daha verimli olabilir.

## Ne İşe Yarar?

- **Maliyetli oluşturmayı azaltır** – Ağır kurulum (I/O, büyük veri yükleme, karmaşık validasyon) gerektiren nesneleri bir kez oluşturup klonlayarak hız kazanırsınız.
- **Çalışma zamanında (runtime) çoğaltma** – Türünü bilmeden, yalnızca arayüz üzerinden polimorfik olarak kopyalayabilirsiniz.
- **Durum taşıyan nesneleri yeniden kullanma** – Varsayılan/şablon bir örnekten başlayıp küçük farklarla çoğaltma yaparsınız.
- **Derin/Sığ kopya kontrolü** – Kendi `clone()` implementasyonunuzla derin veya sığ kopyalama politikasını netleştirirsiniz.

## Örnekler

### 1. Basit Şekiller

![Basic Shape Prototype](./basic_shape/diagram.png)

Bu örnekte `Shape` taban sınıfı `clone()` ile klonlanır. Somut sınıflar (`Circle`, `Rectangle`) kendi durumlarını kopyalayarak yeni örnek döndürür.

```cpp
// Kullanım
std::unique_ptr<Shape> circle = std::make_unique<Circle>(10);
auto copy = circle->clone();
copy->moveTo(100, 50);
copy->draw();
```

### 2. Oyun Karakteri

![Game Character Prototype](./game_character/diagram.png)

Karakterlerin envanter, ekipman gibi bileşenleri olabilir. Klonlama sırasında bunların da uygun şekilde kopyalanması gerekir (genellikle derin kopya):

```cpp
// Örnek (fikir vermesi için)
std::unique_ptr<Character> base = std::make_unique<Rogue>("Ezio", 25);
auto assassin = base->clone(); // Derin kopya: envanter, silahlar kopyalanır
assassin->equip("Hidden Blade");
assassin->printStats();
```

### 3. Karşılaştırma Diyagramı

![Prototype Comparison](./game_shape_diff/diagram.png)

Şekil ve oyun karakteri örneklerinin farklı ihtiyaçlar (sığ/derin kopya) açısından karşılaştırmasını görselleştirir.

## Nasıl Çalışır

1. **Prototype Arayüzü**: `clone()` metodunu tanımlar (genellikle sanal/kopya yapıcı mantığıyla).
2. **Somut Prototipler**: Kendi alanlarını kopyalayarak yeni bir örnek üretir; derin/sığ kopya kararı burada verilir.
3. **İsteğe Bağlı Kayıt (Registry)**: Sık kullanılan prototipler bir haritada tutulur; anahtar ile `clone()` çağrılıp çoğaltılır.
4. **İstemci**: Somut sınıfı bilmeden, prototipten klon alır ve küçük değişiklikler uygular.

## Factory / Builder ile Farkı

- **Factory/Abstract Factory**: Nesneleri “başından” oluşturur, tür seçimini soyutlar.
- **Prototype**: Mevcut bir örneği kopyalar; hali hazırdaki durum (state) korunur ve ufak değişiklikler yapılır.
- **Builder**: Karmaşık nesneleri adım adım inşa eder; Prototype ise var olanı çoğaltır.

Uygulamada Prototype, bir factory kayıt defteriyle birlikte sık kullanılır: önce prototip şablonları kayıt edilir, sonra `clone()` ile istenen varyasyon hızlıca üretilir.
