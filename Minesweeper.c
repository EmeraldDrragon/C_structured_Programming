//---------------------------------------------------------------------------------------------------------------------
// This program is a game called Minesweeper
//---------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#define INPUT_SIZE 10000
#define ARGUMENT_SIZE 10000

enum returnCodes
{
  MEMORY_ISSUE = 1,
  ERROR_INV_NUM_PARAM = 2,
  ERROR_UNEXP_ARG = 3,
  ERROR_INV_TYPE = 4,
  ERROR_INV_VAL = 5,
  CONTINUE = 11,
  INPUT_ERROR = 12,
};

typedef struct _field_
{
  bool closed_;
  bool flagged_;
  bool mine_;
  bool mine_highlighted_;
  int adj_mines_;
} Field;

typedef struct _game_
{
  long long rows_;
  long long cols_;
  long long mines_;
  long long seed_;

  bool running_;
  Field **map_;

  long long fields_no_mine_;
  long long opened_fields_;
  long long remaining_flags_;
} Game;


//---functions---------------------------------------------------------------------------------------------------------

//---------------------------------------------------------------------------------------------------------------------
///
/// checks if string is integer only
///
/// @param char *str string to check
///
/// @return bool
//
bool isInt(const char *str);

//---------------------------------------------------------------------------------------------------------------------
///
/// prints start message
///
/// @param Game * main game struct
///
/// @return no return
//
void startMsg(Game *game);

//---------------------------------------------------------------------------------------------------------------------
///
/// creates map and allocates memory for the map in the game struct
///
/// @param Game * main game struct
///
/// @return int code for error or continue
//
int mapCreation(Game *game);

//---------------------------------------------------------------------------------------------------------------------
///
/// checks argv[] array passed by command line arguments to the program. Assigns new value to the variables
///
/// @param Game * main game struct
/// @param int argc
/// @param char * argv
///
/// @return int code for error or continue
//
int createGame(Game *game, int argc, char *argv[]);


//---------------------------------------------------------------------------------------------------------------------
///
/// deallocates dynamically allocated fields
///
/// @param Game * main game struct
///
/// @return no return
//
void deallocateFields(Game *game);

//---------------------------------------------------------------------------------------------------------------------
///
/// returns true if it reads only two arguments and they are numbers
///
/// @param Game * main game struct
/// @param char * input
/// @param long long * row
/// @param long long * col
///
/// @return bool
//
bool readIntArgument(Game *game, char *input, long long *row, long long *col);

//---------------------------------------------------------------------------------------------------------------------
///
/// returns true if it reads only one argument and its string
///
/// @param char * input
/// @param char * filename
///
/// @return bool
//
bool readStrArgument(char *input, char *filename);

//---------------------------------------------------------------------------------------------------------------------
///
/// returns true if there are no arguments
///
/// @param char * input
///
/// @return bool
//
bool readNoArgument(char *input);

//---------------------------------------------------------------------------------------------------------------------
///
/// returns true if there are no arguments
///
/// @param Game * main game struct
/// @param char * cmd command string to read into
/// @param long long * row
/// @param long long * col
/// @param char * filename
///
/// @return int error code
//
int readInput(Game *game, char *cmd,long long *row, long long *col, char *filename);

//---------------------------------------------------------------------------------------------------------------------
///
/// prints current map
///
/// @param Game * main game struct
///
/// @return no return
//
void printMap(Game *game);

//---------------------------------------------------------------------------------------------------------------------
///
/// creates a pseudorandom number
///
/// @return unsigned long long int
//
unsigned long long int generate_64bit_random_number();

//---------------------------------------------------------------------------------------------------------------------
///
/// sets adjacent mines on the map
///
/// @param Game * main game struct
///
/// @return no return
//
void setAdjMines(Game *game);

//---------------------------------------------------------------------------------------------------------------------
///
/// flags a field or removes flag if its flagged
///
/// @param Game * main game struct
/// @param long long row
/// @param long long col
///
/// @return no return
//
void flag(Game *game, long long row, long long col);

//---------------------------------------------------------------------------------------------------------------------
///
/// loss when a field that contains a mine was opened
///
/// @param Game * main game struct
/// @param long long row
/// @param long long col
///
/// @return no return
//
void loss(Game *game, long long row, long long col);

//---------------------------------------------------------------------------------------------------------------------
///
/// win when opened field = remaining fields
///
/// @param Game * main game struct
///
/// @return no return
//
void win(Game* game);

//---------------------------------------------------------------------------------------------------------------------
///
/// opens fields around the field; part of recursive opening
///
/// @param Game * main game struct
/// @param long long row
/// @param long long col
///
/// @return no return
//
void openFieldsAround(Game *game, long long row, long long col);

//---------------------------------------------------------------------------------------------------------------------
///
/// opens chosen field; part of recursive opening
///
/// @param Game * main game struct
/// @param long long row
/// @param long long col
///
/// @return no return
//
void open(Game *game, long long row, long long col);

//---------------------------------------------------------------------------------------------------------------------
///
/// generates map and opens one field
///
/// @param Game * main game struct
/// @param long long start_row
/// @param long long start_col
///
/// @return no return
//
void mapGeneration(Game *game, long long start_row, long long start_col);

//---------------------------------------------------------------------------------------------------------------------
///
/// starts game and opens one field
///
/// @param Game * main game struct
/// @param long long start_row
/// @param long long start_col
///
/// @return no return
//
void startGame(Game *game, long long start_row, long long start_col);

//---------------------------------------------------------------------------------------------------------------------
///
/// prints opened map
///
/// @param Game main game struct
///
/// @return no return
//
void dump(Game *game);

//---------------------------------------------------------------------------------------------------------------------
///
/// saves game
///
/// @param Game * main game struct
/// @param char * path
///
/// @return no return
//
void save(Game *game, char *path);

//---------------------------------------------------------------------------------------------------------------------
///
/// counts how many mines are on the field
///
/// @param Game * main game struct
///
/// @return long long mines
//
long long countMines(Game* game);

//---------------------------------------------------------------------------------------------------------------------
///
/// counts how many opened fields are on the field
///
/// @param Game * main game struct
///
/// @return long long fields
//
long long countOpenedFields(Game *game);

//---------------------------------------------------------------------------------------------------------------------
///
/// counts how many flags are on the field
///
/// @param Game * main game struct
///
/// @return long long flags
//
long long countFlags(Game *game);

//---------------------------------------------------------------------------------------------------------------------
///
/// loads game
///
/// @param Game * main game struct
/// @param char * path
///
/// @return int error code
//
int load(Game *game, char *path);

//---------------------------------------------------------------------------------------------------------------------
///
/// reads command and executes it, returns CONTINUE if everythings alright, returns MEMORY_ISSUE if there is one
///
/// @param Game * main game struct
///
/// @return int error code
//
int execute(Game *game);


//---main function-----------------------------------------------------------------------------------------------------


//main function. The program receives three optional command line arguments: --size, --mines and --seed
//---------------------------------------------------------------------------------------------------------------------
///
/// main function. The program receives three optional command line arguments: --size, --mines and --seed
///
/// @param int argc
/// @param char * argv[]
///
/// @return int error code
//
int main(int argc, char *argv[])
{
  Game game;
  int error_code = createGame(&game, argc, argv);
  if(error_code == MEMORY_ISSUE)
  {
    printf("Out of memory!\n");
    return MEMORY_ISSUE;
  }
  if(error_code == ERROR_INV_NUM_PARAM)
  {
    return ERROR_INV_NUM_PARAM;
  }
  if(error_code == ERROR_UNEXP_ARG)
  {
    return ERROR_UNEXP_ARG;
  }
  if(error_code == ERROR_INV_TYPE)
  {
    return ERROR_INV_TYPE;
  }
  if(error_code == ERROR_INV_VAL)
  {
    return ERROR_INV_VAL;
  }
  startMsg(&game);
  while(game.running_)
  {
    printf(" > ");
    if(execute(&game)==MEMORY_ISSUE)
    {
      printf("Out of memory!\n");
      return 1;
    }
  }
  deallocateFields(&game);
  return 0;
}


//---functions---------------------------------------------------------------------------------------------------------


//checks if string is integer only
bool isInt(const char *str)
{
  size_t index = 0;
  if(str[index] == '-')
  {
    index++;
    if(str[index] == '\0')
    {
      return false;
    }
  }
  while(str[index] != '\0')
  {
    if(str[index] < '0' || str[index] > '9')
    {
      return false;
    }
    index++;
  }
  return true;
}

//prints start message
void startMsg(Game *game)
{
  printf("Welcome to ESP Minesweeper!\n");
  printf("Chosen field size: %lld x %lld.\n",game->rows_, game->cols_);
  printf("After map generation %lld mines will be hidden in the playing field.\n", game->mines_);
}

//creates map and allocates memory for the map in the game struct
int mapCreation(Game *game)
{
  game->map_ = malloc(game->rows_ * sizeof(Field*));
  if(game->map_ == NULL)
  {
    return MEMORY_ISSUE;
  }
  for(long long index = 0; index < game->rows_; index++)
  {
    game->map_[index] = malloc(game->cols_ * sizeof(Field));
    if(game->map_[index] == NULL)
    {
      for(long long free_index = 0; free_index < index; free_index++)
      {
        free(game->map_[free_index]);
      }
      free(game->map_);
      return MEMORY_ISSUE;
    }

    for(long long field_index = 0; field_index < game->cols_; field_index++)
    {
      //default initialization
      game->map_[index][field_index].closed_ = true;
      game->map_[index][field_index].flagged_ = false;
      game->map_[index][field_index].mine_ = false;
      game->map_[index][field_index].mine_highlighted_ = false;
      game->map_[index][field_index].adj_mines_ = 0;
    }
  }
  return CONTINUE;
}

//checks argv[] array passed by command line arguments to the program. Assigns new value to the variables
int createGame(Game *game, int argc, char* argv[])
{
  game->rows_ = 9;
  game->cols_ = 9;
  game->mines_ = 10;
  game->seed_ = 0;
  game->running_ = true;
  game->fields_no_mine_ = game->rows_ * game->cols_ - game->mines_;
  game->opened_fields_ = 0;
  game->remaining_flags_ = 0;
  for(int index = 1; index < argc; index++)
  {
    if(strcmp(argv[index], "--size") ==0)
    {
      if((index + 2 >= argc || argv[index + 1][0] == '-' || argv[index + 2][0] == '-'))
      {
        printf("Invalid number of parameters given!\n");
        return ERROR_INV_NUM_PARAM;
      }
      if(!isInt(argv[index + 1]) || !isInt(argv[index + 2]))
      {
        printf("Invalid type for argument!\n");
        return ERROR_INV_TYPE;
      }
      game->rows_ = atoi(argv[index + 1]);
      game->cols_ = atoi(argv[index + 2]);
      if ((unsigned long long)game->rows_ > UINT64_MAX - 1 || (unsigned long long)game->cols_ > UINT64_MAX  - 1 || game->rows_ <= 0 || game->cols_ <= 0)
      {
        printf("Invalid value for argument!\n");
        return ERROR_INV_VAL;
      }
      index += 2;
    }
    else if(strcmp(argv[index], "--mines")==0 || strcmp(argv[index], "--seed")==0)
    {
      if(index + 1 >= argc || (argv[index + 1][0] == '-' && (index + 2 >= argc &&argv[index + 2][0] == '-')))
      {
        printf("Invalid number of parameters given!\n");
        return ERROR_INV_NUM_PARAM;
      }
      if(!isInt(argv[index + 1]))
      {
        printf("Invalid type for argument!\n");
        return ERROR_INV_TYPE;
      }
      int value = atoi(argv[index + 1]);

      if(strcmp(argv[index], "--mines")==0)
      {
        game->mines_ = value;
        if(game->mines_ < 0 || (unsigned long long)game->mines_ > UINT64_MAX - 1 || game->mines_ > game->rows_ * game->cols_-1)
        {
          printf("Invalid value for argument!\n");
          return ERROR_INV_VAL;
        }
      }
      else if(strcmp(argv[index], "--seed")==0)
      {
        game->seed_ = value;
        if(game->seed_ < 0 || (unsigned long long)game->seed_ > UINT64_MAX  - 1)
        {
          printf("Invalid value for argument!\n");
          return ERROR_INV_VAL;
        }
      }
      index++;
    }
    else
    {
      printf("Unexpected argument provided!\n");
      return ERROR_UNEXP_ARG;
    }
  }
  srand(game->seed_);
  if(mapCreation(game) == MEMORY_ISSUE)
  {
    return MEMORY_ISSUE;
  }
  return CONTINUE;
}

//deallocates dynamically allocated fields
void deallocateFields(Game *game)
{
  for(long long row = 0; row < game->rows_;row++)
  {
    free(game->map_[row]);
  }
  free(game->map_);
}

//returns true if it reads only two arguments and they are numbers
bool readIntArgument(Game * game, char *input, long long *row, long long *col)
{
  char row_str[ARGUMENT_SIZE];
  char col_str[ARGUMENT_SIZE];

  //skip command
  char *token = strtok(input, " ");

  //row
  token = strtok(NULL, " ");
  if(token != NULL)
  {
    strncpy(row_str, token, strlen(token) + 1);
  }
  else
  {
    printf("Error: Command is missing arguments!\n");
    return false;
  }

  //col
  token = strtok(NULL, " ");
  if(token!=NULL)
  {
    strncpy(col_str, token, strlen(token) + 1);
  }
  else
  {
    printf("Error: Command is missing arguments!\n");
    return false;
  }

  //too many arguments
  token = strtok(NULL," ");
  if(token != NULL)
  {
    printf("Error: Too many arguments given for command!\n");
    return false;
  }

  if(!isInt(row_str)||!isInt(col_str))
  {
    printf("Error: Invalid arguments given!\n");
    return false;
  }

  *row = atoll(row_str);
  *col = atoll(col_str);
  if(*row < 0 || *row > game->rows_ || *col < 0 || *col > game->cols_)
  {
    printf("Error: Coordinates are invalid for this game board!\n");
    return false;
  }
  return true;
}

//returns true if it reads only one argument and its string
bool readStrArgument(char *input, char *filename)
{
  //skip command
  char *token = strtok(input," ");

  //filename
  token = strtok(NULL, " ");
  if(token != NULL)
  {
    strncpy(filename, token, strlen(token) + 1);
  }
  else
  {
    printf("Error: Command is missing arguments!\n");
    return false;
  }

  //too many arguments
  token = strtok(NULL, " ");
  if(token != NULL)
  {
    printf("Error: Too many arguments given for command!\n");
    return false;
  }
  return true;
}

//returns true if there are no arguments
bool readNoArgument(char *input)
{
  //skip command
  char *token = strtok(input, " ");

  //too many arguments
  token = strtok(NULL, " ");
  if(token != NULL)
  {
    printf("Error: Too many arguments given for command!\n");
    return false;
  }
  return true;
}

//reads input and calls argument readers
int readInput(Game *game, char *cmd,long long *row, long long *col, char *filename)
{
  //reading input
  char input[INPUT_SIZE];
  fgets(input, INPUT_SIZE, stdin);
  input[strlen(input) - 1] = '\0';

  char input_copy[INPUT_SIZE];
  strcpy(input_copy, input);

  //reading first word - command from input
  char *token = strtok(input_copy, " ");
  if(token != NULL)
  {
    strncpy(cmd,token,strlen(token) + 1);
  }
  else
  {
    cmd[0] = '\0';
  }

  //checking the command and assigning row col and filename
  if(strcmp(cmd, "start") == 0 || strcmp(cmd, "open") == 0 || strcmp(cmd, "flag") == 0)
  {
    if(!readIntArgument(game, input, row, col))
    {
      return INPUT_ERROR;
    }
  }
  else if(strcmp(cmd, "save") == 0 || strcmp(cmd, "load") == 0)
  {
    if(!readStrArgument(input,filename))
    {
      return INPUT_ERROR;
    }
  }
  else if(strcmp(cmd, "dump") == 0 || strcmp(cmd, "quit") == 0)
  {
    if(!readNoArgument(input))
    {
      return INPUT_ERROR;
    }
  }
  else
  {
    printf("Error: Unknown command!\n");
    return INPUT_ERROR;
  }
  return CONTINUE;
}

//prints current map
void printMap(Game *game)
{
  printf("\n");
  printf("  \033[31m¶\033[0m: %lld\n", game->remaining_flags_);
  printf("  ");
  for(long long border = 0; border < game->cols_; border++)
  {
    printf("=");
  }
  printf(" \n");
  for(long long row = 0; row < game->rows_; row++)
  {
    printf(" |");
    for(long long col = 0; col < game->cols_; col++)
    {
      if(game->map_[row][col].flagged_ && game->map_[row][col].closed_)
      {
        printf("\033[31m¶\033[0m");
//        printf("%c", 244);
      }
      else if(game->map_[row][col].closed_)
      {
        printf("░");
      }
      else if(game->map_[row][col].mine_)
      {
        if(game->map_[row][col].mine_highlighted_)
        {
          printf("\033[33m\033[41m@\033[0m"); //+ color
//          printf("%c",64); //+ color
        }
        else
        {
          printf("\033[33m@\033[0m"); //+ color
//          printf("%c",64); //+ color
        }
      }
      else if(game->map_[row][col].adj_mines_ > 0)
      {
        printf("%d", game->map_[row][col].adj_mines_);
      }
      else
      {
        printf("·");
      }
    }
    printf("|\n");
  }
  printf("  ");
  for(int border = 0; border < game->cols_; border++)
  {
    printf("=");
  }
  printf(" \n");
}

//creates a pseudorandom number
unsigned long long int generate_64bit_random_number()
{
  unsigned long long int upper = (unsigned long long int)rand();
  unsigned long long int lower = (unsigned long long int)rand();
  unsigned long long int random_number = (upper << 32) | lower;
  return random_number;
}

//sets adjacent mines on the map
void setAdjMines(Game *game)
{
  int direction_row[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int direction_col[] = {-1, 0, 1, -1, 1, -1, 0, 1};
  for(long long row = 0; row < game->rows_; row++)
  {
    for(long long col = 0; col < game->cols_; col++)
    {
      if(game->map_[row][col].mine_)
      {
        continue;
      }
      for(int direction = 0; direction < 8; direction++)
      {
        long long new_x = row + direction_row[direction];
        long long new_y = col + direction_col[direction];
        if(new_x >= 0 && new_x < game->rows_ && new_y >= 0 && new_y < game->cols_)
        {
          if(game->map_[new_x][new_y].mine_)
          {
            game->map_[row][col].adj_mines_++;
          }
        }
      }
    }
  }
}

//flags a field or removes flag if its flagged
void flag(Game *game, long long row, long long col)
{
  if(!game->map_[row][col].flagged_)
  {
    if(game->remaining_flags_ == 0)
    {
      return;
    }
    game->map_[row][col].flagged_ = true;
    if(game->map_[row][col].closed_)
    {
      game->remaining_flags_ -= 1;
    }

  }
  else
  {
    game->map_[row][col].flagged_ = false;
    game->remaining_flags_ += 1;
  }
}

//loss when a field that contains a mine was opened
void loss(Game *game, long long row, long long col)
{
  printf("\n=== You lost! ===\n");
  game->running_ = false;
  game->map_[row][col].mine_highlighted_ = true;
  for(long long row = 0; row < game->rows_; row++)
  {
    for(long long col = 0; col < game->cols_; col++)
    {
      if(game->map_[row][col].mine_)
      {
        game->map_[row][col].closed_ = false;
        game->map_[row][col].flagged_ = false;
      }
    }
  }
  printMap(game);
}

//win when opened field = remaining fields
void win(Game* game)
{
  printf("\n=== You won! ===\n");
  game->running_ = false;
  for(long long row = 0; row < game->rows_; row++)
  {
    for(long long col = 0; col < game->cols_; col++)
    {
      game->map_[row][col].flagged_ = false;
      game->map_[row][col].closed_ = false;
    }
  }
  printMap(game);
}

//opens fields around the field; part of recursive opening
void openFieldsAround(Game *game, long long row, long long col)
{
  int direction_x[] = {-1, -1, -1, 0, 0, 1, 1, 1};
  int direction_y[] = {-1, 0, 1, -1, 1, -1, 0, 1};
  for(int direction = 0; direction < 8; direction++)
  {
    long long new_x = row + direction_x[direction];
    long long new_y = col + direction_y[direction];
    if(new_x >= 0 && new_x < game->rows_ && new_y >= 0 && new_y < game->cols_)
    {
      open(game,new_x,new_y);
    }
  }
}

//opens chosen field; part of recursive opening
void open(Game *game, long long row, long long col)
{
  if(row < 0 || row>=game->rows_ || col < 0 || col >= game->cols_)
  {
    return;
  }

  if(!game->map_[row][col].closed_)
  {
    return;
  }

  if(game->map_[row][col].flagged_)
  {
    game->remaining_flags_ += 1;
  }
  game->map_[row][col].closed_ = false;
  game->opened_fields_++;

  if(game->opened_fields_ == game->fields_no_mine_)
  {
    win(game);
    return;
  }

  if(game->map_[row][col].mine_)
  {
    loss(game, row, col);
    return;
  }

  if(game->map_[row][col].adj_mines_ == 0)
  {
    openFieldsAround(game, row, col);
  }
}

//generates map and opens one field
void mapGeneration(Game *game, long long start_row, long long start_col)
{
  long long fields_left = game->rows_ * game->cols_ - 1;
  long long mines_left = game->mines_;
  game->remaining_flags_ = game->mines_;
  game->opened_fields_ = 0;
  for(long long row = 0; row < game->rows_; row++)
  {
    for(long long col = 0; col < game->cols_; col++)
    {
      game->map_[row][col].flagged_ = false;
      game->map_[row][col].mine_ = false;
      game->map_[row][col].closed_ = true;
      game->map_[row][col].adj_mines_ = 0;
      if(row == start_row && col == start_col)
      {
        game->map_[row][col].mine_ = false;
        continue;
      }
      long long random_number = generate_64bit_random_number() % fields_left;
      if(random_number < mines_left)
      {
        game->map_[row][col].mine_ = true;
        mines_left -= 1;
      }
      fields_left -= 1;
    }
  }
  setAdjMines(game);
  open(game, start_row, start_col);
}

//starts game and opens one field
void startGame(Game *game, long long start_row, long long start_col)
{
  game->fields_no_mine_ = game->rows_ * game->cols_ - game->mines_;
  mapGeneration(game, start_row, start_col);
}

//prints opened map
void dump(Game *game)
{
  printf("\n");
  printf("  \033[31m¶\033[0m: %lld\n", game->remaining_flags_);
  printf("  ");
  for(long long border = 0; border < game->cols_; border++)
  {
    printf("=");
  }
  printf(" \n");

  for(long long row = 0; row < game->rows_; row++)
  {
    printf(" |");
    for(long long col = 0; col < game->cols_; col++)
    {
      if(game->map_[row][col].mine_)
      {
        printf("\033[33m@\033[0m"); //+ color
//        printf("%c",64); //+ color
      }
      else if(game->map_[row][col].adj_mines_ != 0)
      {
        printf("%d",game->map_[row][col].adj_mines_);
      }
      else
      {
        printf("·");
      }
    }
    printf("|\n");
  }
  printf("  ");
  for(long long border = 0; border < game->cols_; border++)
  {
    printf("=");
  }
  printf(" \n");
}

//saves game
void save(Game *game, char *path)
{
  FILE *file = fopen(path,"wb");
  if(file == NULL)
  {
    printf("Error: Failed to open file!\n");
    return;
  }
  fwrite("ESP\0",1,4,file);
  fwrite(&game->rows_,sizeof(long long), 1, file);
  fwrite(&game->cols_,sizeof(long long), 1, file);

  long long fields = game->rows_ * game->cols_;
  long long blocks = (fields + 7) / 8;

  for(long long block = 0; block < blocks; block++)
  {
    uint8_t valid_bits = 0;
    uint8_t mine_bits = 0;
    uint8_t opened_bits = 0;
    uint8_t flagged_bits = 0;

    for(int bit = 0; bit < 8; bit++)
    {
      long long field_index = block * 8 + bit;
      if(field_index >= fields)
      {
        break;
      }
      Field *field = &game->map_[field_index / game->cols_][field_index % game->cols_];

      valid_bits |= (1 << bit);

      if(field->mine_)
      {
        mine_bits |= (1 << bit);
      }

      if(!field->closed_)
      {
        opened_bits |= (1 << bit);
      }

      if(field->flagged_)
      {
        flagged_bits |= (1 << bit);
      }
    }
    fwrite(&valid_bits, 1, 1, file);
    fwrite(&mine_bits, 1, 1, file);
    fwrite(&opened_bits, 1, 1, file);
    fwrite(&flagged_bits, 1, 1, file);
  }
  fclose(file);
  printMap(game);
}

//counts how many mines are on the field
long long countMines(Game* game)
{
  long long mines = 0;
  for(long long row = 0; row < game->rows_; row++)
  {
    for(long long col = 0; col < game->cols_; col++)
    {
      if(game->map_[row][col].mine_)
      {
        mines++;
      }
    }
  }
  return mines;
}

//counts how many opened fields are on the field
long long countOpenedFields(Game *game)
{
  long long fields = 0;
  for(long long row = 0; row < game->rows_; row++)
  {
    for(long long col = 0; col < game->cols_; col++)
    {
      if(!game->map_[row][col].closed_)
      {
        fields++;
      }
    }
  }
  return fields;
}

//counts how many flags are on the field
long long countFlags(Game *game)
{
  long long flags = 0;
  for(long long row = 0; row < game->rows_; row++)
  {
    for(long long col = 0; col < game->cols_; col++)
    {
      if(game->map_[row][col].closed_ && game->map_[row][col].flagged_)
      {
        flags++;
      }
    }
  }
  return flags;
}


//loads game
int load(Game *game, char *path)
{
  FILE *file = fopen(path,"rb");
  if(file == NULL)
  {
    printf("Error: Failed to open file!\n");
    return CONTINUE;
  }
  char magic_number[4];
  fread( magic_number, 1, 4, file);
  if(strcmp(magic_number,"ESP\0") != 0)
  {
    fclose(file);
    printf("Error: Invalid file content!\n");
    return CONTINUE;
  }

  deallocateFields(game);
  fread(&game->rows_, sizeof(long long), 1, file);
  fread(&game->cols_, sizeof(long long), 1, file);

  if(mapCreation(game)==MEMORY_ISSUE)
  {
    fclose(file);
    return MEMORY_ISSUE;
  }

  long long fields = game->rows_ * game->cols_;
  long long blocks = (fields + 7) / 8;

  for(long long block = 0; block < blocks; block++)
  {
    uint8_t valid_bits;
    uint8_t mine_bits;
    uint8_t opened_bits;
    uint8_t flagged_bits;

    fread(&valid_bits, 1, 1, file);
    fread(&mine_bits, 1, 1, file);
    fread(&opened_bits, 1, 1, file);
    fread(&flagged_bits, 1, 1, file);

    for (int bit = 0; bit < 8; bit++)
    {
      long long field_index = block * 8 + bit;
      if (field_index >= fields)
      {
        break;
      }
      Field *field = &game->map_[field_index / game->cols_][field_index % game->cols_];
      if (valid_bits & (1 << bit))
      {
        field->mine_ = (mine_bits & (1 << bit)) ? 1 : 0;
        field->closed_ = (opened_bits & (1 << bit)) ? 0 : 1;
        field->flagged_ = (flagged_bits & (1 << bit)) ? 1 : 0;
      }
      else
      {
        field->mine_ = 0;
        field->closed_ = 1;
        field->flagged_ = 0;
      }
    }
  }
  setAdjMines(game);
  game->mines_ = countMines(game);
  game->remaining_flags_ = game->mines_ - countFlags(game);
  game->fields_no_mine_ = game->rows_ * game->cols_ - game->mines_;
  game->opened_fields_ = countOpenedFields(game);
  fclose(file);
  printMap(game);
  return CONTINUE;
}

//reads command and executes it, returns CONTINUE if everythings alright, returns MEMORY_ISSUE if there is one
int execute(Game *game)
{
  long long row;
  long long col;
  char filename[ARGUMENT_SIZE];
  char cmd[INPUT_SIZE];
  if(readInput(game, cmd, &row, &col, filename) == INPUT_ERROR)
  {
    return CONTINUE;
  }

  if(strcmp(cmd, "start")==0)
  {
    startGame(game, row, col);
    printMap(game);
  }

  if(strcmp(cmd,"open")==0)
  {
    open(game, row, col);
    if(game->running_)
    {
      printMap(game);
    }
  }

  if(strcmp(cmd,"flag")==0)
  {
    flag(game, row, col);
    printMap(game);
  }

  if(strcmp(cmd,"dump")==0)
  {
    dump(game);
    printMap(game);
  }

  if(strcmp(cmd,"save")==0)
  {
    save(game, filename);
  }

  if(strcmp(cmd,"load")==0)
  {
    if(load(game, filename) == MEMORY_ISSUE)
    {
      return MEMORY_ISSUE;
    }
  }

  if(strcmp(cmd, "quit")==0)
  {
    game->running_ = false;
    printMap(game);
  }
  return CONTINUE;
}
