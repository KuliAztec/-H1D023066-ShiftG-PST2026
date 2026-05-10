1. Apakah ketiga task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!
2. Bagaimana cara menambahkan task keempat? Jelaskan langkahnya!
3. Modifikasilah program dengan menambah sensor (misalnya potensiometer), lalu gunakan nilainya untuk mengontrol kecepatan LED! Bagaimana hasilnya? Jelaskan program pada file README.md.

# Jawaban

1. 
Ketiga task terlihat berjalan secara concurrent, sebenarnya dieksekusi secara bergantian oleh scheduler FreeRTOS menggunakan teknik context switching.
- FreeRTOS scheduler mengatur kapan setiap task dijalankan.
- Setiap task mendapatkan jatah waktu CPU.
- Ketika task menjalankan vTaskDelay(), task tersebut masuk ke keadaan blocked.
- Scheduler kemudian memberikan CPU ke task lain yang siap dijalankan.
2. 

Langkah 1, Membuat prototype task
```
void Task4(void *pvParameters);
```
Langkah 2, Membuat fungsi task
```
void Task4(void *pvParameters){

  while(1){

    Serial.println("Task 4 berjalan");

    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}
```

Langkah 3,  Menambahkan xTaskCreate() pada setup()
```
xTaskCreate(
  Task4,
  "task4",
  128,
  NULL,
  1,
  NULL
);
```
3. 

```
#include <Arduino_FreeRTOS.h>

// Definisi Pin
const int ledPin = 8;
const int potPin = A0;

// Variabel global (Shared Resource)
int delayTime = 200;

// Prototype Task
void TaskBlink(void *pvParameters);
void TaskPot(void *pvParameters);

void setup() {
  // Memulai serial monitor
  Serial.begin(9600);

  // Membuat Task LED
  xTaskCreate(
    TaskBlink,    // Fungsi Task
    "Blink",      // Nama Task
    128,          // Stack size
    NULL,         // Parameter
    1,            // Prioritas
    NULL          // Task handle
  );

  // Membuat Task Pembacaan Potensiometer
  xTaskCreate(
    TaskPot,
    "Potensiometer",
    128,
    NULL,
    1,
    NULL
  );

  // Menjalankan scheduler (otomatis di Arduino, tapi baik untuk ditulis)
  vTaskStartScheduler();
}

void loop() {
  // Kosong, karena logika berjalan di dalam Task
}

// --- Implementasi Task ---

void TaskBlink(void *pvParameters) {
  pinMode(ledPin, OUTPUT);

  while (1) {
    digitalWrite(ledPin, HIGH);
    vTaskDelay(delayTime / portTICK_PERIOD_MS);
    
    digitalWrite(ledPin, LOW);
    vTaskDelay(delayTime / portTICK_PERIOD_MS);
  }
}

void TaskPot(void *pvParameters) {
  while (1) {
    // Membaca nilai ADC
    int adc = analogRead(potPin);

    // Mengonversi nilai ADC menjadi durasi delay (50ms - 1000ms)
    delayTime = map(adc, 0, 1023, 50, 1000);

    // Menampilkan data ke Serial Monitor
    Serial.print("ADC: ");
    Serial.print(adc);
    Serial.print(" | Delay: ");
    Serial.println(delayTime);

    // Memberi jeda pembacaan sensor agar tidak membebani CPU
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }
}

```