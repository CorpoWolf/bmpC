#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef uint8_t byte;

int main()
{
    byte a = 0xAF;
    printf("hex: %x\n", a); // x = hex
    printf("decimal: %d\n", a); // d = decimal
    printf("char: %c\n", a); // c = char
    printf("octal: %o\n", a); // o = octal

    printf("\nSize of byte: %llu\n", sizeof(byte)); // i = integer

    byte b = 0x01;
    printf("\nType B\nhex: %x\ndecimal: %d\n", b, b);

    byte c = 0x0A;
    printf("\nType C\nhex: %x\ndecimal: %d\n", c, c);
    return 0;
}