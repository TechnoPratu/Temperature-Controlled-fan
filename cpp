#include <DHT.h>

#define DHTPIN 2     // Pin which is connected to the DHT sensor
#define DHTTYPE DHT11   // DHT 11
#define FANPIN 9     // Pin which is connected to the fan (PWM)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(FANPIN, OUTPUT);
}

void loop() {
  // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Print the results to the Serial Monitor
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.print(F("%  Temperature: "));
  Serial.print(t);
  Serial.print(F("°C "));
  Serial.print(f);
  Serial.println(F("°F"));

  // Control the fan speed based on temperature
  int fanSpeed = map(t, 20, 30, 0, 255); // Map temperature range to PWM range
  fanSpeed = constrain(fanSpeed, 0, 255); // Constrain the value between 0 and 255
  analogWrite(FANPIN, fanSpeed);
}

