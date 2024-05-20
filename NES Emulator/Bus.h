#pragma once
#include <cstdint>
#include "olc6502.h"
#include <array>

class Bus {
public:
	Bus();
	~Bus();

	// bus is written to and read from by the CPU
	void write(uint16_t addr, uint8_t data);
	uint8_t read(uint16_t addr, bool bReadOnly = false);
	// we don;t need to emulate the read and write signal because it's implied
	// depending on which function is being called

	olc6502 cpu;
	std::array<uint8_t, 64 * 1024> ram;
};