#ifndef __LONELYPARTYARRAY_H
#define __LONELYPARTYARRAY_H


// Directives and Definitions

#include <limits.h>

#define UNUSED INT_MIN
#define LPA_SUCCESS -1911318927
#define LPA_FAILURE -1911318928

typedef struct LonelyPartyArray
{
	int size;                  // number of occupied cells across all fragments
	int num_fragments;         // number of fragments (arrays) in this struct
	int fragment_length;       // number of cells per fragment
	int num_active_fragments;  // number of allocated (non-NULL) fragments
	int **fragments;           // array of pointers to individual fragments
	int *fragment_sizes;       // stores number of used cells in each fragment
} LonelyPartyArray;

typedef LonelyPartyArray LPA;


// Functional Prototypes

LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length);

LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party);

LonelyPartyArray *cloneLonelyPartyArray(LonelyPartyArray *party);  // optional (bonus)

int set(LonelyPartyArray *party, int index, int key);

int get(LonelyPartyArray *party, int index);

int delete(LonelyPartyArray *party, int index);

int containsKey(LonelyPartyArray *party, int key);

int isSet(LonelyPartyArray *party, int index);

int printIfValid(LonelyPartyArray *party, int index);

LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party);

int getSize(LonelyPartyArray *party);

int getCapacity(LonelyPartyArray *party);

int getAllocatedCellCount(LonelyPartyArray *party);

long long unsigned int getArraySizeInBytes(LonelyPartyArray *party);

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party);

double difficultyRating(void);

double hoursSpent(void);


#endif
