#include <cstdint>
#include <fstream>
#include <chrono>
#include <random>
#include <cstring>

class Chip8
{
    public:
        Chip8();
        void loadRom(char const* filename);

        //IO
        uint8_t keypad[16]; //0-F
        uint32_t display[64 * 32];

    private:
        //Instructions
        //There are 34 instructions

        //CLS | clear dispalay
        void OP_00E0();
        //RET | Return from subroutine
        void OP_00EE();
        //JP | Jump to location nnn
        void OP_1nnn();
        //CALL | call subroutine at nnn
        void OP_2nnn();
        //SE | skip next instruction if Vx == kk
        void OP_3xkk();
        //SNE | skip next instrucion if Vx != kk
        void OP_4xkk();
        //SE | skip next instruction if Vx = Vy
        void OP_5xy0();
        //LD | put kk into Vx
        void OP_6xkk();
        //ADD | set Vx = Vx+kk
        void OP_7xkk();
        //LD | set Vx = Vy
        void OP_8xy0();
        //OR | set Vx = Vx OR Vy
        void OP_8xy1();
        //AND | set Vx = Vx AND Vy
        void OP_8xy2();
        //XOR | set Vx = Vx XOR Vy
        void OP_8xy3();
        //ADD | Vx = Vx + Vy set Vf = carry
        void OP_8xy4();
        //SUB | Vx = Vx - Vy set Vf = NOT borrow
        void OP_8xy5();
        //SHR | Vf is set to least-significant bit of Vx and than Vx is divided by 2
        void OP_8xy6();
        //SUBN | Vx = Vy - Vx, set VF not borrow
        void OP_8xy7();
        //SHL | Set Vx = Vx SHL 1
        void OP_8xyE();
        //SNE | skip next instruction if Vx != Vy
        void OP_9xy0();
        //LD | Set Index = nnn
        void OP_Annn();
        //JP | jump to location nnn + V0
        void OP_Bnnn();
        //RND | Set Vx = random byte AND kk
        void OP_Cxkk();
        //Drw | Display n-byte sprite starting at memory location I at (Vx, Vy), set VF = collision.
        void OP_Dxyn();
        //SKP | Skip next instruction if key with value Vx is pressed.
        void OP_Ex9E();
        //SKNP | skip next instruction if key Vx is not pressed.
        void OP_ExA1();
        //LD | set Vx delay timer value
        void OP_Fx07();
        //LD | Wait for keypress and store in Vx
        void OP_Fx0A();
        //LD | set delay timer = Vx
        void OP_Fx15();
        //LD | set sound timer = Vx
        void OP_Fx18();
        //ADD | Set Index = Index + Vx
        void OP_Fx1E();
        //LD | Set I = location of sprite for digit Vx
        void OP_Fx29();
        //LD | Store BCD representation of Vx in memory locations I, I+1, I+2
        void OP_Fx33();
        //LD | Store Registers Vo - Vx in memory starting at location Index
        void OP_Fx55();
        //LD | Read registers V0 - Vx from memory starting at location Index

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
        

        uint16_t opcode; //holds current instruction consisting out of 2 bytes

        //needed for random number generation
        std::default_random_engine randGen;
	    std::uniform_int_distribution<uint8_t> randByte;

        //general
        const unsigned int START_ADDRESS = 0x200; //here is where the program data starts
        
};