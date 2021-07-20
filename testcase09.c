// Sean Szumlanski
// COP 3502, Fall 2018

// ==============================
// LonelyPartyArray: testcase09.c
// ==============================
// A hodgpodge of calls to set(), delete(), and printIfValid().


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

	// Toggle.
	if (set(party, 14, 28) != LPA_SUCCESS)
		failwhale("(Err0.01) set() check failed.");
	if (delete(party, 14) != LPA_SUCCESS)
		failwhale("(Err0.02) delete() check failed.");
	if (set(party, 14, 28) != LPA_SUCCESS)
		failwhale("(Err0.03) set() check failed on.");
	if (delete(party, 14) != LPA_SUCCESS)
		failwhale("(Err0.04) delete() check failed.");
	if (set(party, 14, 28) != LPA_SUCCESS)
		failwhale("(Err0.05) set() check failed.");
	if (delete(party, 14) != LPA_SUCCESS)
		failwhale("(Err0.06) delete() check failed.");

	// Check that set() is capable of overwriting an existing value.
	if (set(party, 14, 28) != LPA_SUCCESS)
		failwhale("(Err1.01) set() check failed.");
	if (printIfValid(party, 14) != LPA_SUCCESS)
		failwhale("(Err1.02) printIfValid() check failed.");
	if (set(party, 14, 56) != LPA_SUCCESS)
		failwhale("(Err1.03) set() check failed.");
	if (printIfValid(party, 14) != LPA_SUCCESS)
		failwhale("(Err1.04) printIfValid() check failed.");

	// Check that calling set() on the same index twice doesn't increase the
	// size variables twice.
	if (set(party, 14, 112) != LPA_SUCCESS)
		failwhale("(Err2.01) set() check failed.");
	if (printIfValid(party, 14) != LPA_SUCCESS)
		failwhale("(Err2.02) printIfValid() check failed.");
	if (set(party, 14, 224) != LPA_SUCCESS)
		failwhale("(Err2.03) set() check failed.");
	if (printIfValid(party, 14) != LPA_SUCCESS)
		failwhale("(Err2.04) printIfValid() check failed.");
	if (delete(party, 14) != LPA_SUCCESS)
		failwhale("(Err2.05) delete() check failed.");
	if (party->fragments[1] != NULL)
		failwhale("(Err2.06) fragment deallocation check failed.");
	if (printIfValid(party, 14) != LPA_FAILURE)
		failwhale("(Err2.07) printIfValid() check failed.");
	if (delete(party, 14) != LPA_FAILURE)
		failwhale("(Err2.08) delete() check failed.");
	if (printIfValid(party, 14) != LPA_FAILURE)
		failwhale("(Err2.09) printIfValid() check failed.");

	destroyLonelyPartyArray(party);

	return 0;
}
