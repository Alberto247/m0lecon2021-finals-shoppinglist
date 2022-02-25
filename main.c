#include "things.h"
#include "addItems.h"
#include "ownList.h"
int giftReceived=0;

char ugetchar(void)
{
  static struct termios oldt, newt;

  /*tcgetattr gets the parameters of the current terminal
  STDIN_FILENO will tell tcgetattr that it should write the settings
  of stdin to oldt*/
  tcgetattr( STDIN_FILENO, &oldt);
  /*now the settings will be copied*/
  newt = oldt;

  /*ICANON normally takes care that one line at a time will be processed
  that means it will return if it sees a "\n" or an EOF or an EOL*/
  newt.c_lflag &= ~(ICANON | ECHO);

  /*Those new settings will be set to STDIN
  TCSANOW tells tcsetattr to change attributes immediately. */
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);

  /*This is your part:
  I choose 'e' to end input. Notice that EOF is also turned off
  in the non-canonical mode*/
  char c=getchar();

  /*restore the old settings*/
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
  return c;
}

void initialize(void)
{
    clrscr();
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

void showMenu(char** text, int length, int currentChoice){
  clrscr();
  puts("Welcome to ptmList, the program to help you keep your shopping lists in order!");
  for(int x=0; x<length; x++){
    if(x==currentChoice){
      printf("------------------\n");
    }else{
      printf("\n");
    }
    printf("%s\n", text[x]);
    if(x==currentChoice){
      printf("------------------\n");
    }else{
      printf("\n");
    }
  }
}

int mainMenuDown(int currentChoice){
  if(currentChoice!=3){
    currentChoice++;
  }
  char* options[4]={"| View item list |", "| View your list |", "| Secret gift    |", "| Exit           |"};
  showMenu(options, 4, currentChoice);
  return currentChoice;
}

int mainMenuUp(int currentChoice){
  if(currentChoice!=0){
    currentChoice--;
  }
  char* options[4]={"| View item list |", "| View your list |", "| Secret gift    |", "| Exit           |"};
  showMenu(options, 4, currentChoice);
  return currentChoice;
}

int mainMenu(){
  char input;
  int currentChoice=0;
  char* options[4]={"| View item list |", "| View your list |", "| Secret gift    |", "| Exit           |"};
  showMenu(options, 4, currentChoice);
  input=ugetchar();
  while (input!='\n'){
    if(input=='s'){
      currentChoice=mainMenuDown(currentChoice);
    }else if(input=='w'){
      currentChoice=mainMenuUp(currentChoice);
    }
    input=ugetchar();
  }
  return currentChoice;
}

void shop(){
  item ownList[51];
  for(int x=0; x<51; x++){
    ownList[x].id=255;
    ownList[x].quantity=255;
  }
  u_char itemsOnList=0;
  while(1==1){
    int choice = mainMenu();
    if (choice==0){
      itemListController(ownList, &itemsOnList);
    }else if (choice==1){
      myListController(ownList, &itemsOnList);
    }else if (choice==2){
      if(!giftReceived){
        int cancelPosition=256;
        for(int x=0; x<256; x++){
          if(ownList[x].id==255){
            cancelPosition=x;
            break;
          }
        }
        int currentChoice=secretGiftHandle(cancelPosition, ownList);
        if(currentChoice!=0xff){
          ownList[currentChoice].quantity=255;
          giftReceived=1;
        }
      }else{
        printf("You already received the gift.");
        sleep(3);
      }
    }else if (choice==3){
      return;
    }
  }
}


int main(void) {
  initialize();
  shop();
}
