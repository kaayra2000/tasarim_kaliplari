# Tasarım Kalıpları (Design Patterns)

Bu depo, yazılım tasarım kalıplarına (design patterns) dair örnekleri ve kısa açıklamaları içerir. Tasarım kalıpları, sık karşılaşılan yazılım tasarım problemlerine tekrar kullanılabilir, test edilebilir ve iyi tanımlanmış çözümler sunar.

## Tasarım kalıpları nedir?

Tasarım kalıpları, tecrübeye dayanan, tekrar eden tasarım problemlerine uygulanabilecek sınıflandırılmış çözümlerdir. Bir problemi nasıl çözeceğinizi adım adım anlatmak yerine; objektif, yeniden kullanılabilir yapı taşları sunar. Kalıplar, uygulama mantığını değil, yapısal ve davranışsal yaklaşımları soyutlar.

## Ne işe yarar?

- Hızlı çözüm: Bilinen sorunlara hazır yaklaşımlar sağlar, tasarım kararlarını hızlandırır.
- İletişim: Takım içinde ortak bir dil oluşturur ("Singleton kullandık", "Strategy uygula").
- En iyi uygulamalar: Denenmiş çözümleri teşvik eder; anti-pattern'lerden kaçınmaya yardımcı olur.

## Kısa vadeli faydaları

- Hızlı prototipleme ve karar verme.
- Kodun belli görevler için daha net ayrılması (sorumlulukların bölünmesi).
- Yeni geliştiricilerin mevcut mimariyi anlamasını kolaylaştırır.

## Uzun vadeli faydaları

- Bakım kolaylığı: Kod yeniden yapılandırılırken hata riski azalır.
- Genişleyebilirlik: Yeni özellikler eklenirken mevcut katmanlara zarar verme olasılığı düşer.
- Yeniden kullanım: Benzer problemler için tekrar kullanılabilecek güvenli soyutlamalar sağlar.

## Kod okunaklılığı ve genişleyebilirlik

Tasarım kalıpları doğru uygulandığında kodun okunaklığı artar çünkü belirli rollere sahip sınıf/nesne yapıları standartlaşır. Bu, kodu okuyan kişinin hangi sorumluluğun nerede olduğunu hızlıca anlamasını sağlar. Ayrıca kalıplar genellikle açık arabirimler (interfaces) ve gevşek bağlılık (loose coupling) önerdiği için yeni davranışlar eklemek veya mevcutları değiştirmek kolaylaşır.

Önemli noktalar:
- Aşırı kullanımdan kaçının (over-engineering).
- Önce basit yazın, ihtiyaç doğarsa kalıp uygulayın.

## Tasarım kalıplarının türleri

Genel olarak üç ana kategori vardır:

- Creational (Yaratıcı) Kalıplar:
	- Nesne oluşturma süreçlerini soyutlar. Nesne yaratmayı merkezi hale getirerek esneklik sağlar.
	- Örnekler: Singleton, Factory Method, Abstract Factory, Builder, Prototype.

- Structural (Yapısal) Kalıplar:
	- Sınıfların ve nesnelerin bileşimini düzenler; daha büyük yapıların oluşturulmasını kolaylaştırır.
	- Örnekler: Adapter, Decorator, Facade, Composite, Bridge.

- Behavioral (Davranışsal) Kalıplar:
	- Nesneler arası iletişim ve sorumlulukların dağılımına odaklanır.
	- Örnekler: Observer, Strategy, Command, Iterator, State, Chain of Responsibility.

Bu depoda dizinler bu kategorileri yansıtır: `creational/`, `structural/`, `behavioral/`.