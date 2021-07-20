// Sean Szumlanski
// COP 3502, Fall 2018

// ===============================
// LonelyPartyArray: SanityCheck.c
// ===============================
// This just checks that your system is using appropriately sized int, pointer,
// and long long unsigned int types. If not, the getArraySizeInBytes() and
// getCurrentSizeInBytes() functions could generate output mismatches during
// testing.


#include <stdio.h>
#include "LonelyPartyArray.h"

#define EXPECTED_SIZEOF_INT 4
#define EXPECTED_SIZEOF_PTR 8
#define EXPECTED_SIZEOF_LLU 8
#define EXPECTED_SIZEOF_LPA 32

int main(void)
{
	int success = 1;

	if (sizeof(int) != EXPECTED_SIZEOF_INT)
	{
		printf("    sizeof(int): %lu bytes (expected %d bytes)\n",
		       sizeof(int), EXPECTED_SIZEOF_INT);
		success = 0;
	}

	if (sizeof(int *) != EXPECTED_SIZEOF_PTR)
	{
		printf("    sizeof(int*): %lu bytes (expected %d bytes)\n",
		       sizeof(int *), EXPECTED_SIZEOF_PTR);
		success = 0;
	}

	if (sizeof(int **) != EXPECTED_SIZEOF_PTR)
	{
		printf("    sizeof(int**): %lu bytes (expected %d bytes)\n",
		       sizeof(int **), EXPECTED_SIZEOF_PTR);
		success = 0;
	}

	if (sizeof(long long unsigned int) < EXPECTED_SIZEOF_LLU)
	{
		printf("    sizeof(long long unsigned int): %lu bytes (expected %d bytes)\n",
		       sizeof(int), EXPECTED_SIZEOF_LLU);
		success = 0;
	}

	if (sizeof(LPA) != EXPECTED_SIZEOF_LPA)
	{
		printf("    sizeof(LonelyPartyArray) %lu bytes (expected %d bytes)\n",
		       sizeof(int), EXPECTED_SIZEOF_LPA);
		success = 0;
	}

	if (success)
	{
		printf("  Your system's sizeof() values are within normal parameters. Hooray!\n");
	}
	else
	{
		printf("\n");
		printf("  This might cause output mismatches for test cases involving\n");
		printf("  getArraySizeInBytes() and getCurrentSizeInBytes(). Please\n");
		printf("  consider testing your code on a different system.\n");
	}

	return 0;
}
