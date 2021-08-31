#include <cstdint>

class Chip8
{
    public:
        //general purpose memory
        //0x0 - 0x1FF Reserved for Interpreter
        //0x200 - 0xFFF Program/Data space
        uint8_t memory[4069];
        //registers
        uint8_t reg[16]; //16 8-bit general purpose registers
        uint16_t index; //holds a memory address
        uint8_t delayTimer;
        uint8_t soundTimer;
        uint16_t PC; //Program Counter
        uint8_t SP; //Stack Pointer
        uint16_t stack[16];
        //Input - Output
        uint8_t keypad[16]; //0-F
        uint32_t display[64 * 32];

        uint16_t opcode; //holds current instruction consisting out of 2 bytes

        //functions
        const unsigned int START_ADDRESS = 0x200;
        Chip8();
        void loadRom(char const* filename);
};