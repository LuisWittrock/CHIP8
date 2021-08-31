#include <chip8.hpp>


//FONT (0-F)
const unsigned int FONTSET_START_ADDRESS = 0x50;
const unsigned int  FONTSET_SIZE = 80;

uint8_t fontset[FONTSET_SIZE] =
	{
		0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
		0x20, 0x60, 0x20, 0x20, 0x70, // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
		0x90, 0x90, 0xF0, 0x10, 0x10, // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
		0xF0, 0x10, 0x20, 0x40, 0x40, // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90, // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
		0xF0, 0x80, 0x80, 0x80, 0xF0, // C
		0xE0, 0x90, 0x90, 0x90, 0xE0, // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
		0xF0, 0x80, 0xF0, 0x80, 0x80  // F
	};


Chip8::Chip8() 
    : randGen(std::chrono::system_clock::now().time_since_epoch().count())
{
    PC = START_ADDRESS; // set the program counter to the starting address of the program.

    //load fonts into memory starting from position FONTSET_START_ADDRESS normally 0x50
    for(int i = 0; i<FONTSET_SIZE; i++)
    {
        memory[FONTSET_START_ADDRESS + i] = fontset[i];
    }

    //initialize RandomNumberGenerator
    randByte = std::uniform_int_distribution<uint8_t>(0, 255U);
}

void Chip8::loadRom(char const *filename)
{
    //open file as binary and move file pointer to the end of the file
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if (file.is_open())
    {
        //create new buffer in the size of the file
        std::streampos size = file.tellg(); //get size of file
        char *buffer = new char[size];      //create buffer

        file.seekg(0, std::ios::beg); //go to beg(inning) of file
        file.read(buffer, size);      //fill the buffer with characters from the file
        file.close();

        //Load the rom contents into the chip8 memory starting at START_ADDRESS (probaply 0x200)
        for (int i = 0; i < size; i++)
        {
            memory[START_ADDRESS + i] = buffer[i];
        }

        delete[] buffer;
    }
}