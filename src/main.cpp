
/**
 * @brief Test the BME280
 */

#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <Wire.h>

Adafruit_BME280 bme; // I2C

#define inch_Hg_per_hPa 0.02953
#define SEALEVELPRESSURE_HPA (1013.25)

extern void scan(bool verbose = false);

bool init_bme280() {
    // default settings
    bool status = bme.begin(0x76);
    // You can also pass in a Wire library object like &Wire2
    // status = bme.begin(0x76, &Wire2)
    if (!status) {
        Serial.println("Could not find a valid BME280 sensor, check wiring, address, sensor ID!");
        Serial.print("SensorID was: 0x");
        Serial.println(bme.sensorID(), 16);
    }

    return status;
}

void test_bme280() {
    Serial.print("Temperature = ");
    Serial.print(bme.readTemperature());
    Serial.println(" °C");

    Serial.print("Pressure = ");

    Serial.print(bme.readPressure() / 100.0F);
    Serial.println(" hPa");

    Serial.print("Approx. Altitude = ");
    Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
    Serial.println(" m");

    Serial.print("Humidity = ");
    Serial.print(bme.readHumidity());
    Serial.println(" %");

    Serial.println();
}

void setup() {
    Serial.begin(115200);
    while (!Serial)
        delay(100);

    Serial.println("boot");

    Wire.begin();

    Serial.println("\nI2C Scanner");

#if 1
    init_bme280();

    test_bme280();
#endif
}


void loop() {
    static long last = 0;
    while (millis() - last > 1000) {
        last = millis();
        scan();
        #if 1
        test_bme280();
        #endif

    }
}