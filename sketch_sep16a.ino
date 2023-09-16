#include<DHT.h>

//  declaring sensor pin
byte sensor_pin = 4;

//  macro for type of sensor used
#define sensor_type DHT11

//  making object using constructor
DHT dht_sensor(sensor_pin , sensor_type);

const byte r_pin = 5;  //  GPIO 25,26,27
const byte g_pin = 18;
const byte b_pin = 19;

//  channel
const byte r_channel = 0;
const byte g_channel = 1;
const byte b_channel = 2;

//  frequency and resolution
const int frequency = 5000;
const int resolution = 8;

void setup(){

  //  serial communication
  Serial.begin(9600);

  //  initialize the sensor
  dht_sensor.begin();

  //  setup function
  ledcSetup(r_channel , frequency , resolution);
  ledcSetup(g_channel , frequency , resolution);
  ledcSetup(b_channel , frequency , resolution);

  //  attaching channel with pin
  ledcAttachPin(r_pin , r_channel);
  ledcAttachPin(g_pin , g_channel);
  ledcAttachPin(b_pin , b_channel);
  
}

void loop(){

  float temp_c = dht_sensor.readTemperature();  //  DHT works in 0 to 50 deg celcius
  float temp_f = dht_sensor.readTemperature(true);  //  arg : isFahrenheit = true
  float temp_k = temp_c + 273.15; //  kelevin = celcius + 273.15
  float humidity = dht_sensor.readHumidity();  //  relative humidity
  float dew_point = (temp_c - (100 - humidity) / 5);  //  dew point in celcius

  if (isnan(temp_c)  ||  isnan(temp_f)  ||  isnan(humidity))
  {
    Serial.println("Can't get temperature and humidity");
    return;
  }

  Serial.print("Celcius Temperature : ");
  Serial.print(temp_c);
  Serial.println(" *C");
  Serial.print("Fahrenheit Temperature : ");
  Serial.print(temp_f);
  Serial.println(" *F");
  Serial.print("Kelevin Temperature : ");
  Serial.print(temp_k);
  Serial.println(" *K");
  Serial.print("Humidity : ");
  Serial.print(humidity);
  Serial.println(" % RH");
  Serial.print("Dew point : ");
  Serial.print(dew_point);
  Serial.println(" *C");
  Serial.println();  //  new line

  delay(2000);  //  sensor is slow, wait for 2 sec, before taking new readings
  
}