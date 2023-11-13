/*
 Pinsauf dem ESP:
 
 Joystick links
 VRy = G26 = orange
 VRx = G25 = gelb

 Joystick rechts
 VRy = G19 = grün
 VRx = G18 = blau
 */



const int X_pinL = 25; // X-AusgangL
const int Y_pinL = 26; // Y-AusgangL

const int X_pinR = 25; // X-AusgangR
const int Y_pinR = 26; // Y-AusgangR

void setup() {
Serial.begin(9600);
}

void loop() {
int X_L = 0;
int Y_L = 0;
int X_R = 0;
int Y_R = 0;

X_L = analogRead(X_pinL);
Y_L = analogRead(Y_pinL);

X_R = analogRead(X_pinR);
Y_R = analogRead(Y_pinR);


Serial.println(X_L);
Serial.println(Y_L);
Serial.println(X_R);
Serial.println(Y_R);

delay(500);
}
