1. Gambarkan rangkaian schematic yang digunakan pada percobaan!
2. Apa yang terjadi jika nilai num lebih dari 15?
3. Apakah program ini menggunakan common cathode atau common anode? Jelaskan alasanya!
4. Modifikasi program agar tampilan berjalan dari F ke 0 dan berikan penjelasan disetiap baris kode nya dalam bentuk README.md!


Jawaban  
1.   
2. Jika nilai num lebih dari 15, maka program akan mencoba mengakses data array di luar batas indeks yang tersedia. Karena tampilan hexadecimal hanya memiliki 16 karakter (0–15 atau 0–F), maka indeks array valid hanya dari 0 sampai 15.  
3. Program ini menggunakan cathode.
- Segmen LED menyala ketika pin Arduino diberi logika HIGH.
Pada common cathode, seluruh kaki katoda disambungkan ke GND.

4. 
# Program Seven Segment Countdown F ke 0

## Tujuan
Program digunakan untuk menampilkan karakter hexadecimal dari F sampai 0 pada seven segment menggunakan Arduino Uno.

---

## Source Code

```cpp
// Menentukan pin untuk masing-masing segmen
int segmentPins[7] = {7,6,5,11,10,8,9};

// Data pola hexadecimal untuk seven segment
byte numbers[16][7] = {
  {1,1,1,1,1,1,0}, // 0
  {0,1,1,0,0,0,0}, // 1
  {1,1,0,1,1,0,1}, // 2
  {1,1,1,1,0,0,1}, // 3
  {0,1,1,0,0,1,1}, // 4
  {1,0,1,1,0,1,1}, // 5
  {1,0,1,1,1,1,1}, // 6
  {1,1,1,0,0,0,0}, // 7
  {1,1,1,1,1,1,1}, // 8
  {1,1,1,1,0,1,1}, // 9
  {1,1,1,0,1,1,1}, // A
  {0,0,1,1,1,1,1}, // b
  {1,0,0,1,1,1,0}, // C
  {0,1,1,1,1,0,1}, // d
  {1,0,0,1,1,1,1}, // E
  {1,0,0,0,1,1,1}  // F
};

void setup() {

  // Mengatur semua pin segment sebagai output
  for(int i = 0; i < 7; i++){
    pinMode(segmentPins[i], OUTPUT);
  }
}

void loop() {

  // Perulangan dari F ke 0
  for(int num = 15; num >= 0; num--){

    // Mengirim data ke masing-masing segmen
    for(int i = 0; i < 7; i++){
      digitalWrite(segmentPins[i], numbers[num][i]);
    }

    // Delay 1 detik
    delay(1000);
  }
}