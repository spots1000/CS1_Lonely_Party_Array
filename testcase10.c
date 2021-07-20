// Sean Szumlanski
// COP 3502, Fall 2018

// ==============================
// LonelyPartyArray: testcase10.c
// ==============================
// A small test of various stat-related functions.


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
	LPA *party = createLonelyPartyArray(3, 12);

	// Set a single element.
	if (set(party, 14, 28) != LPA_SUCCESS)
		failwhale("(Err0.01) set() check failed.");

	// Print some stats.
	printf("Size: %d\n", getSize(party));
	printf("Capacity: %d\n", getCapacity(party));
	printf("Allocated Cells: %d\n", getAllocatedCellCount(party));
	printf("Traditional Array Size: %llu bytes\n", getArraySizeInBytes(party));
	printf("Lonely Party Array Size: %llu bytes\n", getCurrentSizeInBytes(party));

	destroyLonelyPartyArray(party);

	return 0;
}
