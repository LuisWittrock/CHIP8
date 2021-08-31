#include <chip8.hpp>
#include <fstream>

Chip8::Chip8()
{
    PC = START_ADDRESS; // set the program counter to the starting address of the program.
}

void Chip8::loadRom(char const* filename)
{
    //open file as binary and move file pointer to the end of the file
    std::ifstream file(filename, std::ios::binary | std::ios::ate);

    if(file.is_open())
    {
        //create new buffer in the size of the file
        std::streampos size = file.tellg(); //get size of file
        char* buffer = new char[size]; //create buffer

        file.seekg(0, std::ios::beg); //go to beg(inning) of file
        file.read(buffer, size); //fill the buffer with characters from the file
        file.close();

        //Load the rom contents into the chip8 memory starting at START_ADDRESS (probaply 0x200)
        for(int i = 0; i<size; i++)
        {
            memory[START_ADDRESS + i] = buffer[i];
        }

        delete[] buffer;
    }
}