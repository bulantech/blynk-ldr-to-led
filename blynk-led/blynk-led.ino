
/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <Ticker.h>

#define LED_BUILTIN 2

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
//char auth[] = "ad0cd4da292e49c4bd7c969cb4e74cfd"; //ldr
char auth[] = "bc1e65214e7646638a9604c88e88b8da"; //led

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "true_home2G_350";
char pass[] = "88f02350";

int lampPin = D1;    // select the input pin for the potentiometer
int ldrValue = 0;  // variable to store the value coming from the sensor
bool stateV1 = false;

Ticker ldrBlinker;

void setup()
{
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(lampPin, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  ldrBlinker.attach(1, ldrBlink);
}

void loop()
{
  Blynk.run();
}

void ldrBlink() {  
  if(stateV1) {
    analogWrite(lampPin, 1023);
    Serial.println("analogWrite = 1023" );
  } else {
    analogWrite(lampPin, ldrValue);
    Serial.println("analogWrite = " + String(ldrValue));
  }
  digitalWrite(LED_BUILTIN, LOW);  
  delay(100);
  digitalWrite(LED_BUILTIN, HIGH);
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

BLYNK_WRITE(V5)
{
  digitalWrite(LED_BUILTIN, LOW); //on
  int pinValue = param.asInt(); // assigning incoming value from pin V1 to a variable
  Serial.println("V5 pinValue = " + String(pinValue));
  ldrValue = pinValue;
}


