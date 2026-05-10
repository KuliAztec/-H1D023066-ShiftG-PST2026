1. 
- Arduino bertindak sebagai master.
- LCD I2C bertindak sebagai slave.
- Arduino mengirim data melalui jalur SDA.
- Jalur SCL digunakan sebagai sinkronisasi clock.
- Setiap perangkat I2C memiliki alamat unik, misalnya LCD biasanya menggunakan alamat 0x27 atau 0x3F.
- Arduino mengirimkan karakter atau perintah ke alamat LCD tersebut.
- Modul I2C backpack pada LCD menerjemahkan data serial menjadi sinyal paralel untuk LCD.

2. 
pin kiri dan kanan sebenarnya dapat dipertukarkan, tetapi efek pembacaannya akan terbalik.

3. 
```
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD dengan alamat I2C 0x27, 16 kolom, dan 2 baris
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Pin potensiometer
const int potPin = A0;

void setup() {
  // Memulai serial monitor
  Serial.begin(9600);

  // Memulai LCD
  lcd.init();
  lcd.backlight();
}

void loop() {
  // Membaca nilai ADC (0-1023)
  int adc = analogRead(potPin);

  // Konversi ke tegangan (5V)
  float volt = adc * (5.0 / 1023.0);

  // Konversi ke persen
  int persen = map(adc, 0, 1023, 0, 100);

  // Menampilkan ke Serial Monitor
  Serial.print("ADC: ");    Serial.print(adc);
  Serial.print(" | Volt: "); Serial.print(volt, 2);
  Serial.print("V | Persen: "); Serial.print(persen);
  Serial.println("%");

  // Update tampilan LCD
  lcd.clear();
  
  // Baris 1: Menampilkan ADC dan Persen
  lcd.setCursor(0, 0);
  lcd.print("ADC:");
  lcd.print(adc);
  lcd.setCursor(12, 0); // Menaruh persen di pojok kanan atas
  lcd.print(persen);
  lcd.print("%");

  // Baris 2: Membuat bar level (0-16 karakter)
  lcd.setCursor(0, 1);
  int barLength = map(adc, 0, 1023, 0, 16);
  for (int i = 0; i < barLength; i++) {
    lcd.print((char)255); // Karakter blok penuh
  }

  // Delay agar tampilan tidak terlalu cepat berkedip
  delay(300);
}

```
4.
| ADC | Volt (V) | Persen (%) |
| --- | -------- | ---------- |
| 1   | 0.00 V   | 0%         |
| 21  | 0.10 V   | 2%         |
| 49  | 0.24 V   | 4%         |
| 74  | 0.36 V   | 7%         |
| 96  | 0.47 V   | 9%         |
