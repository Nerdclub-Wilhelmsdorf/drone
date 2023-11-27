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


const int X_pinL = 19; // X-AusgangL
const int Y_pinL = 18; // Y-AusgangL

const int X_pinR = 25; // X-AusgangR
const int Y_pinR = 26; // Y-AusgangR

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
int X_L;
int Y_L;
int X_R;
int Y_R;


X_L = analogRead(X_pinL);
Y_L = analogRead(Y_pinL);


X_R = analogRead(X_pinR);
Y_R = analogRead(Y_pinR);


Serial.println(X_L);
Serial.println(Y_L);
Serial.println();
Serial.println(X_R);
Serial.println(Y_R);
Serial.println();

  myData.a = X_L;
  myData.b = Y_L;
  myData.c = X_R;
  myData.d = Y_R;

 esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }

delay(500);
}
