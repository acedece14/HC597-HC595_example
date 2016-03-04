/*
 * hc597.h
 *
 *  Created on: 03 марта 2016 г.
 *      Author: admin
 */

#ifndef HC597_HC595_H_
#define HC597_HC595_H_

#include <Arduino.h>
class HC597_595 {
private:
	uint8_t dataPin_in;
	uint8_t dataPin_out;
	uint8_t clockPin;
	uint8_t latchPin;
	uint8_t plPin;
	uint8_t state_in;
	uint8_t state_out;
public:
	HC597_595(uint8_t data_in, uint8_t data_out, uint8_t clock, uint8_t latch,
			uint8_t pl);
	void writeToReg();
	void setStateBit(uint8_t bit, uint8_t val);
	void writeStateByte(uint8_t state);
	void readFromReg();
	boolean getStateBit(uint8_t bit);
	uint8_t getStateByte();
};

#endif /* HC597_HC595_H_ */
