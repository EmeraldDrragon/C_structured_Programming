//---------------------------------------------------------------------------------------------------------------------
// Evolving Spelling Puzzle. The program gets 1-2 command line arguments.
// First one is the solution second (optional) color.
// The player tries to guess the word maximum 6 times, on each attempt he is shown the correctness of his guess
//---------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define GUESS_INPUT_SIZE 1024
#define ATTEMPTS 6
#define WORD_LENGTH 5
#define ANSI_COLOR_RESET "\x1b[0m"
#define ANSI_COLOR_BLUE "\x1b[94m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"

enum _ReturnCode_
{
  INVALID_USAGE = -1,
  EOF_INPUT = 0,
  WIN = 1,
  LOSE = 2,
  INPUT_ERROR = 3,
  ALRIGHT = 4
} ReturnCode;

//---------------------------------------------------------------------------------------------------------------------
/// returns the length of the string
///
/// @param str string
/// @return int the number of characters in an array
int strLen(const char *str);

//---------------------------------------------------------------------------------------------------------------------
/// checks <solution> argument given in command line and changes letters in it to uppercase
///
/// @param solution given <solution>
/// @return true if it's okay, false if not
bool checkSolution(char *solution);

//---------------------------------------------------------------------------------------------------------------------
/// checks <color mode> argument given in command line
///
/// @param color_mode given <solution>
/// @return true if it's okay, false if not
bool checkColorMode(const char *color_mode);

//---------------------------------------------------------------------------------------------------------------------
/// checks command line arguments
///
/// @param arg array of string arguments
/// @param count number of arguments
/// @return true if it's okay, false if not
bool checkCommandLine(char **arg, int count);

//---------------------------------------------------------------------------------------------------------------------
/// removes all whitespaces from the string
///
/// @param str string to remove whitespaces in
/// @return no return
void removeWhitespaces(char *str);

//---------------------------------------------------------------------------------------------------------------------
/// reads the input from stdin character by character
///
/// @param input string to store the input in
/// @return return code
int inputGuess(char *input);

//---------------------------------------------------------------------------------------------------------------------
/// copies one string into another
///
/// @param str_from string to copy from
/// @param str_into string to copy into
/// @return no return
void strCopy(const char *str_from, char *str_into);

//---------------------------------------------------------------------------------------------------------------------
/// searcher for a character in a string
///
/// @param word given string/word
/// @param c character/letter to find
/// @return true if it's there, false if not
bool charInWord(const char *word, char c);

//---------------------------------------------------------------------------------------------------------------------
/// prints words guessed now and in earlier attempts,
/// checks letters if they are in the solution or not and if they are in the correct positions
///
/// @param word_to_guess solution
/// @param words array of already guessed words
/// @param words_count number of already guessed words
/// @param color_mode color mode for printing
/// @return no return
void printWords(char *word_to_guess, char words[][WORD_LENGTH + 1], int words_count, int color_mode);

//---------------------------------------------------------------------------------------------------------------------
/// checks if two strings are equal
///
/// @param word_1 string 1
/// @param word_2 string 2
/// @return true if it is, false if not
bool strCompare(const char *word_1, const char *word_2);

//---------------------------------------------------------------------------------------------------------------------
/// analyses the input returns win if the player guessed the word
///
/// @param input input
/// @param word_to_guess solution
/// @param words array of already guessed words
/// @param words_count number of already guessed words
/// @param color_mode color mode for printing
/// @return return code
int guessAnalysis(char *input, char *word_to_guess, char words[][WORD_LENGTH + 1], int words_count, int color_mode);

//---------------------------------------------------------------------------------------------------------------------
/// contains logic for guessing the word and analyses the input for errors
///
/// @param word_to_guess solution
/// @param words array of already guessed words
/// @param words_count number of already guessed words
/// @param color_mode color mode for printing
/// @return return code
int guess(char *word_to_guess, char words[][WORD_LENGTH + 1], int words_count, int color_mode);

//---------------------------------------------------------------------------------------------------------------------
/// main function contains solution, array of the guessed words, color mode, attempts and the main loop of the game
///
/// @return integer exit code
int main(int argc, char *argv[])
{
  if(!checkCommandLine(argv, argc))
  {
    return INVALID_USAGE;
  }
  printf("Welcome to Evolving Spelling Puzzle!\n\n");
  char words[ATTEMPTS][WORD_LENGTH + 1];
  int color_mode = 0;
  if(argc == 3)
  {
    color_mode = atoi(argv[2]);
  }
  int attempts = ATTEMPTS;
  while(attempts > 0)
  {
    int words_count = ATTEMPTS - attempts;
    int guess_return_value = guess(argv[1],words,words_count,color_mode);
    if(guess_return_value == EOF_INPUT)
    {
      return EOF_INPUT;
    }
    if(guess_return_value == ALRIGHT)
    {
      attempts--;
    }
    if(guess_return_value == WIN)
    {
      return WIN;
    }
  }
  printf("Oh no! You did not guess the word correctly! :(\n");
  printf("The solution was: '%s'!\n",argv[1]);
  return LOSE;
}

//---------------------------------------------------------------------------------------------------------------------
//functions

int strLen(const char *str)
{
  int len = 0;
  while(str[len] != '\0')
  {
    len++;
  }
  return len;
}


bool checkSolution(char *solution)
{
  int len = strLen(solution);
  if(len != WORD_LENGTH)
  {
    printf("ERROR: Solution argument must be 5 characters long.\n");
    return false;
  }
  for(int i = 0; i < WORD_LENGTH; i++)
  {
    if(!((solution[i] >= 'A' && solution[i] <= 'Z') || (solution[i] >= 'a' && solution[i] <= 'z')))
    {
      printf("ERROR: Solution argument contains invalid characters.\n");
      return false;
    }
    if(solution[i] >= 'a' && solution[i] <= 'z')
    {
      solution[i] = solution[i] - 32;
    }
  }

  return true;
}

bool checkColorMode(const char *color_mode)
{
  if(strLen(color_mode) != 1 || (*color_mode != '1' && *color_mode != '0'))
  {
    printf("ERROR: (Optional) color output parameter can either be enabled (1) or not (0).\n");
    return false;
  }
  return true;
}


//return true if okay, false if not. Double pointer: pointer to an array of pointers to char
bool checkCommandLine(char **arg, int count)
{
  if(count != 2 && count != 3)
  {
    printf("Usage: ./a2 <solution> [optional: color_enabled]\n");
    return false;
  }

  for(int i = 0; i < count; i++)
  {
    if(i == 1)
    {
      if(!checkSolution(arg[i]))
      {
        return false;
      }
    }
    if(i == 2)
    {
      if(!checkColorMode(arg[i]))
      {
        return false;
      }
    }
  }
  return true;
}

void removeWhitespaces(char *str)
{
  int count = 0;
  int index = 0;
  while(str[index] != '\0')
  {
    if(str[index] != ' ')
    {
      str[count] = str[index];
      count++;
    }
    index++;
  }
  str[count] = '\0';
}

int inputGuess(char *input)
{
  int index = 0;
  int c;
  while((c = getchar()) != '\n' && c != EOF)
  {
    if(index < GUESS_INPUT_SIZE - 1)
    {
      input[index] = (char)c;
      index++;
    }
  }
  input[index] = '\0';
  if(c == EOF)
  {
    return EOF_INPUT;
  }
  return ALRIGHT;
}

void strCopy(const char *str_from, char *str_into)
{
  int index = 0;
  while(str_from[index] != '\0')
  {
    str_into[index] = str_from[index];
    index++;
  }
  str_into[index] = '\0';
}

bool charInWord(const char *word, char c)
{
  int index = 0;
  while(word[index] != '\0')
  {
    if(word[index] == c)
    {
      return true;
    }
    index++;
  }
  return false;
}

void printWords(char *word_to_guess, char words[][WORD_LENGTH + 1], int words_count, int color_mode)
{
  for(int i = 0; i < words_count + 1; i++)
  {
    printf("|");
    int index = 0;
    while(words[i][index] != '\0')
    {
      if(word_to_guess[index] == words[i][index])
      {
        if(color_mode == 0)
        {
          printf(" *%c",words[i][index]);
        }
        else
        {
          printf("  " ANSI_COLOR_BLUE "%c" ANSI_COLOR_RESET, words[i][index]);
        }
      }
      else if(charInWord(word_to_guess,words[i][index]))
      {
        if(color_mode == 0)
        {
          printf(" ~%c",words[i][index]);
        }
        else
        {
          printf("  " ANSI_COLOR_MAGENTA "%c" ANSI_COLOR_RESET, words[i][index]);
        }
      }
      else
      {
        printf("  %c",words[i][index]);
      }
      index++;
    }
    printf("\n");
  }
  printf("\n");
}

bool strCompare(const char *word_1, const char *word_2)
{
  int index = 0;
  while(word_1[index] != '\0')
  {
    if(word_1[index] != word_2[index])
    {
      return false;
    }
    index++;
  }
  return true;
}

int guessAnalysis(char *input, char *word_to_guess, char words[][WORD_LENGTH + 1], int words_count, int color_mode)
{
  strCopy(input,words[words_count]);
  printWords(word_to_guess, words, words_count, color_mode);
  if(strCompare(word_to_guess,words[words_count]))
  {
    printf("Good job! You solved this puzzle!\n");
    return WIN;
  }
  else
  {
    return ALRIGHT;
  }
}

int guess(char *word_to_guess, char words[][WORD_LENGTH + 1], int words_count, int color_mode)
{
  printf("Please enter your guess:\n > ");
  char input[GUESS_INPUT_SIZE + 1];
  if(inputGuess(input) == EOF_INPUT)
  {
    return EOF_INPUT;
  }
  removeWhitespaces(input);
  if(strLen(input) != 5)
  {
    printf("ERROR: Word is not 5 characters long.\n\n");
    return INPUT_ERROR;
  }
  for(int i = 0; i < strLen(input);i++)
  {
    if(!((input[i] >= 'A' && input[i] <= 'Z') || (input[i] >= 'a' && input[i] <= 'z')))
    {
      printf("ERROR: Word contains invalid characters.\n\n");
      return INPUT_ERROR;
    }
    if(input[i] >= 'a' && input[i] <= 'z')
    {
      input[i] = input[i] - 32;
    }
  }
  return guessAnalysis(input, word_to_guess, words, words_count, color_mode);
}
