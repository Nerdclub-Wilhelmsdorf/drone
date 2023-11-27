#include <esp_now.h>
#include <WiFi.h>

void onDataRecv(const uint8_t *mac_addr, const uint8_t *data, int data_len) {
  if (data_len == sizeof(int) * 4) {
    int receivedData[4];
    memcpy(receivedData, data, data_len);

    Serial.println("Received data:");
    for (int i = 0; i < 4; i++) {
      Serial.print(receivedData[i]);
      Serial.print(" ");
    }
    Serial.println();
  } else {
    Serial.println("Invalid data length");
  }
}

void setup() {
  Serial.begin(115200);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_register_recv_cb(onDataRecv);
}

void loop() {
  delay(1000);
}
