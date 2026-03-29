## Pertanyaan Praktikum

1. Pada kondisi apa program masuk ke blok `if`?
2. Pada kondisi apa program masuk ke blok `else`?
3. Apa fungsi dari perintah `delay(timeDelay)`?
4. Jika program memiliki alur `mati → lambat → cepat → reset (mati)`, ubah menjadi: `lambat → cepat → sedang → mati (tanpa reset langsung)` dan jelaskan setiap baris kode.

## Jawaban

### 1. Kondisi masuk ke blok `if`

Program masuk ke blok `if` ketika `timeDelay <= 100`.

- Loop ke-1: `timeDelay = 1000` → kondisi FALSE, masuk `else`
- Loop ke-2: `timeDelay = 900` → kondisi FALSE, masuk `else`
- ...terus berkurang 100 setiap loop...
- Loop ke-10: `timeDelay = 100` → kondisi TRUE, masuk `if`

### 2. Kondisi masuk ke blok `else`

Program masuk ke blok `else` ketika `timeDelay > 100`.

- Pada `else`: `timeDelay -= 100;` (berkurang 100 setiap loop)
- Loop ke-1: `timeDelay = 1000` → `timeDelay = 900`
- Loop ke-2: `timeDelay = 900` → `timeDelay = 800`
- ...hingga `timeDelay` mencapai 100

### 3. Fungsi `delay(timeDelay)`

`delay(timeDelay)` memberikan jeda eksekusi selama `timeDelay` milidetik.

Contoh:

```cpp
void loop() {
  // Nyalakan LED
  digitalWrite(ledPin, HIGH);
  delay(timeDelay);          // LED tetap ON selama timeDelay ms

  // Matikan LED
  digitalWrite(ledPin, LOW);
  delay(timeDelay);          // LED tetap OFF selama timeDelay ms

  // Ubah delay
  if (timeDelay <= 100) {
    delay(3000);             // JEDA 3 detik sebelum reset
    timeDelay = 1000;
  } else {
    timeDelay -= 100;
  }
}
```

### 4. (Permintaan tambahan) alur baru

- Mati → Lambat → Cepat → Sedang → Mati (tanpa reset langsung)
  - `timeDelay` dimulai dari nilai lambat (misalnya 1000)
  - turun ke cepat (misalnya 500), lalu sedang (misalnya 300), lalu mati (`timeDelay` = 0 atau berhenti)
  - setiap transisi terjadi berdasarkan kondisi `if`/`else if`

Contoh dasar (pseudocode):

```cpp
const int ledPin = 6;     // Menentukan pin LED pada pin digital 6
int timeDelay = 1000;     // Delay awal (LED berkedip lambat)

void setup() { 
  pinMode(ledPin, OUTPUT);   // Mengatur pin LED sebagai output
}

void loop() { 
  // Menyalakan LED
  digitalWrite(ledPin, HIGH);  
  delay(timeDelay);           // Menunggu sesuai nilai delay (LED ON)

  // Mematikan LED
  digitalWrite(ledPin, LOW);  
  delay(timeDelay);           // Menunggu sesuai nilai delay (LED OFF)

  // Percabangan untuk mengatur perubahan kecepatan LED
  if (timeDelay <= 200) {     
    // Jika delay sudah sangat kecil (LED sangat cepat)
    timeDelay = 500;          
    // Ubah menjadi kecepatan sedang

  } else if (timeDelay <= 500) {  
    // Jika delay berada pada kecepatan sedang
    timeDelay = 0;            
    // Ubah menjadi mati (tidak berkedip)

  } else {  
    // Jika LED masih dalam kondisi lambat
    timeDelay -= 200;         
    // Kurangi delay agar LED semakin cepat
  }

  // Kondisi untuk menghentikan program
  if (timeDelay == 0) {
    digitalWrite(ledPin, LOW); // Pastikan LED benar-benar mati
    while(true);               // Menghentikan program secara permanen
  }
}
```

---

### Penjelasan Alur Program

1. **Kondisi Awal**
   - `timeDelay = 1000 ms`
   - LED berkedip lambat  

2. **Percepatan Bertahap**
   - Program masuk ke blok `else`
   - `timeDelay` dikurangi (`-200`)
   - LED menjadi semakin cepat  

3. **Kondisi Cepat**
   - Saat `timeDelay ≤ 200`
   - Program masuk ke blok `if`
   - Delay diubah menjadi `500 ms` (kecepatan sedang)  

4. **Kondisi Sedang ke Mati**
   - Saat `timeDelay ≤ 500`
   - Delay diubah menjadi `0`  
   - LED berhenti berkedip  

5. **Program Berhenti**
   - LED dimatikan  
   - `while(true)` menjaga program tetap berhenti (tidak reset ulang)  

---