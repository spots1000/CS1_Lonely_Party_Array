// Sean Szumlanski
// COP 3502, Fall 2018

// ==============================
// LonelyPartyArray: testcase14.c
// ==============================
// Tests the functionality of resetLonelyPartyArray().


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

// Check the struct contents and call failwhale() if anything is out of sorts.
void party_check_nonempty(LonelyPartyArray *party)
{
	int i;

	// Check struct setup.
	if (party == NULL)
		failwhale("(Err1.01) NULL check failed.");
	if (party->size != 6)
		failwhale("(Err1.02) party->size check failed.");
	if (party->num_fragments != 11)
		failwhale("(Err1.03) party->num_fragments check failed.");
	if (party->fragment_length != 10)
		failwhale("(Err1.04) party->fragment_length check failed.");
	if (party->num_active_fragments != 4)
		failwhale("(Err1.05) party->num_active_fragments check failed.");
	if (party->fragments == NULL)
		failwhale("(Err1.06) party->fragments check failed.");
	if (party->fragment_sizes == NULL)
		failwhale("(Err1.07) party->fragment_sizes check failed.");

	// Check fragments. Only fragments 3, 8, 9, and 10 should be active.
	for (i = 0; i < 11; i++)
	{
		if ((i != 3 && i != 8 && i != 9 && i != 10) && party->fragments[i] != NULL)
			failwhale("(Err1.08a) party->fragments[i] check failed.");
		if ((i == 3 || i == 8 || i == 9 || i == 10) && party->fragments[i] == NULL)
			failwhale("(Err1.08b) party->fragments[i] check failed.");
	}
	// Check contents of fragment 3.
	for (i = 0; i < 10; i++)
	{
		if (i != 4 && party->fragments[3][i] != UNUSED)
			failwhale("(Err1.09a) party->fragments[i] check failed.");
		if (i == 4 && party->fragments[3][i] != 1)
			failwhale("(Err1.09b) party->fragments[i] check failed.");
	}
	// Check contents of fragment 8.
	for (i = 0; i < 10; i++)
	{
		if (i != 3 && party->fragments[8][i] != UNUSED)
			failwhale("(Err1.10a) party->fragments[i] check failed.");
		if (i == 3 && party->fragments[8][i] != 2)
			failwhale("(Err1.10b) party->fragments[i] check failed.");
	}
	// Check contents of fragment 9.
	for (i = 0; i < 10; i++)
	{
		if ((i != 2 && i != 5 && i != 8) && party->fragments[9][i] != UNUSED)
			failwhale("(Err1.11a) party->fragments[i] check failed.");
		if (i == 2 && party->fragments[9][i] != 5)
			failwhale("(Err1.11b) party->fragments[i] check failed.");
		if (i == 5 && party->fragments[9][i] != 8)
			failwhale("(Err1.11c) party->fragments[i] check failed.");
		if (i == 8 && party->fragments[9][i] != 6)
			failwhale("(Err1.11d) party->fragments[i] check failed.");
	}
	// Check contents of fragment 10.
	for (i = 0; i < 10; i++)
	{
		if (i != 9 && party->fragments[10][i] != UNUSED)
			failwhale("(Err1.12a) party->fragments[i] check failed.");
		if (i == 9 && party->fragments[10][i] != 3)
			failwhale("(Err1.12b) party->fragments[i] check failed.");
	}
}

// Check the struct contents and call failwhale() if anything is out of sorts.
void party_check_empty(LonelyPartyArray *party)
{
	int i;

	// Check struct setup.
	if (party == NULL)
		failwhale("(Err2.01) NULL check failed.");
	if (party->size != 0)
		failwhale("(Err2.02) party->size check failed.");
	if (party->num_fragments != 11)
		failwhale("(Err2.03) party->num_fragments check failed.");
	if (party->fragment_length != 10)
		failwhale("(Err2.04) party->fragment_length check failed.");
	if (party->num_active_fragments != 0)
		failwhale("(Err2.05) party->num_active_fragments check failed.");
	if (party->fragments == NULL)
		failwhale("(Err2.06) party->fragments check failed.");
	if (party->fragment_sizes == NULL)
		failwhale("(Err2.07) party->fragment_sizes check failed.");

	// Check that all fragments are inactive.
	for (i = 0; i < 11; i++)
		if (party->fragments[i] != NULL)
			failwhale("(Err2.08a) party->fragments[i] check failed.");
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

	// Check structure and contents of this non-empty lonely party array.
	party_check_nonempty(party);

	// Hold on to these pointers to make sure they're not lost or reset when
	// resetLonelyPartyArray() is called.
	ptr1 = party->fragments;
	ptr2 = party->fragment_sizes;

	// Now for the main event: Reset the lonely party array.
	resetLonelyPartyArray(party);

	// Check structure and contents of this empty lonely party array.
	party_check_empty(party);

	if (party->fragments != ptr1)
		failwhale("(Err3.00) party->fragments check failed.");
	if (party->fragment_sizes != ptr2)
		failwhale("(Err3.01) party->fragment_sizes check failed.");

	destroyLonelyPartyArray(party);

	return 0;
}
