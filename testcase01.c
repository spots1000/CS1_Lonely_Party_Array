// Sean Szumlanski
// COP 3502, Fall 2018

// ==============================
// LonelyPartyArray: testcase01.c
// ==============================
// This test case is a simple boundary check to make sure the difficultyRating()
// function is implemented correctly.


#include <stdio.h>
#include "LonelyPartyArray.h"

int main(void)
{
	if (difficultyRating() < 1.0 || difficultyRating() > 5.0)
		printf("fail whale :(\n");
	else
		printf("Hooray!\n");

	return 0;
}
