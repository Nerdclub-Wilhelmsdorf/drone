/*
 Pinsauf dem ESP:
 
 Joystick links
 VRy = G26 = orange
 VRx = G25 = gelb

 Joystick rechts
 VRy = G19 = grün
 VRx = G18 = blau
 */

#include <esp_now.h>
#include <WiFi.h>

#define VRX_PIN  26 // ESP32 pin GPIO36 (ADC0) connected to VRX pin

#define VRY_PIN  25 // ESP32 pin GPIO39 (ADC0) connected to VRY pin



// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x24, 0x0A, 0xC4, 0x5F, 0xEC, 0xEC};

typedef struct struct_message {
  int a;
  int b;
  int c;
  int d;
} struct_message;

struct_message myData;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}



void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  Serial.println(getJoystickX());
  myData.a = getJoystickX();
  myData.b = getJoystickY();
  myData.c = 1;
  myData.d = 1;

Serial.println(myData.a);

 esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
delay(100);
}

float getJoystickY() {

  int valueX = 0; // to store the X-axis value

  valueX = analogRead(VRY_PIN);

  //return ((valueX/4095.0) * 180);

  //return map(valueY, 0, 4095, -180, 180);

  return valueX;

}

float getJoystickX() {

  int valueX = 0; // to store the X-axis value

  valueX = analogRead(VRX_PIN);

  //return ((valueX/4095.0) * 180);

  return map(valueX, 2900, 0, 0, 180);

 // return valueX;

}
