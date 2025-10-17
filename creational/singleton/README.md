# Singleton Pattern Nedir?

**Singleton Pattern**, bir sınıfın yalnızca tek bir örneğe (instance) sahip olmasını ve bu örneğe evrensel bir erişim noktası sunulmasını sağlayan bir **oluşum kalıbıdır (creational pattern)**. Konfigürasyon, logger, cache gibi tekil servislerin uygulama genelinde paylaşıldığı senaryolarda kullanılır.

## Ne İşe Yarar?

- **Tek örnek** – Uygulama boyunca bir sınıfın en fazla bir örneği bulunur.
- **Evrensel erişim** – `getInstance()`/`instance()` üzerinden aynı nesneye ulaşılır.
- **Kaynak paylaşımı** – Dosya/log yazımı, ayarlar gibi paylaşılan bileşenler için uygundur.

Ancak dikkat: Gereksiz evrensel durum (state) bağımlılığı oluşturabilir. Test edilebilirliği düşürmemek için kullanım alanını dar tutun.

## Örnekler

### 1) Basit (Lazy) Singleton – Thread-Safe değil

![Lazy Singleton](./basic_lazy/diagram.png)

```cpp
// Kullanım
Logger& logger = Logger::getInstance();
logger.log("Uygulama başladı");
```

Bu örnekte instance ilk istendiğinde oluşturulur (lazy initialization). Çok iş parçacığında (multi-thread) yarış koşulu riski vardır.

### 2) Thread-Safe Singleton (Meyers Singleton)

![Thread-Safe Singleton](./thread_safe/diagram.png)

```cpp
// Kullanım
Logger& logger = Logger::getInstance();
logger.log("Thread-safe loglama");
```

Bu örnek C++11 ve sonrası için yerel statik değişken başlatmanın thread-safe garantisinden yararlanır.

### 3) İki Yaklaşımın Karşılaştırması

![Lazy vs Thread-Safe](./basic_threadsafe_diff/diagram.png)

- **Lazy (basit):** Uygulaması kolaydır, fakat çok iş parçacıklı ortamlarda güvenli değildir.
- **Meyers (thread-safe):** Çağdaş C++’ta güvenli ve yalın bir yaklaşımdır.

## Nasıl Çalışır

1. Kurucu gizlenir (private) ve kopyalama devre dışı bırakılır.
2. Sınıf kendi içinde tek örneği üretir ve saklar.
3. İstemci, sağlanan statik yöntemle aynı örneğe erişir.

## Ne Zaman Kullanılır / Kullanılmaz?

- Kullan: Gerçekten tek bir paylaşılan kaynak/servis olması gerekiyorsa (örn. loglayıcı, merkezi ayarlar).
- Kaçın: Her yerde erişilebilir evrensel durum testleri zorlaştırıyorsa; çoğu durumda açık bağımlılık enjeksiyonu tercih edilmelidir.
