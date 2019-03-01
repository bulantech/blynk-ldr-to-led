
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Ticker.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "ad0cd4da292e49c4bd7c969cb4e74cfd"; //ldr
char auth2[] = "bc1e65214e7646638a9604c88e88b8da"; //led

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "true_home2G_350";
char pass[] = "88f02350";

int ldrPin = A0;    // select the input pin for the potentiometer
int ldrValue = 0;  // variable to store the value coming from the sensor
bool stateV1 = false;

Ticker ldrReader;
WidgetBridge bridge0(V0);

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  ldrReader.attach(1, ldrRead);
}

void loop()
{
  Blynk.run();
}

void ldrRead() {
  int state = digitalRead(LED_BUILTIN);  // get the current state of GPIO1 pin
  digitalWrite(LED_BUILTIN, !state);     // set pin to the opposite state
  ldrValue = analogRead(ldrPin);
  Serial.println("ldrValue = " + String(ldrValue));
  if(stateV1) {
    Serial.println("stateV1 = true" );
    bridge0.virtualWrite(V5, ldrValue); 
  } else {
    Serial.println("stateV1 = false" );
    bridge0.virtualWrite(V5, 0); 
  }
}

BLYNK_WRITE(V1)
{
  digitalWrite(LED_BUILTIN, LOW); //on
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.println("V1 pinValue = " + String(pinValue));
  if(pinValue) {
    stateV1 = true;
  } else {
    stateV1 = false;
  }
}

BLYNK_CONNECTED() {
  bridge0.setAuthToken(auth2); // Place the AuthToken of the second hardware here
}

