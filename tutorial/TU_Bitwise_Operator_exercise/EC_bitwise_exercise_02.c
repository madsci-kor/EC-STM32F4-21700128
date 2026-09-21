#include <stdio.h> 

int main()
{
    unsigned char num1 = 4;    // 4: 0000 0100
    unsigned char num2 = 4;    // 4: 0000 0100
    unsigned char num3 = 4;    // 4: 0000 0100
    unsigned char num4 = 4;    // 4: 0000 0100
    unsigned char num5 = 4;    // 4: 0000 0100

    num1 &= 5;     // 5 (0000 0101) AND 연산 후 할당
    num2 |= 2;     // 2 (0000 0010) OR 연산 후 할당
    num3 ^= 3;     // 3 (0000 0011) XOR 연산 후 할당
    num4 <<= 2;    // 비트를 왼쪽으로 2번 이동한 후 할당
    num5 >>= 2;    // 비트를 오른쪽으로 2번 이동한 후 할당

    printf("%u\n", num1);
    printf("%u\n", num2);
    printf("%u\n", num3);
    printf("%u\n", num4);
    printf("%u\n", num5);

    return 0;
}