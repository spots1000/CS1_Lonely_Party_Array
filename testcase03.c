// Sean Szumlanski
// COP 3502, Fall 2018

// ==============================
// LonelyPartyArray: testcase03.c
// ==============================
// Basic check to ensure createLonelyPartyArray() is initializing everything
// correctly.


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

	if (party == NULL)
		failwhale("(Err01) NULL check failed.");
	if (party->size != 0)
		failwhale("(Err02) party->size check failed.");
	if (party->num_fragments != 3)
		failwhale("(Err03) party->num_fragments check failed.");
	if (party->fragment_length != 12)
		failwhale("(Err04) party->fragment_length check failed.");
	if (party->num_active_fragments != 0)
		failwhale("(Err05) party->num_active_fragments check failed.");
	if (party->fragments == NULL)
		failwhale("(Err06) party->fragments check failed.");
	if (party->fragment_sizes == NULL)
		failwhale("(Err07) party->fragment_sizes check failed.");

	for (i = 0; i < 3; i++)
		if (party->fragments[i] != NULL)
			failwhale("(Err08) party->fragments[i] check failed.");

	for (i = 0; i < 3; i++)
		if (party->fragment_sizes[i] != 0)
			failwhale("(Err09) party->fragment_sizes[i] check failed.");

	destroyLonelyPartyArray(party);

	return 0;
}
