// Sean Szumlanski
// COP 3502, Fall 2018

// ==============================
// LonelyPartyArray: testcase13.c
// ==============================
// A test of various stat-related functions for a very large lonely party array
// (capacity: 2 billion elements).


#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

int main(void)
{
	LPA *party = createLonelyPartyArray(20000, 100000);

	// Set a few elements.
	set(party, 58105, 987);
	set(party, 27272, 534);
	set(party, 624362, 63);
	set(party, 72477, 166);
	set(party, 825682, 93);
	set(party, 2000000000, 9816);  // invalid index
	set(party, 2000000001, 9329);  // invalid index
	set(party, 1999999999, 9455);

	// Print a few elements. Recall that printIfValid() does not grumble about
	// invalid indices; it just quietly fails.
	printIfValid(party, 72477);      // 166
	printIfValid(party, 27272);      // 534
	printIfValid(party, -1);         // invalid
	printIfValid(party, 825682);     // 93
	printIfValid(party, 624362);     // 63
	printIfValid(party, 9888);       // invalid
	printIfValid(party, 19888);      // invalid
	printIfValid(party, 58105);      // 987
	printIfValid(party, 465451);     // invalid
	printIfValid(party, 9849136);    // invalid
	printIfValid(party, 1999999999); // 9455
	printIfValid(party, 2000000001); // invalid
	printIfValid(party, 2055555555); // invalid

	// Print some stats.
	printf("Size: %d\n", getSize(party));
	printf("Capacity: %d\n", getCapacity(party));
	printf("Allocated Cells: %d\n", getAllocatedCellCount(party));
	printf("Traditional Array Size: %llu bytes\n", getArraySizeInBytes(party));
	printf("Lonely Party Array Size: %llu bytes\n", getCurrentSizeInBytes(party));

	destroyLonelyPartyArray(party);

	return 0;
}
