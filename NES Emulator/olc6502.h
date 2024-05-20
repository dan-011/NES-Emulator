#pragma once
#include <cstdint>
#include <string>
#include <vector>
#include "Bus.h"

class Bus;

class olc6502 {
public:
	olc6502();
	~olc6502();

	void ConnectToBus(Bus* newBus);

	enum FLAG6502 {
		C = (1 << 0), // Carry bit: set by the user to inform an operation that we want to use a carry bit, or it is set by the operation itself
		Z = (1 << 1), // Zero bit: set when the result of an operation equals zero
		I = (1 << 2), // Interrupts bit: set to disable interrupts
		D = (1 << 3), // Decimal bit: WOULD be used to to flag floating points
		B = (1 << 4), // Break bit: indicates the break operation has been called
		U = (1 << 5), // Unused bit
		V = (1 << 6), // Overflow bit
		N = (1 << 7), // Negative bit: indicates signed variables
	};

	uint8_t status = 0x00; // status register
	uint8_t accumulator = 0x00; // accumulator register
	uint8_t x = 0x00; // x register
	uint8_t y = 0x00; // y register
	uint8_t stackPointer = 0x00; // stack pointer
	uint16_t programCounter = 0x0000; // program counter

	// Addressing Modes (12 total)
	uint8_t IMP(); // implied data source
	uint8_t IMM(); // immediate data source
	uint8_t ZP0();
	uint8_t ZPX();
	uint8_t ZPY();
	uint8_t REL();
	uint8_t ABS(); // reeference data witha bsolute value
	uint8_t ABX();
	uint8_t ABY();
	uint8_t IND();
	uint8_t IZX();
	uint8_t IZY();

	//Opcodes
	uint8_t ADC();
	uint8_t AND();
	uint8_t ASL();
	uint8_t BCC();
	uint8_t BCS();
	uint8_t BEQ();
	uint8_t BIT();
	uint8_t BMI();
	uint8_t BNE();
	uint8_t BPL();
	uint8_t BRK();
	uint8_t BVC();
	uint8_t BVS();
	uint8_t CLC();
	uint8_t CLD();
	uint8_t CLI();
	uint8_t CLV();
	uint8_t CMP();
	uint8_t CPX();
	uint8_t CPY();
	uint8_t DEC();
	uint8_t DEX();
	uint8_t DEY();
	uint8_t EOR();
	uint8_t INC();
	uint8_t INX();
	uint8_t INY();
	uint8_t JMP();
	uint8_t JSR();
	uint8_t LDA();
	uint8_t LDX();
	uint8_t LDY();
	uint8_t LSR();
	uint8_t NOP();
	uint8_t ORA();
	uint8_t PHA();
	uint8_t PHP();
	uint8_t PLA();
	uint8_t PLP();
	uint8_t ROL();
	uint8_t ROR();
	uint8_t RTI();
	uint8_t RTS();
	uint8_t SBC();
	uint8_t SEC();
	uint8_t SED();
	uint8_t SEI();
	uint8_t STA();
	uint8_t STX();
	uint8_t STY();
	uint8_t TAX();
	uint8_t TAY();
	uint8_t TSX();
	uint8_t TXA();
	uint8_t TXS();
	uint8_t TYA();

	uint8_t XXX(); // for illegal opcode

	void clock(); // indicates clocks signal

	// these functions can occur at any time, behave asynchronously, interrupt rpocessor from doing what it's doing
	// processor will always finish its instruction
	void reset();
	void interruptRequest(); // this can be ignored depending on if the interrupt enabled flag is on
	void nonmaskableInterruptRequest(); // never can be disabled

	uint8_t fetch(); // fetch data from the appropriate sournce
	uint8_t fetchedData = 0x00;

	uint16_t absoluteAddr = 0x0000; // we want to store the location that we are pulling from (depends on the addressing mode) - absolute address
	uint16_t relativeAddr = 0x0000; // branch instructions can only jump a certain distance from wheere teh function was called which is hte relative distance

	uint8_t opcode = 0x00;
	uint8_t cycles = 0;

private:
	// cpu class body is responsible for internally calling read and writes
	uint8_t read(uint16_t addr);
	void write(uint16_t addr, uint8_t data);

	uint8_t GetFlag(FLAG6502 flag);
	void SetFlag(FLAG6502 flag, bool isSet);

	Bus* bus;

	struct INSTRUCTION {
		std::string name; // holds the numonic
		uint8_t(olc6502::* operate)(void) = nullptr; // function pointer to the operation
		uint8_t(olc6502::* addrMode)(void) = nullptr; // function pointer to the address mode
		uint8_t cycles = 0; // count for the number of cycles that the instruction requires
	};

	std::vector<INSTRUCTION> lookup;
};