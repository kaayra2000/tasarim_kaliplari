# Tasarım Kalıpları (Design Patterns)

Bu depo, yazılım tasarım kalıplarına (design patterns) dair örnekleri ve kısa açıklamaları içerir. Tasarım kalıpları, sık karşılaşılan yazılım tasarım sorunlarını tekrar kullanılabilir, sınanabilir ve iyi tanımlanmış çözümler sunar.

## Tasarım kalıpları nedir?

Tasarım kalıpları, tecrübeye dayanan, tekrar eden tasarım sorunlarına uygulanabilecek sınıflandırılmış çözümlerdir. Bir sorunu nasıl çözeceğinizi adım adım anlatmak yerine; nesnel, yeniden kullanılabilir yapı taşları sunar. Kalıplar, uygulama mantığını değil, yapısal ve davranışsal yaklaşımları soyutlar.

## Ne işe yarar?

- Hızlı çözüm: Bilinen sorunlara hazır yaklaşımlar sunar, tasarım kararlarını hızlandırır.
- İletişim: Takım içinde ortak bir dil oluşturur ("Singleton kullandık", "Strategy uygula").
- En iyi uygulamalar: Denenmiş çözümleri teşvik eder; ters kalıplardan (anti-pattern) kaçınmaya yardımcı olur.

## Kısa vadeli faydaları

- Hızlı çözüm ve karar verme.
- Kodun belli görevler için daha net ayrılması (sorumlulukların bölünmesi).
- Yeni geliştiricilerin mevcut mimariyi anlamasını kolaylaştırır.

## Uzun vadeli faydaları

- Bakım kolaylığı: Kod yeniden yapılandırılırken hata tehlikesi azalır.
- Genişleyebilirlik: Yeni özellikler eklenirken mevcut katmanlara zarar verme olasılığı düşer.
- Yeniden kullanım: Benzer sorunlar için tekrar kullanılabilecek güvenli soyutlamalar sunar.

## Kod okunaklılığı ve genişleyebilirlik

Tasarım kalıpları doğru uygulandığında kodun okunaklığı artar çünkü belirli rollere sahip sınıf/nesne yapıları standartlaşır. Bu, kodu okuyan kişinin hangi sorumluluğun nerede olduğunu hızlıca anlamasına vesile olur. Ayrıca kalıplar genellikle açık arabirimler (interfaces) ve gevşek bağlılık (loose coupling) önerdiği için yeni davranışlar eklemek veya mevcutları değiştirmek kolaylaşır.

Önemli noktalar:
- Aşırı kullanımdan kaçının (aşırı mühendislik):
Bu hataya birçok mühendis düşmektedir. Tam olarak hata sayılmasa da, gereksiz yere karmaşık yapılar oluşturulması işlemidir.
- Önce basit yazın, ihtiyaç doğarsa kalıp uygulayın.

## Tasarım kalıplarının türleri

Genel olarak üç ana başlık vardır:

- **[Oluşum Kalıpları (Creational Patterns)](./creational/README.md)**:
	- Nesne oluşturma süreçlerini soyutlar. Nesne oluşturmayı merkezi hale getirerek esneklik sunar.
	- Örnekler: [Singleton](./creational/singleton/README.md), [Abstract Factory](./creational/abstract_factory/README.md), [Builder](./creational/builder/README.md), [Factory Method](./creational/factory_method/README.md), [Prototype](./creational/prototype/README.md).

- Yapı Kalıpları (Structural Patterns):
	- Sınıfların ve nesnelerin bileşimini düzenler; daha büyük yapıların oluşturulmasını kolaylaştırır.
	- Örnekler: [Adapter](./structural/adapter/README.md), [Decorator](./structural/decorator/README.md), [Facade](./structural/facade/README.md), Composite, Bridge.

- Davranış Kalıpları (Behavioral Patterns):
	- Nesneler arası iletişim ve sorumlulukların dağılımına odaklanır.
	- Örnekler: Observer, Strategy, Command, Iterator, State, Chain of Responsibility.

Daha ayrıntılı örnekler ve açıklamalar için ilgili kalıbın isminin üzerine tıklayabilirsiniz. Bunun yanında dizinlerde gezinerek örnek kodları ve diyagramları inceleyebilirsiniz.