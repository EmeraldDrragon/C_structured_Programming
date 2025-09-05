//---------------------------------------------------------------------------------------------------------------------
// Card game "Entertaining Spice Pretending" for two players.
// This game is inspired by the card game Spicy. This game is played in multiple rounds.
// Rounds consist of of players taking turns, playing cards from their hand face down and saying what it shows.
// The other player then tells if the first lied or not.
//---------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

typedef enum _ReturnCode_
{
  QUIT = 0,
  INVALID_USAGE = 1,
  CANNOT_OPEN_FILE = 2,
  INVALID_FILE = 3,
  OUT_OF_MEMORY = 4,
  ALRIGHT = 5,
  CHALLENGE = 6
} Return_code;

typedef struct _Card_
{
  int value_;
  char spice_;
  struct _Card_ *next_;

} Card;

typedef struct _Player_
{
  int id_;
  int points_;
  Card *hand_;
  bool draw_last_turn;
  bool round_loser;
} Player;

//---------------------------------------------------------------------------------------------------------------------
/// inserts a card at the end of a given linked list and returns the newly made linked list
///
/// @param stack stack of cards
/// @param value value of a card to insert
/// @param spice spice of a card to insert
/// @return linked list with a new card at the end
Card *insertCardEnd(Card *stack, int value, char spice);

//---------------------------------------------------------------------------------------------------------------------
/// checks command line arguments for correctness and parses the config file
///
/// @param arg command line arguments
/// @param count number of command line arguments
/// @param stack main stack of cards
/// @return return_code
int checkCommandLine(char **arg, int count, Card **stack);

//---------------------------------------------------------------------------------------------------------------------
/// moves a card from one stack to the end of another
///
/// @param stack1 stack from
/// @param stack2 stack to
/// @param card card to move
/// @return no return
void moveFromStackToStack(Card **stack1, Card **stack2, Card *card);

//---------------------------------------------------------------------------------------------------------------------
/// sorts a stack of cards by value in ascending order
///
/// @param stack stack to sort
/// @return no return
void sortStackByValue(Card **stack);

//---------------------------------------------------------------------------------------------------------------------
/// sorts a stack of cards by spice and value
///
/// @param stack stack to sort
/// @return no return
void sortStack(Card **stack);

//---------------------------------------------------------------------------------------------------------------------
/// distributes cards from the main stack to players hands
///
/// @param stack main stack
/// @param player_1 player 1
/// @param player_2 player 2
/// @return no return
void distributeCards(Card **stack, Player *player_1, Player *player_2);

//---------------------------------------------------------------------------------------------------------------------
/// prints a stack of cards
///
/// @param stack stack to print
/// @return no return
void printStack(Card *stack);

//---------------------------------------------------------------------------------------------------------------------
/// prints information about the players hand and about the latest played card
///
/// @param player player
/// @param last_card bool if its last card
/// @param played number of cards played this round
/// @param said_value said value
/// @param said_spice said spice
/// @param latest_played latest played card
/// @return no return
void printPlayer(Player *player, bool last_card, int played, int said_value, char said_spice, Card *latest_played);

//---------------------------------------------------------------------------------------------------------------------
/// creates an input buffer and dynamically allocates memory to it using malloc()
/// reads the input character by character and stores it on the heap, updating the buffer using realloc() as needed
///
/// @return char pointer to the created input buffer
char *getInput(void);

//---------------------------------------------------------------------------------------------------------------------
/// checks the format of the inputted card
///
/// @param card inputted card
/// @param value inputted value
/// @param spice inputted spice
/// @return true or false
bool checkCardFormat(char *card, int *value, char *spice);

//---------------------------------------------------------------------------------------------------------------------
/// looks for the card in the stack of cards by the value and spice
///
/// @param stack to look in
/// @param value to look for
/// @param spice to look for
/// @return Card pointer to this card
Card *findCard(Card *stack, int value, char spice);

//---------------------------------------------------------------------------------------------------------------------
/// play <arg1> <arg2> command plays a card and says its value and spice
///
/// @param arg1 played card
/// @param arg2 said card
/// @param player player
/// @param latest_played latest played card
/// @param said_value said value
/// @param said_spice said spice
/// @param last_card bool if its last card
/// @param discard discard pile
/// @param played number of cards played this round
/// @return true or false
bool playCommand(char *arg1, char *arg2, Player *player, Card **latest_played, int *said_value, char *said_spice,
                 bool *last_card, Card **discard, int *played);

//---------------------------------------------------------------------------------------------------------------------
/// draws additional cards at the end of the round
///
/// @param loser loser of the round
/// @param winner winner of the round
/// @param stack main stack of cards
/// @return no return
void drawAdditionalCards(Player *loser, Player *winner, Card **stack);

//---------------------------------------------------------------------------------------------------------------------
/// challenge <arg1> challenges the opponents played card in either value or spice
///
/// @param arg1 played card
/// @param player player
/// @param opponent opponent
/// @param latest_played latest played card
/// @param said_value said value
/// @param said_spice said spice
/// @param last_card bool if its last card
/// @param discard discard pile
/// @param stack main stack of cards
/// @param played number of cards played this round
/// @return true or false
bool challengeCommand(char *arg1, Player *player, Player *opponent, Card **latest_played, int *said_value,
                      char *said_spice, bool *last_card, Card **discard, Card **stack, int *played);

//---------------------------------------------------------------------------------------------------------------------
/// draw draws additional card from the main stack of cards
///
/// @param player player
/// @param stack main stack of cards
/// @return no return
void drawCommand(Player *player, Card **stack);

//---------------------------------------------------------------------------------------------------------------------
/// checks input for quit command
///
/// @param input input
/// @return no return
bool checkQuit(char *input);

//---------------------------------------------------------------------------------------------------------------------
/// checks input for play command
///
/// @param input input
/// @param player player
/// @param latest_played latest played card
/// @param said_value said value
/// @param said_spice said spice
/// @param last_card bool if its last card
/// @param discard discard pile
/// @param played number of cards played this round
/// @return true or false
bool checkPlay(char *input, Player *player, Card **latest_played, int *said_value, char *said_spice,
               bool *last_card, Card **discard, int *played);

//---------------------------------------------------------------------------------------------------------------------
/// checks input for challenge command
///
/// @param input input
/// @param player player
/// @param opponent opponent
/// @param latest_played latest played card
/// @param said_value said value
/// @param said_spice said spice
/// @param last_card bool if its last card
/// @param discard discard pile
/// @param stack main stack of cards
/// @param played number of cards played this round
/// @return true or false
bool checkChallenge(char *input, Player *player, Player *opponent, Card **latest_played, int *said_value,
                    char *said_spice, bool *last_card, Card **discard, Card **stack, int *played);

//---------------------------------------------------------------------------------------------------------------------
/// checks input for draw command
///
/// @param input input
/// @param player player
/// @param stack main stack of cards
/// @param last_card bool if its last card
/// @return true or false
bool checkDraw(char *input, Player *player, Card **stack, bool *last_card);

//---------------------------------------------------------------------------------------------------------------------
/// reads input, checks input and does the command given by the input
///
/// @param player player
/// @param opponent opponent
/// @param latest_played latest played card
/// @param said_value said value
/// @param said_spice said spice
/// @param last_card bool if its last card
/// @param stack main stack of cards
/// @param discard discard pile
/// @param played number of cards played this round
/// @return return_code
int readAndDoAction(Player *player,Player *opponent, Card **latest_played, int *said_value, char *said_spice,
                    bool *last_card, Card **stack, Card **discard, int *played);

//---------------------------------------------------------------------------------------------------------------------
/// main loop of the game
///
/// @param stack main stack of cards
/// @param player_1 player 1
/// @param player_2 player 2
/// @param discard discard pile
/// @return return_code
int playingTheGame(Card **stack, Player *player_1, Player *player_2, Card **discard);

//---------------------------------------------------------------------------------------------------------------------
/// prints the score board and saves the result into file
///
/// @param arg command line argument - file path
/// @param player_1 player 1
/// @param player_2 player 2
/// @return no return
void finishingTheGame(char **arg, Player *player_1, Player *player_2);

//---------------------------------------------------------------------------------------------------------------------
/// frees the allocated memory of the linked list
///
/// @param stack stack of cards
/// @return no return
void freeStack(Card **stack);

//---------------------------------------------------------------------------------------------------------------------
/// main function contains main stack of cards, discard pile and two players, also frees allocated memory at the end
///
/// @return integer exit code
int main(int argc, char *argv[])
{
  int return_code;
  Card *stack = NULL;
  return_code = checkCommandLine(argv, argc, &stack);
  if(return_code == INVALID_USAGE ||
     return_code == CANNOT_OPEN_FILE ||
     return_code == INVALID_FILE ||
     return_code == OUT_OF_MEMORY)
  {
    return return_code;
  }
  printf("Welcome to Entertaining Spice Pretending!\n");
  Player player_1;
  Player player_2;
  distributeCards(&stack, &player_1, &player_2);
  Card *discard = NULL;
  return_code = playingTheGame(&stack, &player_1, &player_2, &discard);
  if(return_code == QUIT ||
     return_code == OUT_OF_MEMORY)
  {
    freeStack(&stack);
    freeStack(&discard);
    freeStack(&player_1.hand_);
    freeStack(&player_2.hand_);
    return return_code;
  }
  finishingTheGame(argv, &player_1, &player_2);
  freeStack(&stack);
  freeStack(&discard);
  freeStack(&player_1.hand_);
  freeStack(&player_2.hand_);
  return QUIT;
}

//---------------------------------------------------------------------------------------------------------------------
//functions

Card *insertCardEnd(Card *stack, int value, char spice)
{
  Card *new = malloc(sizeof(Card));
  if(new == NULL)
  {
    printf("Error: Out of memory\n");
    return NULL;
  }
  new->value_ = value;
  new->spice_ = spice;
  new->next_ = NULL;
  if(stack == NULL)
  {
    return new;
  }
  Card *current = stack;
  while(current->next_ != NULL)
  {
    current = current->next_;
  }
  current->next_ = new;
  return stack;
}

int checkCommandLine(char **arg, int count, Card **stack)
{
  if(count < 2)
  {
    printf("Usage: ./a4-csf <config file>\n");
    return INVALID_USAGE;
  }
  FILE *file = fopen(arg[1], "r");
  if(file == NULL)
  {
    printf("Error: Cannot open file: %s\n", arg[1]);
    return CANNOT_OPEN_FILE;
  }
  char magic_number[5];
  fgets(magic_number, sizeof(magic_number), file);
  if(strcmp(magic_number, "ESP\n") != 0)
  {
    printf("Error: Invalid file: %s\n", arg[1]);
    fclose(file);
    return INVALID_FILE;
  }
  int value;
  char spice;
  while(fscanf(file, "%d_%c\n", &value, &spice) == 2)
  {
    *stack = insertCardEnd(*stack, value, spice);
    if(*stack == NULL)
    {
      return OUT_OF_MEMORY;
    }
  }
  fclose(file);
  return ALRIGHT;
}

void moveFromStackToStack(Card **stack1, Card **stack2, Card *card)
{
  Card *current = *stack1;
  Card *previous = NULL;
  while(current != NULL)
  {
    if(current == card)
    {
      break;
    }
    previous = current;
    current = current->next_;
  }
  if(current != NULL)
  {
    if(previous != NULL)
    {
      previous->next_ = current->next_;
    }
    else
    {
      *stack1 = current->next_;
    }
    current->next_ = NULL;
    if(*stack2 == NULL)
    {
      *stack2 = current;
      return;
    }
    Card *stack2_current = *stack2;
    while(stack2_current->next_ != NULL)
    {
      stack2_current = stack2_current->next_;
    }
    stack2_current->next_ = current;
  }
}

void sortStackByValue(Card **stack)
{
  Card *new_stack = NULL;

  Card *current = *stack;
  while(current != NULL)
  {
    Card *next = current->next_;
    current->next_ = NULL;
    if(new_stack == NULL || current->value_ < new_stack->value_)
    {
      current->next_ = new_stack;
      new_stack = current;
    }
    else
    {
      Card *new_stack_current = new_stack;
      while(new_stack_current->next_ != NULL && new_stack_current->next_->value_ < current->value_)
      {
        new_stack_current = new_stack_current->next_;
      }
      current->next_ = new_stack_current->next_;
      new_stack_current->next_ = current;
    }
    current = next;
  }
  *stack = new_stack;
}

void sortStack(Card **stack)
{
  Card *c = NULL;
  Card *p = NULL;
  Card *w = NULL;

  Card *current = *stack;
  while(current != NULL)
  {
    Card *next = current->next_;
    if(current->spice_ == 'c')
    {
      moveFromStackToStack(stack, &c, current);
    }
    if(current->spice_ == 'p')
    {
      moveFromStackToStack(stack, &p, current);
    }
    if(current->spice_ == 'w')
    {
      moveFromStackToStack(stack, &w, current);
    }
    current = next;
  }
  sortStackByValue(&c);
  sortStackByValue(&p);
  sortStackByValue(&w);

  current = c;
  while(current != NULL)
  {
    Card *next = current->next_;
    moveFromStackToStack(&c, stack, current);
    current = next;
  }
  current = p;
  while(current != NULL)
  {
    Card *next = current->next_;
    moveFromStackToStack(&p, stack, current);
    current = next;
  }
  current = w;
  while(current != NULL)
  {
    Card *next = current->next_;
    moveFromStackToStack(&w, stack, current);
    current = next;
  }
}

void distributeCards(Card **stack, Player *player_1, Player *player_2)
{
  player_1->hand_ = NULL;
  player_1->id_ = 1;
  player_2->hand_ = NULL;
  player_2->id_ = 2;
  int count = 0;
  Card *current = *stack;
  while(current != NULL)
  {
    Card *card_1 = current;
    Card *card_2 = current->next_;
    Card *next = card_2->next_;
    moveFromStackToStack(stack, &player_1->hand_, card_1);
    moveFromStackToStack(stack, &player_2->hand_, card_2);
    count++;
    if(count == 6)
    {
      break;
    }
    current = next;
  }
  sortStack(&player_1->hand_);
  sortStack(&player_2->hand_);
}

void printStack(Card *stack)
{
  Card *current = stack;
  while(current != NULL)
  {
    if(current->next_ != NULL)
    {
      printf("%d_%c ", current->value_, current->spice_);
    }
    else
    {
      printf("%d_%c", current->value_, current->spice_);
    }
    current = current->next_;
  }
  printf("\n");
}

void printPlayer(Player *player, bool last_card, int played, int said_value, char said_spice, Card *latest_played)
{
  printf("\nPlayer %d:\n", player->id_);
  printf("    latest played card:");
  if(latest_played != NULL)
  {
    printf(" %d_%c", said_value, said_spice);
  }
  if(last_card)
  {
    printf(" LAST CARD");
  }
  printf("\n    cards played this round: %d\n", played);
  printf("    hand cards: ");
  printStack(player->hand_);
}

char *getInput(void)
{
  int size = 10;
  char *buffer = malloc(size * sizeof(char));
  if(buffer == NULL)
  {
    printf("Error: Out of memory\n");
    return NULL;
  }
  int index = 0;
  char input;
  while((input = getchar()) != '\n')
  {
    buffer[index] = input;
    index++;
    if(index == size - 1)
    {
      size = size * 2;
      char *temp = realloc(buffer, size * sizeof(char));
      if(temp == NULL)
      {
        free(buffer);
        printf("Error: Out of memory\n");
        return NULL;
      }
      buffer = temp;
    }
  }
  buffer[index] = '\0';
  for(unsigned long i = 0; i < strlen(buffer); i++)
  {
    if(buffer[i] >= 'A' && buffer[i] <= 'Z')
    {
      buffer[i] = buffer[i] + 32;
    }
  }
  return buffer;
}

bool checkCardFormat(char *card, int *value, char *spice)
{
  if(strlen(card) < 3 || strlen(card) > 4)
  {
    return false;
  }
  char *underscore_pos = strchr(card, '_');
  if(!underscore_pos)
  {
    return false;
  }
  long long value_part = underscore_pos - card;
  if(value_part < 1 || value_part > 2)
  {
    return false;
  }
  for(int i = 0; i < value_part; i++)
  {
    if(!isdigit(card[i]))
    {
      return false;
    }
  }
  *value = atoi(card);
  if(*value < 1 || *value > 10)
  {
    return false;
  }

  if(strlen(underscore_pos + 1) != 1)
  {
    return false;
  }
  *spice = *(underscore_pos + 1);
  if(*spice != 'c' && *spice != 'p' && *spice != 'w')
  {
    return false;
  }
  return true;
}

Card *findCard(Card *stack, int value, char spice)
{
  Card *current = stack;
  while(current != NULL)
  {
    if(current->value_ == value && current->spice_ == spice)
    {
      return current;
    }
    current = current->next_;
  }
  return NULL;
}

bool playCommand(char *arg1, char *arg2, Player *player, Card **latest_played, int *said_value, char *said_spice,
                 bool *last_card, Card **discard, int *played)
{
  int new_said_value;
  char new_said_spice;
  int played_value;
  char played_spice;
  if(!checkCardFormat(arg1, &played_value, &played_spice) ||
     !checkCardFormat(arg2, &new_said_value, &new_said_spice))
  {
    printf("Please enter the cards in the correct format!\n");
    return false;
  }
  Card *played_card = findCard(player->hand_, played_value, played_spice);
  if(played_card == NULL)
  {
    printf("Please enter a card in your hand cards!\n");
    return false;
  }
  if(*latest_played != NULL)
  {
    if((*said_value != 10 && *said_value > new_said_value) || (*said_value == 10 && new_said_value > 3))
    {
      printf("Please enter a valid VALUE!\n");
      return false;
    }
    if(*said_spice != new_said_spice)
    {
      printf("Please enter a valid SPICE!\n");
      return false;
    }
  }
  else
  {
    if(new_said_value > 3)
    {
      printf("Please enter a valid VALUE!\n");
      return false;
    }
  }
  *said_value = new_said_value;
  *said_spice = new_said_spice;
  if(*latest_played != NULL)
  {
    moveFromStackToStack(latest_played, discard, *latest_played);
  }
  moveFromStackToStack(&player->hand_, latest_played, played_card);
  (*played)++;
  if(player->hand_ == NULL)
  {
    *last_card = true;
  }

  return true;
}

void drawAdditionalCards(Player *loser, Player *winner, Card **stack)
{
  int count = 0;
  Card *current = *stack;
  while(current != NULL)
  {
    Card *next_card = current->next_;
    moveFromStackToStack(stack, &loser->hand_, current);
    count++;
    if(count == 2)
    {
      break;
    }
    current = next_card;
  }
  count = 0;
  if(winner->hand_ == NULL)
  {
    current = *stack;
    while(current != NULL)
    {
      Card *next_card = current->next_;
      moveFromStackToStack(stack, &winner->hand_, current);
      count++;
      if(count == 6)
      {
        break;
      }
      current = next_card;
    }
  }
  sortStack(&loser->hand_);
  sortStack(&winner->hand_);
}

bool challengeCommand(char *arg1, Player *player, Player *opponent, Card **latest_played, int *said_value,
                      char *said_spice, bool *last_card, Card **discard, Card **stack, int *played)
{
  Player *winner;
  Player *loser;
  if(strcmp(arg1, "spice") != 0 && strcmp(arg1, "value") != 0)
  {
    printf("Please choose SPICE or VALUE!\n");
    return false;
  }
  if(strcmp(arg1, "value") == 0)
  {
    if((*latest_played)->value_ != *said_value)
    {
      printf("Challenge successful: %d_%c's value does not match the real card %d_%c.\n",
             *said_value, *said_spice, (*latest_played)->value_, (*latest_played)->spice_);
      winner = player;
      loser = opponent;
    }
    else
    {
      printf("Challenge failed: %d_%c's value matches the real card %d_%c.\n",
             *said_value, *said_spice, (*latest_played)->value_, (*latest_played)->spice_);
      winner = opponent;
      loser = player;
    }
  }
  if(strcmp(arg1, "spice") == 0)
  {
    if((*latest_played)->spice_ != *said_spice)
    {
      printf("Challenge successful: %d_%c's spice does not match the real card %d_%c.\n",
             *said_value, *said_spice, (*latest_played)->value_, (*latest_played)->spice_);
      winner = player;
      loser = opponent;
    }
    else
    {
      printf("Challenge failed: %d_%c's spice matches the real card %d_%c.\n",*said_value,
             *said_spice, (*latest_played)->value_, (*latest_played)->spice_);
      winner = opponent;
      loser = player;
    }
  }
  printf("Player %d gets %d points.\n", winner->id_, *played);
  winner->points_ += *played;
  if(winner == opponent && *last_card)
  {
    printf("Player %d gets 10 bonus points (last card).\n", winner->id_);
    winner->points_ += 10;
  }

  drawAdditionalCards(loser, winner, stack);
  moveFromStackToStack(latest_played, discard, *latest_played);
  *played = 0;
  *said_value = 0;
  *said_spice = 'a';
  *last_card = false;
  loser->round_loser = true;
  return true;
}

void drawCommand(Player *player, Card **stack)
{
  player->draw_last_turn = true;
  moveFromStackToStack(stack, &player->hand_, *stack);
  sortStack(&player->hand_);
}

bool checkQuit(char *input)
{
  if(strtok(NULL," ") != NULL)
  {
    printf("Please enter the correct number of parameters!\n");
    free(input);
    return false;
  }
  free(input);
  return true;
}

bool checkPlay(char *input, Player *player, Card **latest_played, int *said_value, char *said_spice,
               bool *last_card, Card **discard, int *played)
{
  char *arg1 = strtok(NULL, " ");
  char *arg2 = strtok(NULL, " ");

  if(arg1 == NULL || arg2 == NULL || strtok(NULL," ") != NULL)
  {
    printf("Please enter the correct number of parameters!\n");
    free(input);
    return false;
  }
  if(*last_card)
  {
    printf("Please enter a command you can use at the moment!\n");
    free(input);
    return false;
  }
  if(!playCommand(arg1, arg2, player, latest_played, said_value, said_spice, last_card, discard,played))
  {
    free(input);
    return false;
  }
  player->draw_last_turn = false;
  free(input);
  return true;
}

bool checkChallenge(char *input, Player *player, Player *opponent, Card **latest_played, int *said_value,
                    char *said_spice, bool *last_card, Card **discard, Card **stack, int *played)
{
  char *arg1 = strtok(NULL, " ");
  if(arg1 == NULL || strtok(NULL, " ") != NULL)
  {
    printf("Please enter the correct number of parameters!\n");
    free(input);
    return false;
  }
  if(*latest_played == NULL || opponent->draw_last_turn == true)
  {
    printf("Please enter a command you can use at the moment!\n");
    free(input);
    return false;
  }
  if(!challengeCommand(arg1, player, opponent, latest_played, said_value, said_spice, last_card, discard, stack, played))
  {
    free(input);
    return false;
  }
  free(input);
  return true;
}

bool checkDraw(char *input, Player *player, Card **stack, bool *last_card)
{
  if(strtok(NULL, " ") != NULL)
  {
    printf("Please enter the correct number of parameters!\n");
    free(input);
    return false;
  }
  if(*last_card)
  {
    printf("Please enter a command you can use at the moment!\n");
    free(input);
    return false;
  }
  drawCommand(player, stack);
  free(input);
  return true;
}

int readAndDoAction(Player *player,Player *opponent, Card **latest_played, int *said_value, char *said_spice,
                    bool *last_card, Card **stack, Card **discard, int *played)
{
  char *input;
  while(true)
  {
    printf("P%d > ", player->id_);
    input = getInput();
    if(input == NULL)
    {
      return OUT_OF_MEMORY;
    }
    char *token = strtok(input," ");
    if(token == NULL || (strcmp(token, "quit") != 0 && strcmp(token, "play") != 0 &&
                         strcmp(token, "challenge") != 0 && strcmp(token, "draw") != 0))
    {
      printf("Please enter a valid command!\n");
      free(input);
      continue;
    }
    if(strcmp(token, "quit") == 0)
    {
      if(checkQuit(input))
      {
        return QUIT;
      }
      else
      {
        continue;
      }
    }
    if(strcmp(token, "play") == 0)
    {
      if(checkPlay(input, player, latest_played, said_value, said_spice, last_card, discard, played))
      {
        break;
      }
      else
      {
        continue;
      }
    }
    if(strcmp(token, "challenge") == 0)
    {
      if(checkChallenge(input, player, opponent, latest_played, said_value, said_spice, last_card, discard, stack, played))
      {
        return CHALLENGE;
      }
      else
      {
        continue;
      }
    }
    if(strcmp(token, "draw") == 0)
    {
      if(checkDraw(input, player, stack, last_card))
      {
        break;
      }
      else
      {
        continue;
      }
    }
  }
  return ALRIGHT;
}

int playingTheGame(Card **stack, Player *player_1, Player *player_2, Card **discard)
{
  Player *first = player_1;
  first->draw_last_turn = false;
  first->round_loser = false;
  first->points_ = 0;
  Player *second = player_2;
  second->draw_last_turn = false;
  second->round_loser = false;
  second->points_ = 0;
  Card *latest_played = NULL;
  int said_value = 0;
  char said_spice = 'a';
  bool last_card = false;
  int played = 0;
  bool finished = false;
  while(!finished)
  {
    printf("\n-------------------\nROUND START\n-------------------\n");
    while(true)
    {
      printPlayer(first, last_card, played,said_value, said_spice, latest_played);
      int return_code = readAndDoAction(first, second, &latest_played, &said_value,
                                        &said_spice, &last_card, stack, discard, &played);
      if(return_code == QUIT || return_code == OUT_OF_MEMORY)
      {
        free(latest_played);
        return return_code;
      }
      if(*stack == NULL)
      {
        finished = true;
        break;
      }
      if(return_code == CHALLENGE)
      {
        break;
      }
      printPlayer(second,last_card, played, said_value, said_spice, latest_played);
      return_code = readAndDoAction(second, first, &latest_played, &said_value,
                                    &said_spice, &last_card, stack, discard, &played);
      if(return_code == QUIT || return_code == OUT_OF_MEMORY)
      {
        free(latest_played);
        return return_code;
      }
      if(*stack == NULL)
      {
        finished = true;
        break;
      }
      if(return_code == CHALLENGE)
      {
        break;
      }
    }

    if(second->round_loser)
    {
      Player *temp = first;
      first = second;
      second = temp;
    }
    first->round_loser = false;
    second->round_loser = false;
  }
  free(latest_played);
  return ALRIGHT;
}

void finishingTheGame(char **arg, Player *player_1, Player *player_2)
{
  if(player_1->points_ > player_2->points_)
  {
    printf("\nPlayer 1: %d points\n", player_1->points_);
    printf("Player 2: %d points\n", player_2->points_);
    printf("\nCongratulations! Player 1 wins the game!\n");
  }
  else if(player_2->points_ > player_1->points_)
  {
    printf("\nPlayer 2: %d points\n", player_2->points_);
    printf("Player 1: %d points\n", player_1->points_);
    printf("\nCongratulations! Player 2 wins the game!\n");
  }
  else
  {
    printf("\nPlayer 1: %d points\n", player_1->points_);
    printf("Player 2: %d points\n", player_2->points_);
    printf("\nCongratulations! Player 1 wins the game!\n");
    printf("Congratulations! Player 2 wins the game!\n");
  }
  FILE *file = fopen(arg[1],"a");
  if(file == NULL)
  {
    printf("Warning: Results not written to file!\n");
    return;
  }
  if(player_1->points_ > player_2->points_)
  {
    fprintf(file, "\nPlayer 1: %d points\n", player_1->points_);
    fprintf(file, "Player 2: %d points\n", player_2->points_);
    fprintf(file, "\nCongratulations! Player 1 wins the game!\n");
  }
  else if(player_2->points_ > player_1->points_)
  {
    fprintf(file, "\nPlayer 2: %d points\n", player_2->points_);
    fprintf(file, "Player 1: %d points\n", player_1->points_);
    fprintf(file, "\nCongratulations! Player 2 wins the game!\n");
  }
  else
  {
    fprintf(file, "\nPlayer 1: %d points\n", player_1->points_);
    fprintf(file, "Player 2: %d points\n", player_2->points_);
    fprintf(file, "\nCongratulations! Player 1 wins the game!\n");
    fprintf(file, "Congratulations! Player 2 wins the game!\n");
  }
  fclose(file);
}

void freeStack(Card **stack)
{
  Card *current = *stack;
  while(current != NULL)
  {
    Card *temp = current;
    current = current->next_;
    free(temp);
  }
}
