#include <esp_now.h>
#include <WiFi.h>

uint8_t receiverMacAddress[] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};

void setup() {
  Serial.begin(115200);

  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, receiverMacAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  int dataToSend[4] = {100, 200, 300, 400}; // Modify this array with your integer data

  esp_err_t result = esp_now_send(receiverMacAddress, (uint8_t *)dataToSend, sizeof(dataToSend));

  if (result == ESP_OK) {
    Serial.println("Data sent successfully");
  } else {
    Serial.println("Error sending data");
  }

  delay(3000);
}
