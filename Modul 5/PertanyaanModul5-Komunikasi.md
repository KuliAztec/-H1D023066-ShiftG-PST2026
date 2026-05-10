1. Apakah kedua task berjalan secara bersamaan atau bergantian? Jelaskan mekanismenya!
2. Apakah program ini berpotensi mengalami race condition? Jelaskan!
3. Modifikasilah program dengan menggunakan sensor DHT sesungguhnya sehingga informasi yang ditampilkan dinamis. Bagaimana hasilnya? Jelaskan program pada file README.md.

# jawabam

1. Kedua task berjalan secara concurrent, tetapi dieksekusi bergantian oleh scheduler FreeRTOS.
- Task read_data() mengirim data ke queue.
- Task display() menerima data dari queue.
- Ketika task sedang delay atau blocked, scheduler menjalankan task lain.
2.  mengalami race condition karena komunikasi data dilakukan menggunakan queue FreeRTOS.
- Queue memiliki mekanisme sinkronisasi internal.
- Data dikirim menggunakan xQueueSend().
- Data diterima menggunakan xQueueReceive().
3. 
``` 
#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <DHT.h>

// --- Konfigurasi Pin & Sensor ---
#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

// --- Struktur Data ---
struct SensorData {
  float temp;
  float hum;
};

// --- Global Variables ---
QueueHandle_t sensorQueue;

// --- Prototipe Task ---
void TaskReadSensor(void *pvParameters);
void TaskDisplayData(void *pvParameters);

void setup() {
  Serial.begin(9600);
  while (!Serial) { ; } // Tunggu port serial (khusus Arduino Leonardo/Mega)

  dht.begin();

  // Inisialisasi Queue (Kapasitas: 5 item)
  sensorQueue = xQueueCreate(5, sizeof(struct SensorData));

  if (sensorQueue != NULL) {
    // Membuat Task
    xTaskCreate(TaskReadSensor,  "Sensor",  128, NULL, 1, NULL);
    xTaskCreate(TaskDisplayData, "Display", 128, NULL, 1, NULL);

    // Memulai Penjadwal (Scheduler)
    vTaskStartScheduler();
  } else {
    Serial.println(F("Gagal membuat Queue!"));
  }
}

void loop() {
  // Kosong. Semua logika dijalankan di dalam Task.
}

// --- Implementasi Task ---

void TaskReadSensor(void *pvParameters) {
  struct SensorData currentReadings;

  while (1) {
    // Membaca data dari sensor
    currentReadings.temp = dht.readTemperature();
    currentReadings.hum  = dht.readHumidity();

    // Validasi pembacaan sebelum mengirim ke queue
    if (isnan(currentReadings.temp) || isnan(currentReadings.hum)) {
      Serial.println(F("Kesalahan: Gagal membaca sensor DHT!"));
    } else {
      // Mengirim data ke queue
      xQueueSend(sensorQueue, &currentReadings, portMAX_DELAY);
    }

    // Delay task selama 2 detik (DHT11 butuh waktu antar pembacaan)
    vTaskDelay(2000 / portTICK_PERIOD_MS);
  }
}

void TaskDisplayData(void *pvParameters) {
  struct SensorData receivedData;

  while (1) {
    // Menunggu kiriman data dari queue
    if (xQueueReceive(sensorQueue, &receivedData, portMAX_DELAY) == pdPASS) {
      Serial.print(F("Suhu: "));
      Serial.print(receivedData.temp);
      Serial.print(F(" °C | Humidity: "));
      Serial.print(receivedData.hum);
      Serial.println(F(" %"));
    }
  }
}