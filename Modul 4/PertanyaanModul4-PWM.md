1. Jelaskan mengapa LED dapat diatur kecerahannya menggunakan fungsi analogWrite()!
2. Apa hubungan antara nilai ADC (0–1023) dan nilai PWM (0–255)?
3. Modifikasilah program berikut agar LED hanya menyala pada rentang kecerahan sedang, yaitu hanya ketika nilai PWM berada pada rentang 50 sampai 200. Jelaskan program pada file README.md.

# Jawaban

1. Fungsi analogWrite() digunakan untuk menghasilkan sinyal PWM (Pulse Width Modulation) pada pin Arduino.

2. ADC pada Arduino Uno memiliki resolusi 10-bit 
Rentang nilai 0–1023
Sedangkan PWM memiliki resolusi 8-bit Rentang nilai 0–255 Karena rentangnya berbeda, nilai ADC harus dikonversi menggunakan fungsi map()

3.
```
int ledPin = 9;
int potPin = A0;
int adcValue;
int pwmValue;

void setup() {
  // Mengatur LED sebagai output
  pinMode(ledPin, OUTPUT);
  
  // Memulai serial monitor
  Serial.begin(9600);
}

void loop() {
  // Membaca nilai ADC dari potensiometer
  adcValue = analogRead(potPin);
  
  // Mengonversi rentang ADC (0-1023) ke PWM (0-255)
  pwmValue = map(adcValue, 0, 1023, 0, 255);

  // Mengecek apakah PWM berada pada rentang 50 - 200
  if (pwmValue >= 50 && pwmValue <= 200) {
    // LED menyala sesuai intensitas PWM
    analogWrite(ledPin, pwmValue);
  } else {
    // LED mati jika di luar rentang
    analogWrite(ledPin, 0);
  }

  // Menampilkan data ke serial monitor
  Serial.print("ADC: ");
  Serial.print(adcValue);
  Serial.print(" | PWM: ");
  Serial.println(pwmValue);

  delay(100);
}
```