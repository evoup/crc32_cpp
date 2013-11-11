#ifndef INCLUDE_MAIN_H
#define INCLUDE_MAIN_H
//
typedef unsigned long ULONG;
ULONG crc32_table[256]; // Lookup table array
void Init_CRC32_Table(); // Builds Lookup table array
ULONG Reflect(ULONG ref, char ch); // Reflects CRC bits in the lookup table
int Get_CRC(char * text); // Creates a CRC from a string buffer
//
#endif
