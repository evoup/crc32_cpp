#include <stdio.h>
#include <stdlib.h>
#include <string>
#include "main.h"
int main(int argc, char ** argv){
    Init_CRC32_Table();
    char * csText="post";
    int nCRC;
    char chCRC[8];
    nCRC = Get_CRC(csText);
    printf("%d\r\n", nCRC);
    // Convert the integer to an ASCII character string.
    //itoa(nCRC, chCRC, 16); // Note that the CRC number is in hex
    //printf("%s", chCRC);
    return 1;
}




// Call this function only once to initialize the CRC table.
void Init_CRC32_Table()
{// Called by OnInitDialog()

    // This is the official polynomial used by CRC-32 
    // in PKZip, WinZip and Ethernet. 
    ULONG ulPolynomial = 0x04c11db7;

    // 256 values representing ASCII character codes.
    for(int i = 0; i <= 0xFF; i++)
    {
        crc32_table[i]=Reflect(i, 8) << 24;
        for (int j = 0; j < 8; j++)
            crc32_table[i] = (crc32_table[i] << 1) ^ (crc32_table[i] & (1 << 31) ? ulPolynomial : 0);
        crc32_table[i] = Reflect(crc32_table[i], 32);
    }
}

// Reflection is a requirement for the official CRC-32 standard.
// You can create CRCs without it, but they won't conform to the standard.
ULONG Reflect(ULONG ref, char ch)
{// Used only by Init_CRC32_Table()

    ULONG value(0);

    // Swap bit 0 for bit 7
    // bit 1 for bit 6, etc.
    for(int i = 1; i < (ch + 1); i++)
    {
        if(ref & 1)
            value |= 1 << (ch - i);
        ref >>= 1;
    }
    return value;
}

// Once the lookup table has been filled in by the two functions above,
// this function creates all CRCs using only the lookup table.
int Get_CRC(char * text)
{// Called by OnChangeText()

    // Be sure to use unsigned variables,
    // because negative values introduce high bits
    // where zero bits are required.

    // Start out with all bits set high.
    ULONG  ulCRC(0xffffffff);
    int len;
    unsigned char* buffer;

    // Get the length.
    // Note that if the text contains NULL characters
    // processing ends at the first NULL and the CRC value is invalid.
    // See the 32 Bit File Demonstration source code
    // for a method of dealing with NULL characters in files.
    // len = text.GetLength();
    len = strlen(text);

    // Save the text in the buffer.
    buffer = (unsigned char*)( char * )text;
    // Perform the algorithm on each character
    // in the string, using the lookup table values.
    while(len--)
        ulCRC = (ulCRC >> 8) ^ crc32_table[(ulCRC & 0xFF) ^ *buffer++];
    // Exclusive OR the result with the beginning value.
    return ulCRC ^ 0xffffffff;
}

