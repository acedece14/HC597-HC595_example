/*
 * hc597_hc595.cpp
 *
 *  Created on: 03 марта 2016 г.
 *      Author: admin
 */

#include "hc597_hc595.h"

HC597_595::HC597_595(uint8_t data_in, uint8_t data_out, uint8_t clock,
		uint8_t latch, uint8_t pl) {
	dataPin_in = data_in;
	dataPin_out = data_out;
	clockPin = clock;
	latchPin = latch;
	plPin = pl;

	pinMode(dataPin_out, OUTPUT);
	pinMode(dataPin_in, INPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(latchPin, OUTPUT);
	pinMode(plPin, OUTPUT);

	state_in = 0;
	state_out = 0;
}

/********************************
 ██████╗ ███████╗ █████╗ ██████╗
 ██╔══██╗██╔════╝██╔══██╗██╔══██╗
 ██████╔╝█████╗  ███████║██║  ██║
 ██╔══██╗██╔══╝  ██╔══██║██║  ██║
 ██║  ██║███████╗██║  ██║██████╔╝
 ╚═╝  ╚═╝╚══════╝╚═╝  ╚═╝╚═════╝
 *******************************/

uint8_t shiftInReg(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder) {
	uint8_t value = 0;
	uint8_t i;

	for (i = 0; i < 8; ++i) {
		if (bitOrder == LSBFIRST) value |= digitalRead(dataPin) << i;
		else value |= digitalRead(dataPin) << (7 - i);
		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);
	}
	return value;
}

void HC597_595::readFromReg() {
	digitalWrite(latchPin, LOW);
	digitalWrite(latchPin, HIGH);
	digitalWrite(plPin, LOW);
	digitalWrite(plPin, HIGH);
	state_in = shiftInReg(dataPin_in, clockPin, MSBFIRST);
}

uint8_t HC597_595::getStateByte() {
	return state_in;
}

boolean HC597_595::getStateBit(uint8_t bit) {
	return bitRead(state_in, bit);
}

/**************************************
 ██╗    ██╗██████╗ ██╗████████╗███████╗
 ██║    ██║██╔══██╗██║╚══██╔══╝██╔════╝
 ██║ █╗ ██║██████╔╝██║   ██║   █████╗
 ██║███╗██║██╔══██╗██║   ██║   ██╔══╝
 ╚███╔███╔╝██║  ██║██║   ██║   ███████╗
 ╚══╝╚══╝ ╚═╝  ╚═╝╚═╝   ╚═╝   ╚══════╝
 *************************************/
void shiftOutReg(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder,
		uint8_t val) {
	uint8_t i;

	for (i = 0; i < 8; i++) {
		if (bitOrder == LSBFIRST) digitalWrite(dataPin, !!(val & (1 << i)));
		else digitalWrite(dataPin, !!(val & (1 << (7 - i))));

		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);
	}
}

void HC597_595::writeStateByte(uint8_t state) {
	state_out = state;
}

void HC597_595::writeToReg() {
	digitalWrite(latchPin, LOW);
	shiftOutReg(dataPin_out, clockPin, MSBFIRST, state_out);
	digitalWrite(latchPin, HIGH);
}

void HC597_595::setStateBit(uint8_t bit, uint8_t val) {
	bitWrite(state_out, bit, val);
}

