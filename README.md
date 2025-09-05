# C_structured_Programming

**Collection of small programs in C, done while learning programming**
- [Spice card game](#Spice-card-game)
- [Minesweeper](#Minesweeper)
- [Electronic shopping process](#Electronic-shopping-process)
- [Evolving spelling puzzle](#Evolving-spelling-puzzle)
- [Hangman](#Hangman)
- [Juice filling machine](#Juice-filling-machine)
- [Election simulation program](#Election-simulation-program)

## Spice card game
***./Spice_card_game <CONFIG (file path)>***

A card game for two players which is loosely inspired by "Spicy". All cards have two characteristics:
a spice and a value. The game is started with a command line argument which leads to config file containing
all playing cards. The game is played in multiple rounds. Each round consists of the players taking 
alternating turns. On their turn, a player plays a card from their hand face down and tells the other player 
what the card shows. The other player can believe what has been said and continue with their own turn, or 
challenge the first player on one of the two characteristics to see if it was a lie. Players score points for 
catching lies, but if a player challenges a card and the challenged characteristic was not a lie, the other
player gets points. Challenging a card ends the current round and starts the next one. The game ends when the
draw pile is empty and the player with the most points wins.


## Minesweeper
***./Minesweeper [--size x] [--mines x] [--seed x]***

A game inspired by the game Minesweeper, its played on a 2-D grid of fields. The goal is to open
all fields, except the ones which hide mines. If a field with a mine is opened, the mine explodes
and the game is lost. Each opened field bears the number of mines on the 8 fields surrounding it,
or no number if there are no mines. Whenever a field is opened, if it bears no number, all adjacent
fields are also opened until each opened field bears a number. If the player suspects a field to hide 
a mine, they can put a flag on it. The game is over when all fields which do not contain mines are opened.
The first opened field never contains a mine. Opening the first field triggers the generation of the map.

## Electronic shopping process
***./Electronic_shopping_process***

A program that implements a basic shopping list management system. The user is prompted to
enter the name of the shopping list. After that, the program waits for input of the name and
quantity of each item. This process continues until the user terminates the program with a command.

## Evolving spelling puzzle
***./Evolving_spelling_puzzle <SOLUTION (five-letter word)> [COLOR_ENABLE (1/0)]***

A game inspired by the online word guessing game Wordle. The goal of the game is to guess a
five-letter word within six tries. After each guess, the player gets told if the letters  of
the guess are part of the solution and if they are in the correct position.

## Hangman
***./Hangman***

A game for two players, one thinks of a word and the other tries to guess 
it by suggesting letters. The player only has a limited number of available guesses. 
When the player does not have any guess left, the player looses the game.
When the player guesses the word before that, the player wins.

## Juice filling machine
***./Juice_filling_machine***

A calculator for a juice filling machine. Various Juices, turned into canisters. 
Depending on the user's input, the calculator determines the price for the filling.

## Election simulation program
***./Election_simulation_program***

A simplified election simulator. There are always 5 candidates that can be voted for.
The user has to choose an ID for each candidate, input the number of votes and confirm.
The program then calculates the percentage of votes for each candidate and finds the winner.
