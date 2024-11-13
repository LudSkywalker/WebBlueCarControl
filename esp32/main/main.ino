#include "BluetoothSerial.h"
BluetoothSerial SerialBT;

#define PC_SERIAL_BAUDRATE  9600
#define BT_SERIAL_BAUDRATE  9600

int leds[4] = {15, 2, 4, 5};

void setup()
{

    Serial.begin(9600);
    SerialBT.begin("LudESP32");
    for (int i = 0; i < sizeof(leds); i++)
    {
        pinMode(leds[i], OUTPUT);
    }
}

void loop()
{
    for (int i = 0; i < sizeof(leds); i++)
    {
        digitalWrite(leds[i], LOW);
    }
    if (SerialBT.available())
    {
        String command = SerialBT.readString();
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
    }
}
