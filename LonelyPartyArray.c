/*
  Anthony Dalia
  an694448
  LonelyPartyArray - CS 1
*/

#include <stdio.h>
#include <stdlib.h>
#include "LonelyPartyArray.h"

LonelyPartyArray *createLonelyPartyArray(int num_fragments, int fragment_length)
{
  int i, **newFrag, *fragSizes;
  LonelyPartyArray *party = malloc(sizeof(LonelyPartyArray));

  //Set up the size of the array
  party->num_fragments = num_fragments;
  party->fragment_length = fragment_length;

  //Set up the active segment trackers
  party->num_active_fragments = 0;
  party->size = 0;

  //Dynamically allocate the fragments array
  newFrag = malloc(sizeof(int*) * num_fragments);

  //Populate the fragments array
  for (i=0; i<num_fragments;i++)
  {
    newFrag[i] = NULL;
  }

  party->fragments = newFrag;

  //Dynamically allocate the Fragment Sizes array
  fragSizes = malloc(sizeof(int) * num_fragments);

  //Populate the fragment sizes array
  for (i=0; i<num_fragments;i++)
  {
    fragSizes[i] = 0;
  }

  party->fragment_sizes = fragSizes;

  //Print the success statement
  printf("-> A new LonelyPartyArray has emerged from the void. (capacity: %d, fragments: %d)\n", (num_fragments*fragment_length), num_fragments);
  return party;
}

LonelyPartyArray *destroyLonelyPartyArray(LonelyPartyArray *party)
{
  int numFrags, i;

  //Check and make sure there is something for us to free
  if (party != NULL)
  {
    numFrags = party->num_fragments;

    //Free any allocated fragments
    for(i=0; i<numFrags; i++)
    {
      free(party->fragments[i]);
    }

    free(party->fragments);

    //Free the fragment size array
    free(party->fragment_sizes);

    //Free the remaining parts of the array
    free(party);

    //Print the output statement
    printf("-> The LonelyPartyArray has returned to the void.\n");
  }
  return NULL;
}


int set(LonelyPartyArray *party, int index, int key)
{
  int fragNum, fragSize, indexFrag, indexPos, i, lowIndex, highIndex;

  //Check for null inputs
  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in set().\n");
    return LPA_FAILURE;
  }

  fragNum = party->num_fragments;
  fragSize = party->fragment_length;

  //Do some math to determine what fragment and positiion the index maps to
  indexFrag = (int) (index / party->fragment_length);
  indexPos = (index - (indexFrag * party->fragment_length));

  //Check to ensure we are working with a valid fragment
  if (indexFrag >= party->num_fragments)
  {
    printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", index, indexFrag, indexPos);
    return LPA_FAILURE;
  }

  //Check to ensure we are working with a valid index
  if (indexPos < 0 || indexPos >= (indexFrag+1)*party->fragment_length)
  {
    printf("-> Bloop! Invalid access in set(). (index: %d, fragment: %d, offset: %d)\n", index, indexFrag, indexPos);
    return LPA_FAILURE;
  }

  //Check if that fragment is initialized or init it
  if (party->fragments[indexFrag] == NULL)
  {
    party->fragments[indexFrag] = malloc(sizeof(int)*fragSize);

    //Init the new fragment
    for(i=0; i < fragSize; i++)
    {
      party->fragments[indexFrag][i] = UNUSED;
    }

    //Update the struct to reflect the new fragment
    party->num_active_fragments++;

    //Do some math to determine the indecie range on this fragment
    lowIndex = (indexFrag)*fragSize;
    highIndex = lowIndex + (fragSize-1);

    //Report creation of the struct
    printf("-> Spawned fragment %d. (capacity: %d, indices: %d..%d)\n", indexFrag, fragSize, lowIndex, highIndex);
  }

  //Check if we need to increment the size part of the struct
  if (party->fragments[indexFrag][indexPos] == UNUSED)
  {
    party->size++;
    party->fragment_sizes[indexFrag]++;
  }

  //Store the key at the correct location
  party->fragments[indexFrag][indexPos] = key;

  return LPA_SUCCESS;
}


int get(LonelyPartyArray *party, int index)
{
  int fragNum, fragSize, indexFrag, indexPos, i, lowIndex, highIndex;

  //Check for null inputs
  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in get().\n");
    return LPA_FAILURE;
  }

  fragNum = party->num_fragments;
  fragSize = party->fragment_length;

  //Do some math to determine what fragment and positiion the index maps to
  indexFrag = (int) (index / party->fragment_length);
  indexPos = (index - (indexFrag * party->fragment_length));

  //Check to ensure we are working with a valid fragment
  if (indexFrag >= party->num_fragments)
  {
    printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", index, indexFrag, indexPos);
    return LPA_FAILURE;
  }

  //Check to ensure we are working with a valid index
  if (indexPos < 0 || indexPos >= (indexFrag+1)*party->fragment_length)
  {
    printf("-> Bloop! Invalid access in get(). (index: %d, fragment: %d, offset: %d)\n", index, indexFrag, indexPos);
    return LPA_FAILURE;
  }

  //Check to see if the fragment we need is initialized
  if (party->fragments[indexFrag] == NULL)
  {
    return UNUSED;
  }

  //Return the correct value
  return party->fragments[indexFrag][indexPos];
}

int delete(LonelyPartyArray *party, int index)
{
  int fragNum, fragSize, indexFrag, indexPos, i, lowIndex, highIndex;

  //Check for null inputs
  if (party == NULL)
  {
    printf("-> Bloop! NULL pointer detected in delete().\n");
    return LPA_FAILURE;
  }

  fragNum = party->num_fragments;
  fragSize = party->fragment_length;

  //Do some math to determine what fragment and positiion the index maps to
  indexFrag = (int) (index / party->fragment_length);
  indexPos = (index - (indexFrag * party->fragment_length));

  //Check to ensure we are working with a valid fragment
  if (indexFrag >= party->num_fragments)
  {
    printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", index, indexFrag, indexPos);
    return LPA_FAILURE;
  }

  //Check to ensure we are working with a valid index
  if (indexPos < 0 || indexPos >= (indexFrag+1)*party->fragment_length)
  {
    printf("-> Bloop! Invalid access in delete(). (index: %d, fragment: %d, offset: %d)\n", index, indexFrag, indexPos);
    return LPA_FAILURE;
  }

  //Check to see if the fragment we need is initialized
  if (party->fragments[indexFrag] == NULL)
  {
    //The fragment we have been taken to already doesnt exist
    return LPA_FAILURE;
  }

  //Delete a cell and update the struct
  if (party->fragments[indexFrag][indexPos] != UNUSED)
  {
    party->fragments[indexFrag][indexPos] = UNUSED;
    party->size--;
    party->fragment_sizes[indexFrag]--;
  }
  else
    return LPA_FAILURE;

  //See if we must delete the fragment and update the struct
  if (party->fragment_sizes[indexFrag] == 0)
  {
    //Free the array and update the struct
    free(party->fragments[indexFrag]);
    party->fragments[indexFrag] = NULL;
    party->num_active_fragments--;

    //Do some math to determine the indecie range on this fragment
    lowIndex = (indexFrag)*fragSize;
    highIndex = lowIndex + (fragSize-1);

    //Report deletion of the fragment
    printf("-> Deallocated fragment %d. (capacity: %d, indices: %d..%d)\n", indexFrag, fragSize, lowIndex, highIndex);
  }

  return LPA_SUCCESS;
}


int containsKey(LonelyPartyArray *party, int key)
{
  int curFrag, curIndex;

  //Check if the LPA we've been passed is invalid
  if(party == NULL || party->size == 0)
  {
    return 0;
  }

  //Loop through the fragments
  for (curFrag = 0; curFrag < party->num_fragments; curFrag++)
  {

    //Check if this fragment is active
    if (party->fragments != NULL && party->fragment_sizes[curFrag] > 0)
    {
      //Loop through the fragment
      for(curIndex = 0; curIndex < party->fragment_length; curIndex++)
      {
        if (party->fragments[curFrag][curIndex] == key)
          return 1;
      }
    }
  }

  //We did not find the key so return 0
  return 0;
}

int isSet(LonelyPartyArray *party, int index)
{

  int fragNum, fragSize, indexFrag, indexPos;

  //Check for null inputs
  if (party == NULL)
  {
    return 0;
  }

  fragNum = party->num_fragments;
  fragSize = party->fragment_length;

  //Do some math to determine what fragment and positiion the index maps to
  indexFrag = (int) (index / party->fragment_length);
  indexPos = (index - (indexFrag * party->fragment_length));

  //Check to ensure we are working with a valid fragment
  if (indexFrag >= party->num_fragments)
  {
    return 0;
  }

  //Check to ensure we are working with a valid index
  if (indexPos < 0 || indexPos >= (indexFrag+1)*party->fragment_length)
  {
    return 0;
  }

  //Check to see if the fragment we need is initialized
  if (party->fragments[indexFrag] == NULL)
  {
    //The fragment we have been taken to already doesnt exist
    return 0;
  }

  //Check to see if the index is set or not
  if (party->fragments[indexFrag][indexPos] != UNUSED)
    return 1;
  else
    return 0;
}


int printIfValid(LonelyPartyArray *party, int index)
{
  int fragNum, fragSize, indexFrag, indexPos;

  //Check for null inputs
  if (party == NULL)
  {
    return LPA_FAILURE;
  }

  fragNum = party->num_fragments;
  fragSize = party->fragment_length;

  //Do some math to determine what fragment and positiion the index maps to
  indexFrag = (int) (index / party->fragment_length);
  indexPos = (index - (indexFrag * party->fragment_length));

  //Check to ensure we are working with a valid fragment
  if (indexFrag >= party->num_fragments)
  {
    return LPA_FAILURE;
  }

  //Check to ensure we are working with a valid index
  if (indexPos < 0 || indexPos >= (indexFrag+1)*party->fragment_length)
  {
    return LPA_FAILURE;
  }

  //Check to see if the fragment we need is initialized
  if (party->fragments[indexFrag] == NULL)
  {
    //The fragment we have been taken to already doesnt exist
    return LPA_FAILURE;
  }

  //Print the correct integer if it is not unused
  if (party->fragments[indexFrag][indexPos] != UNUSED)
  {
    printf("%d\n", party->fragments[indexFrag][indexPos]);
    return LPA_SUCCESS;
  }

  return LPA_FAILURE;
}

LonelyPartyArray *resetLonelyPartyArray(LonelyPartyArray *party)
{
  int i, j;

  //Exit if we are working with a null array, just pass it back
  if ( party == NULL )
  {
    printf("-> Bloop! NULL pointer detected in resetLonelyPartyArray()\n");
    return party;
  }

  //Loop through the fragments array and free any allocated spaces
  for (i = 0; i < party->num_fragments; i++)
  {
    //Free the fragments array and update it
    free(party->fragments[i]);
    party->fragments[i] = NULL;

    //Update the fragment sizes array
    party->fragment_sizes[i] = 0;
  }

  //Update the values in the struct itself
  party->size = 0;
  party->num_active_fragments = 0;

  //Print the output
  printf("-> The LonelyPartyArray has returned to its nascent state. (capacity: %d, fragments: %d)\n", (party->num_fragments*party->fragment_length), party->num_fragments);
  return party;
}

int getSize(LonelyPartyArray *party)
{

  //Simply output the size we have logged if we are given a valid party
  if(party == NULL)
    return -1;
  else
    return party->size;
}

int getCapacity(LonelyPartyArray *party)
{

  //Check if party is valid
  if (party == NULL)
    return -1;

  //Return the capacity desired
  return ( party->num_fragments * party->fragment_length );

}

int getAllocatedCellCount(LonelyPartyArray *party)
{
  //Check if party is valid
  if (party == NULL)
    return -1;

  //Return the number of cells contained in active fragments
  return( party->num_active_fragments * party->fragment_length );
}

long long unsigned int getArraySizeInBytes(LonelyPartyArray *party)
{
  //Check if party is valid
  if (party == NULL)
    return -1;

  //Return the total number of cells in bytes of int memory
  return ( sizeof(int) * party->num_fragments * party->fragment_length);
}

long long unsigned int getCurrentSizeInBytes(LonelyPartyArray *party)
{
  long long unsigned int byteUsage = 0, i, j;

  //Check if party is valid
  if (party == NULL)
    return -1;

  //Add up the size of every principle variable in the LPA
  byteUsage += sizeof(*party);
  byteUsage += sizeof(party->size);
  byteUsage += sizeof(party->num_fragments);
  byteUsage += sizeof(party->fragment_length);
  byteUsage += sizeof(party->num_active_fragments);

  //Add up the size of all alocated ints in the LPA
  for(i = 0; i < party->num_fragments; i++)
  {
    byteUsage += sizeof(party->fragments[i]);
    byteUsage += sizeof(party->fragment_sizes[i]);

    if (party->fragments[i] != NULL)
    {
      for(j = 0; j < party->fragment_length; j++)
      {
        byteUsage += sizeof(party->fragments[i][j]);
      }
    }
  }

  //Return total that we counted - 8 to accoutn for overlap in the coutning process
  return (byteUsage - 8);
}

double difficultyRating(void)
{
  return 1.0; //Update me!
}

double hoursSpent(void)
{
  return 1.0; //Update me!
}

/*
//Bonus Funciton
LonelyPartyArray *cloneLonelyPartyArray(LonelyPartyArray *party)
{

}
*/
