/*
   Wiring
   ------
   BMP085 Vcc to 3.3V
   BMP085 GND to GND
   BMP085 SCL to I2C-SCL
   BMP085 SDA to I2C-SDA

   Adapted for IntoRobot by Robin, Sept 19, 2015
 */
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp085;

// 初始化 BMP085
void InitializeBMP085()
{
    Serial.begin(115200);
    if (!bmp085.begin())
    {
        Serial.println("无法找到有效的BMP085传感器，请检查总线");
        while (1) {}
    }
}

// 发布气压 海拔高度
void PublishBMP085Info()
{
    //获取温度值
    Serial.print("Temperature = ");
    Serial.print(bmp085.readTemperature());
    Serial.println(" *C");

    //获取气压
    Serial.print("Pressure = ");
    Serial.print(bmp085.readPressure());
    Serial.println(" Pa");

    //假设标准大气压为1013.25 millibar = 101325 Pascal 计算海拔高度
    Serial.print("Altitude = ");
    Serial.print(bmp085.readAltitude());
    Serial.println(" meters");

    //你可以得到一个更精准的高度值，如果你知道海平面气压，这和天气有关。比如1015 millibars=101500 Pascals
    Serial.print("Real altitude = ");
    Serial.print(bmp085.readAltitude(101500));
    Serial.println(" meters");

    char szEventInfo[64];

    sprintf(szEventInfo, "Temperature=%.2f °C, Pressure=%.2f hPa", bmp085.readTemperature(), bmp085.readPressure()/100.0);

}

// 初始化LED
void InitializeApplication()
{
    pinMode(D7, OUTPUT);
}

// LED闪烁
void BlinkLED()
{
    digitalWrite(D7, HIGH);
    delay(500);
    digitalWrite(D7, LOW);
    delay(500);
}

void setup()
{
    InitializeApplication();
    InitializeBMP085();
}

void loop()
{
    PublishBMP085Info();
    BlinkLED();
    delay(2000);
}
