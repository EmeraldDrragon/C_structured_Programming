//---------------------------------------------------------------------------------------------------------------------
// Juice filling machine calculator: Depending on the user's input:
// juice type, litres and canister size; the calculator determines the price for the filling.
//---------------------------------------------------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>

//functions

//---------------------------------------------------------------------------------------------------------------------
///
/// The function takes an imput from the user about the juice type,
/// changes juice_type string to either orange or apple depending on the input.
///
///
/// @param juice_type_input takes in an input of the juice type, 1 or 2.
/// @param *juice_type pointer to a string juice_type to change the string inside the main function.
///
/// @return juice_type_input returns the input from the user.
//---------------------------------------------------------------------------------------------------------------------
int input_juice_choice(int juice_type_input, char *juice_type);

//---------------------------------------------------------------------------------------------------------------------
///
/// The function takes an imput from the user about the litres,
///
/// @param litres takes in an input of the litres, 1 to 1000.
///
/// @return litres returns the input from the user.
//---------------------------------------------------------------------------------------------------------------------
int input_litres(int litres);

//---------------------------------------------------------------------------------------------------------------------
///
/// The function takes an imput from the user about the canisters, depending on the chosen juice type
///
/// @param canister takes in an input of the canister.
/// @param juice_type_input determines the options for the canisters.
///
/// @return canister returns the input from the user.
//---------------------------------------------------------------------------------------------------------------------
int input_canister(int canister, int juice_type_input);

//---------------------------------------------------------------------------------------------------------------------
///
/// The function calculates how many canisters with chosen size can be filled with chosen litres of the juice.
/// The function then also calculates how many left-over litres are left.
///
/// @param litres chosen litres.
/// @param canister chosen canister size.
///
/// @return canister_quantity returns how many canisters are needed for the filling
//---------------------------------------------------------------------------------------------------------------------
int calculating_canister_quantity(int litres, int canister);

//---------------------------------------------------------------------------------------------------------------------
///
/// The function calculates the costs based on canister quantity, canister size and juice type and
/// prints all the costs as well as the total cost for everything.
///
/// @param canister_quantity how many canisters are needed for the input
/// @param canister chosen canister size.
/// @param juice_type_input chosen juice type
/// @param *juice_type pointer to the string juice_type in the main function
//---------------------------------------------------------------------------------------------------------------------
void calculating_cost(int canister_quantity, int canister, int juice_type_input, char *juice_type);

//---------------------------------------------------------------------------------------------------------------------
///
/// The function takes input on confirmation on either to fill the canisters or not.
///
/// @return confirmation_input returns the input from the user.
//---------------------------------------------------------------------------------------------------------------------
int input_confirmation();

int main() {
  //declaring variables
  int confirmation = 2;
  int juice_type_input = 0;
  char juice_type[7];
  int litres = 0;
  int canister = 0;
  int canister_quantity = 0;

  //intro
  printf("Welcome to the juice filling machine calculator!\n");

  // main loop
  while (confirmation == 2) {
    //initializing variables
    juice_type_input = 0;
    litres = 0;
    canister = 0;
    canister_quantity = 0;

    //inputing juice choice
    juice_type_input = input_juice_choice(juice_type_input, juice_type);

    //inputing litres
    litres = input_litres(litres);

    //inputing canister size
    canister = input_canister(canister, juice_type_input);

    //Calculating canister quantity
    canister_quantity = calculating_canister_quantity(litres, canister);

    //Calculating the cost
    calculating_cost(canister_quantity, canister, juice_type_input, juice_type);

    //inputing confirmation
    confirmation = input_confirmation();
  }

  //outro
  printf("\n");
  printf("The canisters will be filled as soon as we receive your payment.\n");
  printf("Thank you for using the juice filling machine calculator!\n");

  return 0;
}

//functions

//functions
int input_juice_choice(int juice_type_input, char *juice_type) {
  while ((juice_type_input != 1) && (juice_type_input != 2)) {
    printf("\n");
    printf("Which juice do you want to fill?\n");
    printf("1. Orange juice\n");
    printf("2. Apple juice\n");
    printf(" > ");
    scanf("%d", &juice_type_input);
    if ((juice_type_input != 1) && (juice_type_input != 2)) {
      printf("Invalid input! Please choose a valid juice.\n");
    }
  }

  if (juice_type_input == 1) {
    strcpy(juice_type, "orange");
  }
  if (juice_type_input == 2) {
    strcpy(juice_type, "apple");
  }

  return juice_type_input;
}

int input_litres(int litres) {
  while ((litres < 1) || (litres > 1000)) {
    printf("\n");
    printf("How many litres do you want to fill? (1 to 1000)\n");
    printf(" > ");
    scanf("%d", &litres);
    if ((litres < 1) || (litres > 1000)) {
      printf("Invalid input! Please choose a valid amount.\n");
    }
  }
  return litres;
}

int input_canister(int canister, int juice_type_input) {
  if (juice_type_input == 1) {
    while ((canister != 5) && (canister != 10) && (canister != 20)) {
      printf("\n");
      printf("Which size of canister would you like to use for your orange juice?\n");
      printf("- 5 litres\n");
      printf("- 10 litres\n");
      printf("- 20 litres\n");
      printf(" > ");
      scanf("%d", &canister);
      if ((canister != 5) && (canister != 10) && (canister != 20)) {
        printf("Invalid input! Please choose a valid canister size.\n");
      }
    }
  }
  if (juice_type_input == 2) {
    while ((canister != 5) && (canister != 15) && (canister != 25)) {
      printf("\n");
      printf("Which size of canister would you like to use for your apple juice?\n");
      printf("- 5 litres\n");
      printf("- 15 litres\n");
      printf("- 25 litres\n");
      printf(" > ");
      scanf("%d", &canister);
      if ((canister != 5) && (canister != 15) && (canister != 25)) {
        printf("Invalid input! Please choose a valid canister size.\n");
      }
    }
  }
  return canister;
}

int calculating_canister_quantity(int litres, int canister) {
  int canister_quantity = litres / canister;
  int leftover = litres % canister;
  printf("\n");
  printf("It is possible to fill %d canisters with the size of %d litres.\n", canister_quantity, canister);
  printf("This results in %d left-over litres.\n", leftover);
  return canister_quantity;
}

void calculating_cost(int canister_quantity, int canister, int juice_type_input, char *juice_type) {
  int juice_amount = canister_quantity * canister;

  double juice_costs = 0;
  if (juice_type_input == 1){
    juice_costs = juice_amount * 0.20;
  }
  if (juice_type_input == 2) {
    juice_costs = juice_amount * 0.15;
  }

  double canister_costs = 0;
  switch (canister) {
    case 5:
      canister_costs = canister_quantity * 0.10;
      break;
    case 10:
      canister_costs = canister_quantity * 0.15;
      break;
    case 15:
    case 20:
      canister_costs = canister_quantity * 0.20;
      break;
    case 25:
      canister_costs = canister_quantity * 0.25;
      break;
    default:
      break;
  }

  double total_costs = juice_costs + canister_costs + 5;

  printf("\n");
  printf("The filling costs are:\n");
  printf("----------------------------------------------\n");
  printf("- %d litres of %s juice: %.2f €\n", juice_amount, juice_type, juice_costs);
  printf("- %d canisters: %.2f €\n", canister_quantity, canister_costs);
  printf("- Flat rate for using the machine: 5.00 €\n");
  printf("----------------------------------------------\n");
  printf("This results in a total cost of %.2f €.\n", total_costs);
}

int input_confirmation() {
  int confirmation_input = 0;
  while ((confirmation_input != 1) && (confirmation_input != 2)) {
    printf("\n");
    printf("Are you sure you want to fill the canisters?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf(" > ");
    scanf("%d", &confirmation_input);
    if ((confirmation_input != 1) && (confirmation_input != 2)) {
      printf("Invalid input! Please choose a valid option.\n");
    }
  }
  return confirmation_input;
}
