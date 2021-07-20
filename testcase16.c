// Sean Szumlanski
// COP 3502, Fall 2018

// ==============================
// LonelyPartyArray: testcase16.c
// ==============================
// Various negative index checks.


#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

// This function exist with status 0 so as not to give a false indication of a
// segmentation fault.
void failwhale(char *err_msg)
{
	printf("[failwhale]: %s\n", err_msg);
	exit(0);
}

int main(void)
{
	LPA *party = createLonelyPartyArray(11, 10);

	int **ptr1;
	int *ptr2;

	// Set a few elements.
	printf("\n");
	set(party, 34, 1);
	set(party, 83, 2);
	set(party, 92, 5);
	set(party, 95, 8);
	set(party, 98, 6);
	set(party, 109, 3);

	// Negative index checks. Note that printIfValid() should not grumble if it
	// receives a negative index.
	printf("\n");
	if (set(party, -1, 100) != LPA_FAILURE)
		failwhale("Negative index check for set() function failed.");
	if (get(party, -1) != LPA_FAILURE)
		failwhale("Negative index check for get() function failed.");
	if (delete(party, -1) != LPA_FAILURE)
		failwhale("Negative index check for delete() function failed.");
	if (printIfValid(party, -1) != LPA_FAILURE)
		failwhale("Negative index check for printIfValid() function failed.");

	// Negative index checks. Again, printIfValid() should not grumble if it
	// receives a negative index.
	printf("\n");
	if (set(party, -9, 100) != LPA_FAILURE)
		failwhale("Negative index check for set() function failed.");
	if (get(party, -9) != LPA_FAILURE)
		failwhale("Negative index check for get() function failed.");
	if (delete(party, -9) != LPA_FAILURE)
		failwhale("Negative index check for delete() function failed.");
	if (printIfValid(party, -9) != LPA_FAILURE)
		failwhale("Negative index check for printIfValid() function failed.");

	// Negative index checks. Again, printIfValid() should not grumble if it
	// receives a negative index.
	printf("\n");
	if (set(party, -10, 100) != LPA_FAILURE)
		failwhale("Negative index check for set() function failed.");
	if (get(party, -10) != LPA_FAILURE)
		failwhale("Negative index check for get() function failed.");
	if (delete(party, -10) != LPA_FAILURE)
		failwhale("Negative index check for delete() function failed.");
	if (printIfValid(party, -10) != LPA_FAILURE)
		failwhale("Negative index check for printIfValid() function failed.");

	// Negative index checks. Again, printIfValid() should not grumble if it
	// receives a negative index.
	printf("\n");
	if (set(party, -11, 100) != LPA_FAILURE)
		failwhale("Negative index check for set() function failed.");
	if (get(party, -11) != LPA_FAILURE)
		failwhale("Negative index check for get() function failed.");
	if (delete(party, -11) != LPA_FAILURE)
		failwhale("Negative index check for delete() function failed.");
	if (printIfValid(party, -11) != LPA_FAILURE)
		failwhale("Negative index check for printIfValid() function failed.");

	// Negative index checks. Again, printIfValid() should not grumble if it
	// receives a negative index.
	printf("\n");
	if (set(party, -321, 100) != LPA_FAILURE)
		failwhale("Negative index check for set() function failed.");
	if (get(party, -321) != LPA_FAILURE)
		failwhale("Negative index check for get() function failed.");
	if (delete(party, -321) != LPA_FAILURE)
		failwhale("Negative index check for delete() function failed.");
	if (printIfValid(party, -321) != LPA_FAILURE)
		failwhale("Negative index check for printIfValid() function failed.");

	// Clean up after yourself.
	printf("\n");
	destroyLonelyPartyArray(party);

	return 0;
}
