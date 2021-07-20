// Sean Szumlanski
// COP 3502, Fall 2018

// ==============================
// LonelyPartyArray: testcase07.c
// ==============================
// Tests the ability of delete() to cause a fragment deallocation. This builds
// on testcase06.c.


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
	if (set(party, 14, 200) != LPA_SUCCESS)
		failwhale("(Err0.01) set() check failed.");
	if (set(party, 14, 100) != LPA_SUCCESS)
		failwhale("(Err0.02) set() check failed.");
	if (set(party, 15, 100) != LPA_SUCCESS)
		failwhale("(Err0.03) set() check failed.");
	if (set(party, 26, 100) != LPA_SUCCESS)
		failwhale("(Err0.04) set() check failed.");
	if (set(party, 27, 100) != LPA_SUCCESS)
		failwhale("(Err0.05) set() check failed.");

	// Check that the struct is set up correctly to begin with.
	if (party == NULL)
		failwhale("(Err1.01) NULL check failed.");
	if (party->size != 4)
		failwhale("(Err1.02) party->size check failed.");
	if (party->num_fragments != 3)
		failwhale("(Err1.03) party->num_fragments check failed.");
	if (party->fragment_length != 12)
		failwhale("(Err1.04) party->fragment_length check failed.");
	if (party->num_active_fragments != 2)
		failwhale("(Err1.05) party->num_active_fragments check failed.");
	if (party->fragments == NULL)
		failwhale("(Err1.06) party->fragments check failed.");
	if (party->fragment_sizes == NULL)
		failwhale("(Err1.07) party->fragment_sizes check failed.");

	for (i = 0; i < 3; i++)
	{
		// Fragment 0 should be NULL. The other two should be non-NULL.
		if (i == 0 && party->fragments[i] != NULL)
			failwhale("(Err1.08a) party->fragments[i] check failed.");
		if (i != 0 && party->fragments[i] == NULL)
			failwhale("(Err1.08b) party->fragments[i] check failed.");
	}

	for (i = 0; i < 3; i++)
	{
		// Fragment 0 has no elements. Fragments 1 and 2 have 2 elements.
		if (i == 0 && party->fragment_sizes[i] != 0)
			failwhale("(Err1.09a) party->fragment_sizes[i] check failed.");
		if (i != 0 && party->fragment_sizes[i] != 2)
			failwhale("(Err1.09b) party->fragment_sizes[i] check failed.");
	}

	// Check fragments 1 and 2.
	for (i = 0; i < 12; i++)
	{
		if ((i != 2 && i != 3) && party->fragments[1][i] != UNUSED)
			failwhale("(Err1.10a) party->fragment_sizes[1][i] check failed.");
		if ((i == 2 || i == 3) && party->fragments[1][i] != 100)
			failwhale("(Err1.10b) party->fragment_sizes[1][i] check failed.");

		if ((i != 2 && i != 3) && party->fragments[2][i] != UNUSED)
			failwhale("(Err1.10c) party->fragment_sizes[2][i] check failed.");
		if ((i == 2 || i == 3) && party->fragments[2][i] != 100)
			failwhale("(Err1.10d) party->fragment_sizes[2][i] check failed.");
	}

	// These should not cause fragment deallocation.
	if (delete(party, 26) != LPA_SUCCESS)
		failwhale("(Err2.01) delete() check failed.");
	if (delete(party, 26) != LPA_FAILURE)
		failwhale("(Err2.02) delete() check failed.");
	if (delete(party, 26) != LPA_FAILURE)
		failwhale("(Err2.03) delete() check failed.");
	if (delete(party, 28) != LPA_FAILURE)
		failwhale("(Err2.04) delete() check failed.");
	if (delete(party, 28) != LPA_FAILURE)
		failwhale("(Err2.05) delete() check failed.");
	if (delete(party, 28) != LPA_FAILURE)
		failwhale("(Err2.06) delete() check failed.");

	// These should trigger fragment deallocation.
	if (delete(party, 15) != LPA_SUCCESS)
		failwhale("(Err2.01) delete() check failed.");
	if (delete(party, 14) != LPA_SUCCESS)
		failwhale("(Err2.02) party->size check failed.");

	// Check that the struct is still set up correctly.
	if (party == NULL)
		failwhale("(Err3.01) NULL check failed.");
	if (party->size != 1)
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
		// Fragment 2 should still be active.
		if (i != 2 && party->fragments[i] != NULL)
			failwhale("(Err3.08a) party->fragments[i] check failed.");
		if (i == 2 && party->fragments[i] == NULL)
			failwhale("(Err3.08b) party->fragments[i] check failed.");
	}

	for (i = 0; i < 3; i++)
	{
		// Fragment 2 should still have a single active element.
		if (i != 2 && party->fragment_sizes[i] != 0)
			failwhale("(Err3.09a) party->fragment_sizes[i] check failed.");
		if (i == 2 && party->fragment_sizes[i] != 1)
			failwhale("(Err3.09b) party->fragment_sizes[i] check failed.");
	}

	for (i = 0; i < 12; i++)
	{
		// Fragment 2's active element (100) should be at index 3.
		if (i != 3 && party->fragments[2][i] != UNUSED)
			failwhale("(Err3.10a) party->fragment_sizes[2][i] check failed.");
		if (i == 3 && party->fragments[2][i] != 100)
			failwhale("(Err3.10b) party->fragment_sizes[2][i] check failed.");
	}

	destroyLonelyPartyArray(party);

	return 0;
}
