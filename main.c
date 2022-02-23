#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "things.h"
#include <string.h>

typedef struct _item{
  u_char id;
  u_char quantity;
} item;


void initialize(void)
{
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    unsigned int randval;
    FILE *f;
    f = fopen("/dev/random", "r");
    fread(&randval, sizeof(randval), 1, f);
    fclose(f);
    srand(randval);
}

int get_int(){
  int input=-1;
  int result=scanf("%d", &input);
  if(result==EOF){
    exit(-1);
  }
  if(result==0){
    exit(-1);
  }
  return input;
}

void mainMenu(){
  puts("1. View item list");
  puts("2. View your list");
  puts("3. Add an item to your list");
  puts("4. Remove an item from your list");
  puts("5. Swap/merge two items from your list");
  puts("6. Save your list on disk");
  puts("9. Exit");
  printf("> ");
}

void printList(){
  for(int x=0; x<254; x++){
    if(x!=0 && x%3==0){
      printf("\n");
    }
    printf("%03d. %-30s", x, itemList[x]);
  }
  printf("\n");
}

void printMyList(item *list, u_char *items){
  if(*items==0){
    puts("There are no items in your list!");
  }else{
    for(int x=0; x<*items; x++){
      if(x!=0 && x%3==0){
        printf("\n");
      }
      printf("%03d. %s x %-20d", x, itemList[list[x].id], list[x].quantity);
    }
    printf("\n");
  }
}

char *randstring(size_t length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    char *randomString = NULL;

    if (length) {
        randomString = malloc(sizeof(char) * (length +1));

        if (randomString) {
            for (int n = 0;n < length;n++) {
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }

            randomString[length] = '\0';
        }
    }

    return randomString;
}

void saveList(item *list){
  char* name=randstring(50);
  char path[]="./data/";
  strcat(path, name);
  printf("%s", path);
  FILE* f = fopen(path, "w");
  if(f == NULL)
   {
      printf("Error opening file, contact an admin!");
      exit(1);
   }
  for(int x=0; x<51; x++){
    fprintf(f, "%u;%u;", list[x].id, list[x].quantity);
  }
  fclose(f);
  printf("Your list is available with the code %s\n", name);
  exit(0);
}

void buyItem(item *list, u_char *items){
  if(*items>=50){
    puts("Your list is full, please remove something before adding a new item, space ain't cheap");
  }else{
    printf("What item do you want to add? ");
    int itemToBuy_unsanitized=get_int();
    if (itemToBuy_unsanitized<0 || itemToBuy_unsanitized>=255){
      puts("That does not look like an item we have on catalogue, sorry");
      return;
    }
    u_char itemToBuy=itemToBuy_unsanitized%256;
    printf("How many %s do you want to buy? ", itemList[itemToBuy]);
    int quantity_unsanitized=get_int();
    if (quantity_unsanitized<=0 || quantity_unsanitized>1000){ //Bug inserted for testing!!! reduce 1000 to 100!!!
      puts("That does not look like a valid number, sorry");
      return;
    }
    u_char quantity=quantity_unsanitized%256;
    list[*items].id=itemToBuy;
    list[*items].quantity=quantity;
    (*items)++;
  }
}

void removeItem(item *list, u_char *items){
  if(*items<=0){
    puts("There are no items to be removed");
  }else{
    printf("What item do you want to remove? ");
    u_int itemToRemove=get_int();
    if(itemToRemove>=*items){
      puts("That item is not in your list");
    }else{
      for(int x=itemToRemove; list[x].id!=255 && list[x].quantity!=255; x++){
        list[x].id=list[x+1].id;
        list[x].quantity=list[x+1].quantity;
      }
      (*items)--;
    }
  }
}

void swapItems(item *list, u_char *items){
  printf("What is the first item you want to swap/merge? ");
  u_int item1=get_int();
  if(item1>=*items){
    puts("That item is not in your list");
    return;
  }
  printf("What is the second item you want to swap/merge? ");
  u_int item2=get_int();
  if(item2>=*items){
    puts("That item is not in your list");
    return;
  }
  if(item2==item1){
    puts("The two items are the same");
    return;
  }
  if(list[item1].id!=list[item2].id){
    item tmp;
    tmp.id=list[item1].id;
    tmp.quantity=list[item1].quantity;
    list[item1].id=list[item2].id;
    list[item1].quantity=list[item2].quantity;
    list[item2].id=tmp.id;
    list[item2].quantity=tmp.quantity;
  }else{
    if(item1>item2){
      int tmp=item1;
      item1=item2;
      item2=tmp;
    }
    u_char total=list[item1].quantity+list[item2].quantity;
    if(list[item1].quantity+list[item2].quantity<=99){
      list[item1].quantity+=list[item2].quantity;
    }
    for(int x=item2; list[x].id!=255 && list[x].quantity!=255; x++){
      list[x].id=list[x+1].id;
      list[x].quantity=list[x+1].quantity;
    }
    (*items)--;
  }
}

void shop(){
  puts("Welcome to ptmList, the program to help you keep your shopping lists in order!");
  item ownList[51];
  for(int x=0; x<51; x++){
    ownList[x].id=255;
    ownList[x].quantity=255;
  }
  u_char itemsOnList=0;
  while(1==1){
    mainMenu();
    int choice = get_int();
    if (choice==1){
      printList();
    }else if (choice==2){
      printMyList(ownList, &itemsOnList);
    }else if (choice==3){
      buyItem(ownList, &itemsOnList);
    }else if (choice==4){
      removeItem(ownList, &itemsOnList);
    }else if (choice==5){
      swapItems(ownList, &itemsOnList);
    }else if (choice==6){
      saveList(ownList);
    }else if (choice==9){
      exit(0);
    }else{
      puts("Unknown option");
    }
  }
}


int main(void) {
  initialize();
  shop();
}
