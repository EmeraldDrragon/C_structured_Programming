//---------------------------------------------------------------------------------------------------------------------
// This program is a game Hangman, where one player think of the word and the other tries to guess it. The player
// has 5 attempts before game over.
//---------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

//---------------------------------------------------------------------------------------------------------------------
///
/// reads word from stdin and makes all characters uppercase, if input is '\n' returns
///
/// @param char *input input buffer from main function
///
/// @return no return
//
void readWordToGuess(char *input)
{
  printf("Word to look for:\n");
  printf(" > ");
  fgets(input,19,stdin);
  if(strcmp(input,"\n")==0)
  {
    return;
  }
  for(unsigned long i = 0; i < strlen(input); i++)
  {
    input[i] = (char)toupper(input[i]);
    if(input[i]=='\n')
    {
      input[i]='\0';
    }
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// copies the word_to_guess to word and turns all chars into '_'
///
/// @param char *word_to_guess word to guess from the player 1
/// @param char *word word that will be hidden
///
/// @return no return
//
void wordToGuessToWord(char *word_to_guess,char* word)
{
  strcpy(word,word_to_guess);
  for(unsigned long i = 0; i < strlen(word); i++)
  {
    word[i]='_';
  }
}

//---------------------------------------------------------------------------------------------------------------------
///
/// prints current state of the word
///
/// @param char *word word to print
///
/// @return no return
//
void printCurrentWord(char* word)
{
  for(unsigned long i = 0; i < strlen(word); i++)
  {
    printf("%c ",word[i]);
  }
  printf("\n");
}

//---------------------------------------------------------------------------------------------------------------------
///
/// returns false if the letter was guessed already, true if not
///
/// @param char guess guessed letter
/// @param char *guessed_letters array of already guessed letters
///
/// @return bool true or false
//
bool checkForGuessedLetters(char guess,char* guessed_letters)
{
  for(unsigned long i = 0; i < strlen(guessed_letters); i++)
  {
    if(guessed_letters[i]==guess)
    {
      printf("Letter %c was used already!\n",guess);
      return false;
    }
  }
  strncat(guessed_letters,&guess,1);
  return true;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// checks the guess if its correct or not and if it was already guessed
///
/// @param int *attempts left attempts from main
/// @param char *word_to_guess word to guess from the player 1
/// @param char *word hidden word
/// @param char guess guessed letter
/// @param char *guessed_letters array of already guessed letters
///
/// @return no return
//
void checkGuess(int *attempts, char *word_to_guess, char *word, char guess, char *guessed_letters)
{
  if(!checkForGuessedLetters(guess, guessed_letters))
  {
    return;
  }
  int flag = 0;
  for(unsigned long i = 0; i < strlen(word_to_guess); i++)
  {
    if(word_to_guess[i]==guess)
    {
      word[i]=word_to_guess[i];
      flag = 1;
    }
  }
  if(flag == 0)
  {
    (*attempts)--;
  }
  printCurrentWord(word);
}

//---------------------------------------------------------------------------------------------------------------------
///
/// checks the word if its fully guessed or not
///
/// @param char *word hidden word to check
///
/// @return bool true or false
//
bool checkWord(char *word)
{
  for(unsigned long i = 0; i < strlen(word); i++)
  {
    if(word[i] == '_')
    {
      return false;
    }
  }
  return true;
}

//---------------------------------------------------------------------------------------------------------------------
///
/// main function contains variables and main game loop
///
/// @param no parameters
///
/// @return 0
//
int main()
{
  int attempts = 5;
  char word_to_guess[20];
  readWordToGuess(word_to_guess);
  if(strcmp(word_to_guess,"\n")==0)
  {
    return 0;
  }
  char word[20];
  wordToGuessToWord(word_to_guess,word);
  char guessed_letters[30] = "0";
  char guess = '_';
  while(attempts > 0)
  {
    if(guess!='\n')
    {
      printf("Attempts left: %d\n",attempts);
      printf("Enter a letter:\n");
      printf(" > ");
    }
    guess = (char)getchar();
    guess = (char)toupper(guess);
    if(guess!='\n')
    {
      checkGuess(&attempts,word_to_guess,word,guess,guessed_letters);
    }
    if(checkWord(word))
    {
      break;
    }
  }
  if(attempts==0)
  {
    printf("LOST! The Word was %s\n",word_to_guess);
  }
  else
  {
    printf("Congratulations, you won!\n");
  }
  return 0;
}
