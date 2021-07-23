//
//    FILE: ADS_performance.ino
//  AUTHOR: Rob.Tillaart
// VERSION: 0.1.1
// PURPOSE: read analog input
//

// test
// connect 1 potmeter
//
// GND ---[   x   ]------ 5V
//            |
//
// measure at x (connect to AIN0).


#include "ADS1115-SOLDERED.h" // or #include "ADS1015-SOLDERED.h"

// choose you sensor
// ADS1013 ADS;
// ADS1014 ADS;
// ADS1015 ADS;
// ADS1113 ADS;
// ADS1114 ADS;
ADS1115 ADS;

uint32_t start, d1, d2;
int x;

void setup()
{
    Serial.begin(115200);
    Serial.println(__FILE__);
    Serial.print("ADS1X15_LIB_VERSION: ");
    Serial.println(ADS1X15_LIB_VERSION);

    ADS.begin();
    ADS.setGain(0); // 6.144 volt

    for (int dr = 0; dr < 8; dr++)
    {
        ADS.setDataRate(dr);
        Serial.print("DR:\t");
        Serial.println(dr);

        test_single_shot();
        test_continuous();

        Serial.print("\t\tFACTOR:\t");
        Serial.println(1.0 * d1 / d2);
    }

    Serial.println("\nDone...");
}

void loop()
{
}

void test_single_shot()
{
    Serial.print(__FUNCTION__);

    ADS.setMode(1);
    start = micros();
    x = ADS.readADC(0);
    for (int i = 0; i < 100; i++)
    {
        x = ADS.readADC(0);
    }
    d1 = micros() - start;
    Serial.print("\t");
    Serial.println(d1);
}

void test_continuous()
{
    Serial.print(__FUNCTION__);

    ADS.setMode(0);
    start = micros();
    x = ADS.readADC(0);
    for (int i = 0; i < 100; i++)
    {
        x = ADS.getValue();
    }
    d2 = micros() - start;
    Serial.print("\t\t");
    Serial.println(d2);
}

// -- END OF FILE --