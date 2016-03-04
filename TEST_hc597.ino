#include "hc597_hc595.h"

#define HC_CLOCK 5  // SHCP
#define HC_DATA_OUT 2   // DS
#define HC_DATA_IN 12   // DS
#define HC_LATCH 4  // STCP
#define HC_PL 14 // PL

#define LED_RED 0
#define LED_GREEN 1

HC597_595* hc;
void setup() {
	Serial.begin(115200);
	hc = new HC597_595(HC_DATA_IN, HC_DATA_OUT, HC_CLOCK, HC_LATCH, HC_PL);
	pinMode(0, INPUT);
}

uint8_t readedByte = 0;
uint8_t lastReadedByte = 0;

void loop() {
	if (digitalRead(0) == LOW) {
		ESP.restart();
	}
	hc->readFromReg(); // update data in HC regs

	hc->setStateBit(0, hc->getStateBit(0));
	hc->setStateBit(1, hc->getStateBit(1));

	hc->writeToReg();

	readedByte = hc->getStateByte();
	if (readedByte != lastReadedByte) Serial.println(readedByte, BIN);
	lastReadedByte = readedByte;

	delay(100);
	//delay(500);
}
