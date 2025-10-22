# cloud_streaming

Yerel ses oynatıcıyı bulut akış servisine uyarlayan Adapter örneği.

# Derleyip Çalıştırma

Bu klasördeyken:

```bash
g++ -std=c++17 code.cpp -o app
./app
```

# Beklenen Çıktı

```text
=== Yerel Şarkı ===
LocalAudioPlayer: 'lofi-beats.mp3' dosyası çalınıyor

=== Çevrimiçi Şarkı ===
StreamingAdapter: Bulut akışına hazırlanılıyor
CloudStreamingService: eu-central-1 sunucusuna bağlanılıyor
CloudStreamingService: Kullanıcı kimliği doğrulandı -> token-42
CloudStreamingService: 'uptempo-sax' adlı parça yayınlanıyor
CloudStreamingService: Akış durduruldu

=== Paylaşılan Arayüz ===
StreamingAdapter: Bulut akışına hazırlanılıyor
CloudStreamingService: eu-central-1 sunucusuna bağlanılıyor
CloudStreamingService: Kullanıcı kimliği doğrulandı -> token-42
CloudStreamingService: 'lofi-beats.mp3' adlı parça yayınlanıyor
CloudStreamingService: Akış durduruldu
```