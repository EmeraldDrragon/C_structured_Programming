//---------------------------------------------------------------------------------------------------------------------
// Election Simulator Program. There are 5 candidates, user enters their id's and votes
// and the program automatically calculates the winner.
//---------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#define NUMBER_OF_CANDIDATES 5

typedef struct _Candidate_
{
  char id_;
  int votes_;
  float percentage_of_votes_;
  bool winner_;
} Candidate;


//---------------------------------------------------------------------------------------------------------------------
/// searches for the candidate with the given id in the array of candidates
///
/// @param candidates an array of candidates
/// @param count the size of array of candidates
/// @param id the id to find
/// @return true if found or false if not
bool findId(Candidate candidates[], int count, char id);

//---------------------------------------------------------------------------------------------------------------------
/// checks if the input of id is valid
///
/// @param candidates an array of candidates
/// @param count the size of array of candidates
/// @param input user input
/// @return true if valid or false if not
bool validIdInput(Candidate candidates[], int count, char input);

//---------------------------------------------------------------------------------------------------------------------
/// function for id input
///
/// @param candidates an array of candidates
/// @param count the size of array of candidates
/// @return no return
void enterId(Candidate candidates[], int count);

//---------------------------------------------------------------------------------------------------------------------
/// checks if the input of integer is in bounds
///
/// @param input user input
/// @param lower_bound lower bound
/// @param upper_bound upper bound
/// @return true if it is or false if not
bool validIntInput(int input, int lower_bound, int upper_bound);

//---------------------------------------------------------------------------------------------------------------------
/// function for votes input
///
/// @param candidates an array of candidates
/// @param count the size of array of candidates
/// @return no return
void enterVotes(Candidate candidates[], int count);

//---------------------------------------------------------------------------------------------------------------------
/// function for confirmation input
///
/// @return true if yes false if no
bool enterInputConfirmation();

//---------------------------------------------------------------------------------------------------------------------
/// calculates percentages of votes for each candidate
///
/// @param candidates an array of candidates
/// @param count the size of array of candidates
/// @return no return
void calculatePercentageOfVotes(Candidate candidates[], int count);

//---------------------------------------------------------------------------------------------------------------------
/// prints election results
///
/// @param candidates an array of candidates
/// @param count the size of array of candidates
/// @return no return
void printElectionResults(Candidate candidates[], int count);

//---------------------------------------------------------------------------------------------------------------------
/// calculates for each candidate if this candidate is a winner or not
///
/// @param candidates an array of candidates
/// @param count the size of array of candidates
/// @return no return
void calculateWinners(Candidate candidates[], int count);

//---------------------------------------------------------------------------------------------------------------------
/// prints the winner(s) of the election and calculates if there is a tie
///
/// @param candidates an array of candidates
/// @param count the size of array of candidates
/// @return no return
void announceWinners(Candidate candidates[], int count);

//---------------------------------------------------------------------------------------------------------------------
/// main function contains the main logic of the Election Simulator Program
///
/// @return integer exit code
int main()
{
  printf("Welcome to the Election Simulator Program!\n");
  Candidate candidates[NUMBER_OF_CANDIDATES] = {0};
  enterId(candidates, NUMBER_OF_CANDIDATES);
  while(true)
  {
    enterVotes(candidates, NUMBER_OF_CANDIDATES);
    if(enterInputConfirmation())
    {
      break;
    }
  }
  printElectionResults(candidates, NUMBER_OF_CANDIDATES);
  announceWinners(candidates,NUMBER_OF_CANDIDATES);
  printf("\nThank you for using the Election Simulator Program!\n");

  return 0;
}

//---------------------------------------------------------------------------------------------------------------------
//functions

bool findId(Candidate candidates[], int count, char id)
{
  for(int i = 0; i < count; i++)
  {
    if(candidates[i].id_ == id)
    {
      return true;
    }
  }
  return false;
}

bool validIdInput(Candidate candidates[], int count, char input)
{
  if((input >= 'A' && input <= 'Z') || (input >= 'a' && input <= 'z'))
  {
    //check for id in use perhaps
    if(findId(candidates,count,input))
    {
      printf("[Error] This ID is already in use!\n");
      return false;
    }
    return true;
  }
  else
  {
    printf("[Error] This input is out of bounds!\n");
    return false;
  }
}

void enterId(Candidate candidates[], int count)
{
  for(int i = 0; i < count; i++)
  {
    char tempId;
    while(true)
    {
      printf("\nPlease enter an ID for candidate %d! (single letter only)\n",i + 1);
      printf(" > ");
      tempId = (char)getchar();
      while(getchar() != '\n');
      if(validIdInput(candidates,count,tempId))
      {
        candidates[i].id_ = tempId;
        break;
      }
    }
  }
}

bool validIntInput(int input, int lower_bound, int upper_bound)
{
  if(input >= lower_bound && input <= upper_bound)
  {
    return true;
  }
  else
  {
    printf("[Error] This input is out of bounds!\n");
    return false;
  }
}

void enterVotes(Candidate candidates[], int count)
{
  for(int i = 0; i < count; i++)
  {
    int tempVotes;
    while(true)
    {
      printf("\nPlease enter the amount of votes for candidate \"%c\"! (1 to 1000)\n", candidates[i].id_);
      printf(" > ");
      scanf("%d",&tempVotes);
      if(validIntInput(tempVotes, 1, 1000))
      {
        candidates[i].votes_ = tempVotes;
        break;
      }
    }
  }
}

bool enterInputConfirmation()
{
  int input;
  while(true)
  {
    printf("\nAre you sure the input is correct?\n");
    printf(" 1. Yes\n");
    printf(" 2. No\n");
    printf(" > ");
    scanf("%d",&input);
    if(validIntInput(input, 1, 2))
    {
      if(input == 1)
      {
        return true;
      }
      else
      {
        return false;
      }
    }
  }
}

void calculatePercentageOfVotes(Candidate candidates[], int count)
{
  int sum = 0;
  for(int i = 0; i < count; i++)
  {
    sum += candidates[i].votes_;
  }
  for(int i = 0; i < count; i++)
  {
    candidates[i].percentage_of_votes_ = (float)candidates[i].votes_ / (float)sum * 100;
  }
}

void printElectionResults(Candidate candidates[], int count)
{
  calculatePercentageOfVotes(candidates,count);
  printf("\nThe results of the election are:\n");
  for(int i = 0; i < count; i++)
  {
    printf(" - Candidate \"%c\": %.2f %% (%d votes).\n", candidates[i].id_, candidates[i].percentage_of_votes_, candidates[i].votes_);
  }
}

void calculateWinners(Candidate candidates[], int count)
{
  int max = 0;
  for(int i = 0; i < count; i++)
  {
    if(candidates[i].votes_ > max)
    {
      max = candidates[i].votes_;
    }
  }
  for(int i = 0; i < count; i++)
  {
    if(candidates[i].votes_ == max)
    {
      candidates[i].winner_ = true;
    }
  }
}

void announceWinners(Candidate candidates[], int count)
{
  calculateWinners(candidates, count);
  printf("\nPlease congratulate the winner(s) of the election:\n");
  int winners = 0;
  for(int i = 0; i < count; i++)
  {
    if(candidates[i].winner_)
    {
      winners++;
      printf(" - Candidate \"%c\"!\n",candidates[i].id_);
    }
  }
  if(winners >= 2)
  {
    printf("\nThat's a %d-way tie!\n",winners);
  }
}