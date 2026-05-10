1. Gambarkan rangkaian schematic yang digunakan pada percobaan!
2. Mengapa pada push button digunakan mode INPUT_PULLUP pada Arduino Uno? Apa keuntungannya dibandingkan rangkaian biasa?
3. Jika salah satu LED segmen tidak menyala, apa saja kemungkinan penyebabnya dari sisi hardware maupun software?
4. Modifikasi rangkaian dan program dengan dua push button yang berfungsi sebagai penambahan (increment) dan pengurangan (decrement) pada sistem counter dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!

# Jawaban

1. 
2. Mode INPUT_PULLUP digunakan agar pin input memiliki kondisi default HIGH ketika tombol tidak ditekan.  
Keuntungannya mengurangi komponen eksternal dan
rangkaian lebih sederhana.

3. 
Hardware
- Kabel jumper salah sambung atau rusak.
- Resistor rusak.
- LED segmen pada seven segment rusak.
- Breadboard tidak terhubung dengan benar atau rusak.
- Pin Arduino rusak.
- Polaritas common cathode/common anode salah atau rusak.

Software
- Konfigurasi pin salah.
- Data array pola seven segment salah.
- Pin belum diatur sebagai OUTPUT.
- Kesalahan logika pada digitalWrite().
- Salah memilih tipe seven segment pada program.

4. 

# Program Counter Seven Segment Dengan Dua Push Button

## Tujuan
Program digunakan untuk menampilkan counter hexadecimal pada seven segment menggunakan dua push button:
- Tombol 1 → Increment
- Tombol 2 → Decrement

---

# Konfigurasi Pin

| Komponen | Pin Arduino |
|---|---|
| Segmen a | 7 |
| Segmen b | 6 |
| Segmen c | 5 |
| Segmen d | 11 |
| Segmen e | 10 |
| Segmen f | 8 |
| Segmen g | 9 |
| Push Button Increment | 2 |
| Push Button Decrement | 3 |

---

# Source Code

```cpp
// Array pin seven segment
int segmentPins[7] = {7,6,5,11,10,8,9};

// Pin push button
int btnUp = 2;
int btnDown = 3;

// Variabel counter
int counter = 0;

// Pola angka hexadecimal
byte numbers[16][7] = {
  {1,1,1,1,1,1,0}, //0
  {0,1,1,0,0,0,0}, //1
  {1,1,0,1,1,0,1}, //2
  {1,1,1,1,0,0,1}, //3
  {0,1,1,0,0,1,1}, //4
  {1,0,1,1,0,1,1}, //5
  {1,0,1,1,1,1,1}, //6
  {1,1,1,0,0,0,0}, //7
  {1,1,1,1,1,1,1}, //8
  {1,1,1,1,0,1,1}, //9
  {1,1,1,0,1,1,1}, //A
  {0,0,1,1,1,1,1}, //b
  {1,0,0,1,1,1,0}, //C
  {0,1,1,1,1,0,1}, //d
  {1,0,0,1,1,1,1}, //E
  {1,0,0,0,1,1,1}  //F
};

void setup() {

  // Mengatur pin seven segment sebagai output
  for(int i=0; i<7; i++){
    pinMode(segmentPins[i], OUTPUT);
  }

  // Mengatur push button sebagai input pullup
  pinMode(btnUp, INPUT_PULLUP);
  pinMode(btnDown, INPUT_PULLUP);

  // Menampilkan angka awal
  displayNumber(counter);
}

void loop() {

  // Jika tombol increment ditekan
  if(digitalRead(btnUp) == LOW){

    counter++;

    // Jika lebih dari 15 kembali ke 0
    if(counter > 15){
      counter = 0;
    }

    displayNumber(counter);

    delay(200);
  }

  // Jika tombol decrement ditekan
  if(digitalRead(btnDown) == LOW){

    counter--;

    // Jika kurang dari 0 kembali ke 15
    if(counter < 0){
      counter = 15;
    }

    displayNumber(counter);

    delay(200);
  }
}

// Fungsi menampilkan angka ke seven segment
void displayNumber(int num){

  for(int i=0; i<7; i++){

    digitalWrite(segmentPins[i], numbers[num][i]);

  }
}