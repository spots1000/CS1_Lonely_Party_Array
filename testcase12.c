// Sean Szumlanski
// COP 3502, Fall 2018

// ==============================
// LonelyPartyArray: testcase12.c
// ==============================
// A test of various stat-related functions for a larger lonely party array
// (capacity: 100 million elements).


#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

int main(void)
{
	LPA *party = createLonelyPartyArray(10000, 10000);

	// Set a few elements.
	set(party, 58105, 987);
	set(party, 27272, 534);
	set(party, 624362, 63);
	set(party, 72477, 166);
	set(party, 825682, 93);

	// Print a few elements. Recall that printIfValid() does not grumble about
	// invalid indices; it just quietly fails.
	printIfValid(party, 72477);   // 166
	printIfValid(party, 27272);   // 534
	printIfValid(party, -1);      // invalid
	printIfValid(party, 825682);  // 93
	printIfValid(party, 624362);  // 63
	printIfValid(party, 9888);    // invalid
	printIfValid(party, 19888);   // invalid
	printIfValid(party, 58105);   // 987
	printIfValid(party, 465451);  // invalid
	printIfValid(party, 9849136); // invalid

	// Print some stats.
	printf("Size: %d\n", getSize(party));
	printf("Capacity: %d\n", getCapacity(party));
	printf("Allocated Cells: %d\n", getAllocatedCellCount(party));
	printf("Traditional Array Size: %llu bytes\n", getArraySizeInBytes(party));
	printf("Lonely Party Array Size: %llu bytes\n", getCurrentSizeInBytes(party));

	destroyLonelyPartyArray(party);

	return 0;
}
