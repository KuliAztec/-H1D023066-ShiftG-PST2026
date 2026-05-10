1. Apa fungsi perintah analogRead() pada rangkaian praktikum ini?
2. Mengapa diperlukan fungsi map() dalam program tersebut?
3. Modifikasi program berikut agar servo hanya bergerak dalam rentang 30° hingga 150°, meskipun potensiometer tetap memiliki rentang ADC 0–1023. Jelaskan program pada fill

#  Jawaban

1.  Fungsi analogRead() digunakan untuk membaca nilai tegangan analog dari potensiometer yang terhubung ke pin analog Arduino.  
2.  Fungsi map() digunakan untuk mengubah rentang nilai ADC menjadi rentang sudut servo.  
Nilai ADC dari potensiometer 0 sampai 1023  
Sedangkan servo menggunakan sudut 0° sampai 180°  
3. 
```
#include <Servo.h>

// Membuat objek servo
Servo myservo;

// Definisi Pin
const int potPin = A0;
const int servoPin = 9;

// Variabel
int adcValue;
int angle;

void setup() {
  // Menghubungkan servo ke pin D9
  myservo.attach(servoPin);
  
  // Memulai serial monitor
  Serial.begin(9600);
}

void loop() {
  // Membaca nilai ADC dari potensiometer (0 - 1023)
  adcValue = analogRead(potPin);

  // Mengubah ADC menjadi rentang sudut servo (30 - 150 derajat)
  angle = map(adcValue, 0, 1023, 30, 150);

  // Menggerakkan servo ke sudut hasil pemetaan
  myservo.write(angle);

  // Menampilkan data ke Serial Monitor
  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | Sudut: ");
  Serial.println(angle);

  // Delay kecil agar pergerakan servo lebih stabil
  delay(15);
}

```