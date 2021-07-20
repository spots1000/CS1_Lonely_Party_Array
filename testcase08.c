// Sean Szumlanski
// COP 3502, Fall 2018

// ==============================
// LonelyPartyArray: testcase08.c
// ==============================
// Tests various aspects of printIfValid() functionality.


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
	int i;
	LPA *party = createLonelyPartyArray(3, 12);

	// set() a few elements.
	if (set(party, 35, 93899) != LPA_SUCCESS)
		failwhale("(Err0.03) set() check failed.");
	if (set(party, 8, 412) != LPA_SUCCESS)
		failwhale("(Err0.02) set() check failed.");
	if (set(party, 11, 83644) != LPA_SUCCESS)
		failwhale("(Err0.01) set() check failed.");

	// Check basic printIfValid() functionality.
	for (i = -2; i <= 37; i++)
	{
		if (i == 8 || i == 11 || i == 35)
			continue;
		if (printIfValid(party, i) != LPA_FAILURE)
			failwhale("(Err1.01) printIfValid() check failed.");
	}

	// Call printIfValid() multiple times to ensure it isn't deleting or
	// modifying cells.
	if (printIfValid(party, 8) != LPA_SUCCESS)
		failwhale("(Err2.01) printIfValid() check failed.");
	if (printIfValid(party, 8) != LPA_SUCCESS)
		failwhale("(Err2.02) printIfValid() check failed.");
	if (printIfValid(party, 11) != LPA_SUCCESS)
		failwhale("(Err2.03) printIfValid() check failed.");
	if (printIfValid(party, 11) != LPA_SUCCESS)
		failwhale("(Err2.04) printIfValid() check failed.");
	if (printIfValid(party, 35) != LPA_SUCCESS)
		failwhale("(Err2.05) printIfValid() check failed.");

	destroyLonelyPartyArray(party);

	return 0;
}
