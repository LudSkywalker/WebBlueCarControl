/*
    Based on Neil Kolban example for IDF: https://github.com/nkolban/esp32-snippets/blob/master/cpp_utils/tests/BLE%20Tests/SampleWrite.cpp
    Ported to Arduino ESP32 by Evandro Copercini
*/

#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

#include <BLE2902.h>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/

#define BLE_NAME "LudESP32" //must match filters name in bluetoothterminal.js- navigator.bluetooth.requestDevice
//#define SERVICE_UUID        "6e400001-b5a3-f393-e0a9-e50e24dcca9e" //- must match optional services on navigator.bluetooth.requestDevice
//#define CHARACTERISTIC_UUID "6e400003-b5a3-f393-e0a9-e50e24dcca9e"

//maintain compatability with HM-10
BLEUUID SERVICE_UUID((uint16_t)0xFFE0); // UART service UUID
BLEUUID CHARACTERISTIC_UUID ((uint16_t)0xFFE1);

/*
 * navigator.bluetooth.requestDevice({
   
    filters: [{
        name: 'ESP32'
      }],
      optionalServices: ['6e400001-b5a3-f393-e0a9-e50e24dcca9e',
      '6e400002-b5a3-f393-e0a9-e50e24dcca9e',
      '6e400003-b5a3-f393-e0a9-e50e24dcca9e']
    }).
*/


//BLEUUID  SERVICE_UUID((uint16_t)0xFFE0); // UART service UUID
//BLEUUID CHARACTERISTIC_UUID((uint16_t)0xFFE1);

//BLEUUID CHARACTERISTIC_UUID_RX((uint16_t)0xFFE2);
int leds[4] = {15, 2, 4, 5};

class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      String value = pCharacteristic->getValue();

      if (value.length() > 0) {
        String command=value;
        command.trim();
        if (command == "!UP")
        {
            digitalWrite(leds[0], HIGH);
            delay(1000);
        }
        else if (command == "!DOWN")
        {
            digitalWrite(leds[1], HIGH);
            delay(1000);
        }
        else if (command == "!LEFT")
        {
            digitalWrite(leds[2], HIGH);
            delay(1000);
        }
        else if (command == "!RIGHT")
        {
            digitalWrite(leds[3], HIGH);
            delay(1000);
        }

        pCharacteristic->setValue(value +"\n"); // must add seperator \n for it to register on BLE terminal
        pCharacteristic->notify();

        //pCharacteristic->writeValue(1, 1, true);
      }
    }
};

void setup() {
  Serial.begin(115200);

  BLEDevice::init(BLE_NAME);
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  BLECharacteristic *pCharacteristic = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID,
                                         BLECharacteristic::PROPERTY_READ |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY
                                       );

  pCharacteristic->setCallbacks(new MyCallbacks());
  
  pCharacteristic->addDescriptor(new BLE2902());

  //pCharacteristic->setValue("R/W");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  for (int i = 0; i < sizeof(leds); i++)
  {
      pinMode(leds[i], OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);
}