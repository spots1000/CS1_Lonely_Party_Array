// Sean Szumlanski
// COP 3502, Fall 2018

// ==============================
// LonelyPartyArray: testcase06.c
// ==============================
// Tests various aspects of delete() functionality. This builds on testcase05.c.


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

	// Call set() twice on same index.
	if (set(party, 14, 100) != LPA_SUCCESS)
		failwhale("(Err0.01) set() check failed.");
	if (set(party, 14, 100) != LPA_SUCCESS)
		failwhale("(Err0.02) set() check failed.");
	if (set(party, 14, 100) != LPA_SUCCESS)
		failwhale("(Err0.03) set() check failed.");

	// Check that the struct is set up correctly to begin with.
	if (party == NULL)
		failwhale("(Err1.01) NULL check failed.");
	if (party->size != 1)
		failwhale("(Err1.02) party->size check failed.");
	if (party->num_fragments != 3)
		failwhale("(Err1.03) party->num_fragments check failed.");
	if (party->fragment_length != 12)
		failwhale("(Err1.04) party->fragment_length check failed.");
	if (party->num_active_fragments != 1)
		failwhale("(Err1.05) party->num_active_fragments check failed.");
	if (party->fragments == NULL)
		failwhale("(Err1.06) party->fragments check failed.");
	if (party->fragment_sizes == NULL)
		failwhale("(Err1.07) party->fragment_sizes check failed.");

	for (i = 0; i < 3; i++)
	{
		if (i != 1 && party->fragments[i] != NULL)
			failwhale("(Err1.08a) party->fragments[i] check failed.");
		if (i == 1 && party->fragments[i] == NULL)
			failwhale("(Err1.08b) party->fragments[i] check failed.");
	}

	for (i = 0; i < 3; i++)
	{
		if (i != 1 && party->fragment_sizes[i] != 0)
			failwhale("(Err1.09a) party->fragment_sizes[i] check failed.");
		if (i == 1 && party->fragment_sizes[i] != 1)
			failwhale("(Err1.09b) party->fragment_sizes[i] check failed.");
	}

	for (i = 0; i < 12; i++)
	{
		if (i != 2 && party->fragments[1][i] != UNUSED)
			failwhale("(Err1.10a) party->fragment_sizes[1][i] check failed.");
		if (i == 2 && party->fragments[1][i] != 100)
			failwhale("(Err1.10b) party->fragment_sizes[1][i] check failed.");
	}

	// Check that delete() doesn't cause the deallocation of a fragment when
	// attempting to delete a cell that is actually UNUSED.
	if (delete(party, 15) != LPA_FAILURE)
		failwhale("(Err2.01) delete() check failed.");
	if (party->size != 1)
		failwhale("(Err2.02) party->size check failed.");
	if (party->num_active_fragments != 1)
		failwhale("(Err2.03) party->num_active_fragments check failed.");
	if (party->fragment_sizes[1] != 1)
		failwhale("(Err2.04) party->fragment_sizes check failed.");
	if (party->fragments[1] == NULL)
		failwhale("(Err2.05) party->fragments check failed.");

	// Insert two new elements. Then check that calling delete() on the same
	// element many times in a row doesn't cause the LPA size or fragment size
	// to be reduced many times, resulting in a fragment deallocation.
	if (set(party, 13, 100) != LPA_SUCCESS)
		failwhale("(Err2.06) set() check failed.");
	if (set(party, 15, 100) != LPA_SUCCESS)
		failwhale("(Err2.07) set() check failed.");
	if (delete(party, 15) != LPA_SUCCESS)
		failwhale("(Err2.08) delete() check failed.");
	if (delete(party, 15) != LPA_FAILURE)
		failwhale("(Err2.09) delete() check failed.");
	if (delete(party, 15) != LPA_FAILURE)
		failwhale("(Err2.09) delete() check failed.");
	if (delete(party, 15) != LPA_FAILURE)
		failwhale("(Err2.09) delete() check failed.");

	// Also check that calling delete() on invalid indices produces the correct
	// output and doesn't unsettle the struct's member values. These first two
	// calls should not produce "invalid access" messages because the indices
	// are within bounds (even though they refer to UNUSED cells).
	if (delete(party, 0) != LPA_FAILURE)
		failwhale("(Err2.01) delete() check failed.");
	if (delete(party, 35) != LPA_FAILURE)
		failwhale("(Err2.02) delete() check failed.");
	if (delete(party, 36) != LPA_FAILURE)
		failwhale("(Err2.03) delete() check failed.");
	if (delete(party, 48) != LPA_FAILURE)
		failwhale("(Err2.04) delete() check failed.");
	if (delete(party, 49) != LPA_FAILURE)
		failwhale("(Err2.05) delete() check failed.");
	if (delete(party, 59) != LPA_FAILURE)
		failwhale("(Err2.06) delete() check failed.");

	// Check that the struct is still set up correctly.
	if (party == NULL)
		failwhale("(Err3.01) NULL check failed.");
	if (party->size != 2)
		failwhale("(Err3.02) party->size check failed.");
	if (party->num_fragments != 3)
		failwhale("(Err3.03) party->num_fragments check failed.");
	if (party->fragment_length != 12)
		failwhale("(Err3.04) party->fragment_length check failed.");
	if (party->num_active_fragments != 1)
		failwhale("(Err3.05) party->num_active_fragments check failed.");
	if (party->fragments == NULL)
		failwhale("(Err3.06) party->fragments check failed.");
	if (party->fragment_sizes == NULL)
		failwhale("(Err3.07) party->fragment_sizes check failed.");

	for (i = 0; i < 3; i++)
	{
		if (i != 1 && party->fragments[i] != NULL)
			failwhale("(Err3.08a) party->fragments[i] check failed.");
		if (i == 1 && party->fragments[i] == NULL)
			failwhale("(Err3.08b) party->fragments[i] check failed.");
	}

	for (i = 0; i < 3; i++)
	{
		if (i != 1 && party->fragment_sizes[i] != 0)
			failwhale("(Err3.09a) party->fragment_sizes[i] check failed.");
		if (i == 1 && party->fragment_sizes[i] != 2)
			failwhale("(Err3.09b) party->fragment_sizes[i] check failed.");
	}

	for (i = 0; i < 12; i++)
	{
		if (i != 1 && i != 2 && party->fragments[1][i] != UNUSED)
			failwhale("(Err3.10a) party->fragment_sizes[1][i] check failed.");
		if ((i == 1 || i == 2) && party->fragments[1][i] != 100)
			failwhale("(Err3.10b) party->fragment_sizes[1][i] check failed.");
	}

	destroyLonelyPartyArray(party);

	return 0;
}
