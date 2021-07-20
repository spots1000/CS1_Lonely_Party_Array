// Sean Szumlanski
// COP 3502, Fall 2018

// ==============================
// LonelyPartyArray: testcase15.c
// ==============================
// Various NULL pointer checks.


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
	set(party, 34, 1);
	set(party, 83, 2);
	set(party, 92, 5);
	set(party, 95, 8);
	set(party, 98, 6);
	set(party, 109, 3);

	// NULL checks. Note that printIfValid() should not grumble if it receives
	// a NULL party pointer.
	if (set(NULL, 14, 100) != LPA_FAILURE)
		failwhale("NULL check for set() function failed.");
	if (get(NULL, 14) != LPA_FAILURE)
		failwhale("NULL check for get() function failed.");
	if (delete(NULL, 14) != LPA_FAILURE)
		failwhale("NULL check for delete() function failed.");
	if (printIfValid(NULL, 14) != LPA_FAILURE)
		failwhale("NULL check for printIfValid() function failed.");

	destroyLonelyPartyArray(party);

	return 0;
}
