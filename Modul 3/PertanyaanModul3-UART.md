1) Jelaskan proses dari input keyboard hingga LED menyala/mati!
2) Mengapa digunakan Serial.available() sebelum membaca data? Apa yang terjadi jika baris tersebut dihilangkan?
3) Modifikasi program agar LED berkedip (blink) ketika menerima input '2' dengan kondisi jika ‘2’ aktif maka LED akan terus berkedip sampai perintah selanjutnya diberikan dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!
4) Tentukan apakah menggunakan delay() atau milis()! Jelaskan pengaruhnya terhadapsistem


# Jawaban

1. 
- Pengguna mengetik karakter pada Serial Monitor Arduino IDE
- Data dikirim dari komputer.
- Arduino menerima data serial melalui pin RX.
- Program memeriksa apakah terdapat data masuk
- Program melakukan pengecekan kondisi
- LED berubah kondisi sesuai perintah yang diterima melalui UART.
2. 
Fungsi Serial.available() digunakan untuk memeriksa apakah terdapat data yang tersedia di buffer serial sebelum data dibaca.  
Jika baris tersebut dihilangkan, arduino tetap mencoba membaca data meskipun buffer kosong. `Serial.read()` dapat menghasilkan nilai -1.
3. 

```
// Pin LED
const int ledPin = 13; 

// Variabel kontrol
char mode = '0'; 
bool ledState = LOW;

// Variabel timer blink
unsigned long previousMillis = 0; 
const long interval = 500; 

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // 1. Cek input Serial
  if (Serial.available() > 0) {
    mode = Serial.read();

    // Reset status LED jika pindah dari mode blink ke mode statis
    if (mode == '1') {
      digitalWrite(ledPin, HIGH);
    } 
    else if (mode == '0') {
      digitalWrite(ledPin, LOW);
    }
  }

  // 2. Logika Mode Blink (Mode '2')
  if (mode == '2') {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      ledState = !ledState; // Balik kondisi (toggle)
      digitalWrite(ledPin, ledState);
    }
  }
}
```
4. 
Program lebih baik menggunakan millis() dibandingkan delay(). KArena millis() bersifat non-blocking dan arduino tetap dapat membaca input serial saat LED berkedip.