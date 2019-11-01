
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RtcDS3231.h>

#define btn1 5
#define btn2 9

RtcDS3231<TwoWire> Rtc = RtcDS3231<TwoWire>(Wire);
Adafruit_SSD1306 display(128, 64, &Wire);
void Click1()
{
	Serial.println("click1");
}
void Click2()
{
	Serial.println("click3");
}

void setup()
{
	pinMode(btn1, INPUT_PULLUP);
	pinMode(btn2, INPUT_PULLUP);
	attachInterrupt(digitalPinToInterrupt(btn1), Click1, FALLING);
	attachInterrupt(digitalPinToInterrupt(btn2), Click2, FALLING);
	
	
	Serial.begin(9600);
	Rtc.Begin();
	RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
	Rtc.SetDateTime(compiled);
	// SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
	if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3D)) { // Address 0x3D for 128x64
		Serial.println(F("SSD1306 allocation failed"));
		
	}
	display.clearDisplay();

}
void Draw()
{
	display.clearDisplay();
	char timeBuffer[50];
	sprintf(timeBuffer, "%02u:%02u", Rtc.GetDateTime().Hour(), Rtc.GetDateTime().Minute());
	display.print(timeBuffer);
	display.display();
}

void loop()
{
	Draw();
	

}
