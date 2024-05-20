#include "Bus.h"

Bus::Bus() {
	for (auto& idx : ram) idx = 0x00;
	cpu.ConnectToBus(this); // attach CPU to the bus
}

Bus::~Bus() {}

void Bus::write(uint16_t addr, uint8_t data) {
	if (addr >= 0x0000 && addr <= 0xFFFF) { // gueard the full range of the RAM
		ram[addr] = data;
	}
}
uint8_t Bus::read(uint16_t addr, bool bReadOnly = false) {
	return (addr >= 0x0000 && addr <= 0xFFFF) ? ram[addr] : 0x00;

}