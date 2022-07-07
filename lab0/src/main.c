#define _CRT_SECURE_NO_WARNINGS
#include "converter.h"
#include "in_out.h"
#define SIZE (int)13

int main(void)
{
	int systemBase1 = 0;
    int systemBase2 = 0;
	char number[SIZE + 1] = { 0 };

    InputSystemBase(&systemBase1);
    InputSystemBase(&systemBase2);
    InputNumber(SIZE, number);

    char* convertedNumber = ConvertNumber(systemBase1, systemBase2, number, SIZE);

    OutputNumber(convertedNumber);

    free(convertedNumber);

	return EXIT_SUCCESS;
}
