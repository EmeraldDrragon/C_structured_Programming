//---------------------------------------------------------------------------------------------------------------------
// Electronic shopping list. Shopping list is represented by a linked list.
// User is asked to enter the name of the list, and then add items to it.
// The name and all shopping list items are stored on the heap.
//---------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define QUIT 0
#define OUT_OF_MEMORY 1
#define ALRIGHT 2

typedef struct _Item_
{
  char *name_;
  int quantity_;
  struct _Item_ *next_;
} Item;

//---------------------------------------------------------------------------------------------------------------------
/// creates an input buffer and dynamically allocates memory to it using malloc()
/// reads the input character by character and stores it on the heap, updating the buffer using realloc() as needed
///
/// @return char pointer to the created input buffer
char *getInput(void);

//---------------------------------------------------------------------------------------------------------------------
/// reads shopping list name and checks it for errors
///
/// @param name pointer to the name string from main()
/// @return int return code if it either ran into an error, quit or continued with the program
int readListName(char **name);

//---------------------------------------------------------------------------------------------------------------------
/// checks if inputted quantity is an integer with optional leading + or - and if its larger than 0
///
/// @param q_str item quantity input from user
/// @return true if it's okay, false if not
bool checkQuantity(char *q_str);

//---------------------------------------------------------------------------------------------------------------------
/// inserts an Item at the end of a given linked list. Allocates memory for the new item using malloc()
///
/// @param list pointer to the linked list
/// @param item_name name of an item
/// @param quantity quantity of an item
/// @return Item pointer to the updated linked list
Item *insertItem(Item *list, char *item_name, int quantity);

//---------------------------------------------------------------------------------------------------------------------
/// inserts an Item at the end of a given linked list. Allocates memory for the new item using malloc()
///
/// @param list pointer to the linked list
/// @param counter pointer to the counter variable from main()
/// @return int return code if it either ran into an error, quit or continued with the program
int readItems(Item **list, int *counter);

//---------------------------------------------------------------------------------------------------------------------
/// creates a new list (to be the sorted one) and uses selection sort to sort the items in the shopping list.
/// Iteratively deletes the min element from the unsorted list and appends it to the new list.
///
/// @param list pointer to the linked list
/// @param counter pointer to the counter variable from main()
/// @return Item pointer to the sorted list
Item *sortItems(Item **list, int counter);

//---------------------------------------------------------------------------------------------------------------------
/// calls sortItems() on the given list and prints the sorted shopping list
///
/// @param name name of the list from main()
/// @param list pointer to the linked list
/// @param counter counter of items
/// @return no return
void printList(char *name, Item **list, int counter);

//---------------------------------------------------------------------------------------------------------------------
/// frees items of the given linked list and also their names, as they are also dynamically allocated.
///
/// @param list pointer to the linked lists
/// @return no return
void freeItems(Item **list);

//---------------------------------------------------------------------------------------------------------------------
/// main function contains name of the shopping list, linked list of items and counter of items
///
/// @return integer exit code
int main(void)
{
  printf("\nWelcome to the\nElectronic Shopping Process!\n\n");
  char *name;
  int return_code = readListName(&name);
  if(return_code == OUT_OF_MEMORY)
  {
    return OUT_OF_MEMORY;
  }
  if(return_code == QUIT)
  {
    free(name);
    return QUIT;
  }
  int counter = 1;
  Item *list = NULL;
  return_code = readItems(&list, &counter);
  if(return_code == OUT_OF_MEMORY)
  {
    free(name);
    freeItems(&list);
    return OUT_OF_MEMORY;
  }
  if(return_code == QUIT)
  {
    free(name);
    freeItems(&list);
    return QUIT;
  }
  printList(name, &list, counter);
  free(name);
  freeItems(&list);
  return QUIT;
}

//---------------------------------------------------------------------------------------------------------------------
//functions

char *getInput(void)
{
  int size = 10;
  char* buffer = malloc(size * sizeof(char));
  if(buffer == NULL)
  {
    printf("[ERROR] Memory allocation failed!\n\n");
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
      buffer = realloc(buffer, size * sizeof(char));
      if(buffer == NULL)
      {
        printf("[ERROR] Memory allocation failed!\n\n");
        return NULL;
      }
    }
  }
  buffer[index] = '\0';
  return buffer;
}

int readListName(char **name)
{
  while(true)
  {
    printf("What do you want to name your shopping list?\n > ");
    *name = getInput();
    if(name == NULL)
    {
      return OUT_OF_MEMORY;
    }
    if(strcmp(*name,"quit") == 0)
    {
      return QUIT;
    }
    if(strlen(*name) == 0)
    {
      printf("[ERROR] The name cannot be empty!\n\n");
      free(*name);
      continue;
    }
    break;
  }
  return ALRIGHT;
}

bool checkQuantity(char *q_str)
{
  unsigned long len = strlen(q_str);
  if((q_str[0] != '+' && q_str[0] != '-' && (q_str[0] < '0' || q_str[0] > '9')) ||
    (len == 1 && (q_str[0] == '+' || q_str[0] == '-')) ||
    (len == 0))
  {
    printf("[ERROR] The quantity must be an integer!\n\n");
    return false;
  }
  for(unsigned long i = 0; i < len; i++)
  {
    if(i > 0 && ((q_str)[i] < '0' || q_str[i] > '9'))
    {
      printf("[ERROR] The quantity must be an integer!\n\n");
      return false;
    }
  }
  int q = atoi(q_str);
  if(q <= 0)
  {
    printf("[ERROR] The quantity must be greater than 0!\n\n");
    return false;
  }
  return true;
}

Item *insertItem(Item *list, char *item_name, int quantity)
{
  Item *new = malloc(sizeof(Item));
  if(new == NULL)
  {
    printf("[ERROR] Memory allocation failed!\n\n");
    return NULL;
  }
  new->name_ = item_name;
  new->quantity_ = quantity;
  new->next_ = NULL;
  if(list == NULL)
  {
    return new;
  }
  Item *current = list;
  while(current->next_ != NULL)
  {
    current = current->next_;
  }
  current->next_ = new;
  return list;
}

int readItems(Item **list, int *counter)
{
  while(true)
  {
    printf("\nItem %d:\n",*counter);

    while(true)
    {
      printf("What do you want to add?\n > ");
      char *name = getInput();
      if(name == NULL)
      {
        return OUT_OF_MEMORY;
      }
      if(strcmp(name,"quit") == 0)
      {
        free(name);
        return QUIT;
      }
      if(strcmp(name,"done") == 0)
      {
        free(name);
        return ALRIGHT;
      }
      if(strlen(name) == 0)
      {
        printf("[ERROR] Item name cannot be empty!\n\n");
        free(name);
        continue;
      }
      int quantity;
      while(true)
      {
        printf("How many pieces/grams/milliliters of this item do you want to get?\n > ");
        char *quantity_str = getInput();
        if(quantity_str == NULL)
        {
          return OUT_OF_MEMORY;
        }
        if(strcmp(quantity_str,"quit") == 0)
        {
          free(name);
          free(quantity_str);
          return QUIT;
        }
        if(!checkQuantity(quantity_str))
        {
          free(quantity_str);
          continue;
        }
        quantity = atoi(quantity_str);
        free(quantity_str);
        break;
      }
      *list = insertItem(*list,name,quantity);
      if(*list == NULL)
      {
        return OUT_OF_MEMORY;
      }
      break;
    }
    *counter = (*counter) + 1;
  }
}

Item *sortItems(Item **list, int counter)
{
  Item *new_list = NULL;
  Item *new_list_end = NULL;
  counter -= 1;
  while(counter > 0 && *list != NULL)
  {
    Item *current = *list;
    Item *previous = NULL;
    Item *min = *list;
    Item *before_min = NULL;

    //find min
    while(current != NULL)
    {
      if(strcmp(current->name_, min->name_) < 0)
      {
        min = current;
        before_min = previous;
      }
      else if(strcmp(current->name_, min->name_) == 0)
      {
        if(current->quantity_ < min->quantity_)
        {
          min = current;
          before_min = previous;
        }
      }
      previous = current;
      current = current->next_;
    }

    //delete min from list
    if(min == *list)
    {
      *list = (*list)->next_;
    }
    else if(before_min != NULL)
    {
      before_min->next_ = min->next_;
    }

    //append min to new list
    min->next_ = NULL;
    if(new_list == NULL)
    {
      new_list = min;
      new_list_end = min;
    }
    else
    {
      new_list_end->next_ = min;
      new_list_end = min;
    }
    counter--;
  }
  return new_list;
}

void printList(char *name, Item **list, int counter)
{
  *list = sortItems(list, counter);
  printf("\nShopping list: %s\n",name);
  Item *current = *list;
  while(current != NULL)
  {
    printf(" * %d %s\n",current->quantity_, current->name_);
    current = current->next_;
  }
}

void freeItems(Item **list)
{
  Item *current = *list;
  while(current != NULL)
  {
    Item* temp = current;
    current = current->next_;
    free(temp->name_);
    free(temp);
  }
  *list = NULL;
}
