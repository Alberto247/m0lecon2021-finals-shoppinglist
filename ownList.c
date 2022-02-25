#include "things.h"
char ugetchar(void);
extern char* itemList[256];

typedef struct _action{
  int id;
  char input;
} action;

void showMyList(item* text, int length, int currentChoice){
  clrscr();
  int start=currentChoice>=5 ? currentChoice-5 : 0;
  int end = (currentChoice+6)<=length ? currentChoice+6 : length;
  if(start==0){
    end=MIN(11, length);
  }
  if(end==length){
    start=MAX(length-10, 0);
  }
  //printf("%d %d %d", currentChoice, start, end);
  for(int x=start; x<end; x++){
    if(x==currentChoice){
      printf("---------------------------------------------------\n");
    }else{
      printf("\n");
    }
    printf(" %-30s", itemList[text[x].id]);
    if(text[x].id!=255){
      printf("| Quantity: %02u |\n", text[x].quantity);
    }else{
      printf("\n");
    }
    if(x==currentChoice){
      printf("---------------------------------------------------\n");
    }else{
      printf("\n");
    }
  }
  printf("w/s move, d delete, m move, Esc exit");
}

int myListMenuDown(int currentChoice, int length, item *list){
  if(currentChoice!=length){
    currentChoice++;
  }
  showMyList(list, length+1, currentChoice);
  return currentChoice;
}

int myListMenuUp(int currentChoice, int length, item *list){
  if(currentChoice!=0){
    currentChoice--;
  }
  showMyList(list, length+1, currentChoice);
  return currentChoice;
}

void showSecretGift(item* text, int length, int currentChoice){
  clrscr();
  int start=currentChoice>=5 ? currentChoice-5 : 0;
  int end = (currentChoice+6)<=length ? currentChoice+6 : length;
  if(start==0){
    end=MIN(11, length);
  }
  if(end==length){
    start=MAX(length-10, 0);
  }
  //printf("%d %d %d", currentChoice, start, end);
  for(int x=start; x<end; x++){
    if(x==currentChoice){
      printf("---------------------------------------------------\n");
    }else{
      printf("\n");
    }
    printf(" %-30s", itemList[text[x].id]);
    if(text[x].id!=255){
      printf("| Quantity: %02u |\n", text[x].quantity);
    }else{
      printf("\n");
    }
    if(x==currentChoice){
      printf("---------------------------------------------------\n");
    }else{
      printf("\n");
    }
  }
  printf("Select an item in your shopping cart to get 255 items for free!");
  printf("w/s move, Enter select, Esc exit");
}

int secretGiftMenuDown(int currentChoice, int length, item *list){
  if(currentChoice!=length){
    currentChoice++;
  }
  showSecretGift(list, length+1, currentChoice);
  return currentChoice;
}

int secretGiftMenuUp(int currentChoice, int length, item *list){
  if(currentChoice!=0){
    currentChoice--;
  }
  showSecretGift(list, length+1, currentChoice);
  return currentChoice;
}

int secretGiftHandle(int length, item *list){
  char input;
  int currentChoice=0;
  showSecretGift(list, length+1, currentChoice);
  input=ugetchar();
  while (input!='\n' && input!=0x1b){
    if(input=='s'){
      currentChoice=secretGiftMenuDown(currentChoice, length, list);
    }else if(input=='w'){
      currentChoice=secretGiftMenuUp(currentChoice, length, list);
    }
    input=ugetchar();
  }
  if(input==0x1b){
    currentChoice=0xff;
  }
  if(currentChoice==length){
    currentChoice=0xff;
  }
  return currentChoice;
}


action myListHandle(int currentChoice, int length, item *list, u_char *itemcount){
  char input;
  showMyList(list, length+1, currentChoice);
  input=ugetchar();
  while (input!='\n' && input!=0x1b && input!='d' && input!='m'){
    if(input=='s'){
      currentChoice=myListMenuDown(currentChoice, length, list);
    }else if(input=='w'){
      currentChoice=myListMenuUp(currentChoice, length, list);
    }
    input=ugetchar();
  }
  if(input==0x1b){
    currentChoice=0xff;
  }
  if(currentChoice>=(*itemcount) && (input=='d' || input=='\n')){
    currentChoice=0xff;
  }
  action a;
  a.id=currentChoice;
  a.input=input;
  return a;
}

void showSelectSecondItem(item* text, int length, int currentChoice, int firstSelection){
  clrscr();
  int start=currentChoice>=5 ? currentChoice-5 : 0;
  int end = (currentChoice+6)<=length ? currentChoice+6 : length;
  if(start==0){
    end=MIN(11, length);
  }
  if(end==length){
    start=MAX(length-10, 0);
  }
  //printf("%d %d %d", currentChoice, start, end);
  for(int x=start; x<end; x++){
    if(x==currentChoice || x==firstSelection){
      printf("---------------------------------------------------\n");
    }else{
      printf("\n");
    }
    printf(" %-30s", itemList[text[x].id]);
    if(text[x].id!=255){
      printf("| Quantity: %02u |\n", text[x].quantity);
    }else{
      printf("\n");
    }
    if(x==currentChoice || x==firstSelection){
      printf("---------------------------------------------------\n");
    }else{
      printf("\n");
    }
  }
  printf("w/s move, m select second item, Esc exit");
}

int selectSecondItemMenuDown(int currentChoice, int length, item *list, int firstSelection){
  if(currentChoice!=length){
    currentChoice++;
  }
  showSelectSecondItem(list, length+1, currentChoice, firstSelection);
  return currentChoice;
}

int selectSecondItemMenuUp(int currentChoice, int length, item *list, int firstSelection){
  if(currentChoice!=0){
    currentChoice--;
  }
  showSelectSecondItem(list, length+1, currentChoice, firstSelection);
  return currentChoice;
}

int selectSecondItemMove(int firstItem, int length, item *list){
  char input;
  int currentChoice=firstItem;
  showSelectSecondItem(list, length+1, currentChoice, firstItem);
  input=ugetchar();
  while (input!='\n' && input!=0x1b && input!='m'){
    if(input=='s'){
      currentChoice=selectSecondItemMenuDown(currentChoice, length, list, firstItem);
    }else if(input=='w'){
      currentChoice=selectSecondItemMenuUp(currentChoice, length, list, firstItem);
    }
    input=ugetchar();
  }
  if(input==0x1b){
    currentChoice=0xff;
  }
  if(currentChoice==firstItem){
    currentChoice=0xff;
  }
  return currentChoice;
}


void removeItem(item *list, u_char *items, int position, int amount){
  if(amount< list[position].quantity){
    list[position].quantity-=amount;
  }else{
    for(int x=position; list[x].id!=255 && list[x].quantity!=255; x++){
      list[x].id=list[x+1].id;
      list[x].quantity=list[x+1].quantity;
    }
    (*items)--;
  }
}

void swapItems(item *list, u_char *items, int item1, int item2){
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
    if((u_char)(list[item1].quantity+list[item2].quantity)<=99){
      list[item1].quantity+=list[item2].quantity;
      for(int x=item2; list[x].id!=255 && list[x].quantity!=255; x++){
        list[x].id=list[x+1].id;
        list[x].quantity=list[x+1].quantity;
      }
      (*items)--;
    }else{
      clrscr();
      printf("Cannot merge the two stacks.");
      sleep(3);
    }
  }
}

void showDropMenu(item* text, int length, int currentChoice, unsigned int currentQuantity){
  clrscr();
  printf("%d", currentChoice);
  int start=currentChoice>=5 ? currentChoice-5 : 0;
  int end = (currentChoice+6)<=length ? currentChoice+6 : length;
  if(start==0){
    end=MIN(11, length);
  }
  if(end==length){
    start=MAX(length-10, 0);
  }
  //printf("%d %d %d", currentChoice, start, end);
  for(int x=start; x<end; x++){
    if(x==currentChoice){
      printf("---------------------------------------------------\n");
    }else{
      printf("\n");
    }
    printf(" %-30s", itemList[text[x].id]);
    if(x==currentChoice){
      printf("| Quantity to drop: %02u |\n", currentQuantity);
      printf("---------------------------------------------------\n");
    }else{
      printf("\n");
      printf("\n");
    }
  }
  printf("w/s select quantity to drop, Enter remove from list, Esc exit");
}

int dropMenuHandler(int currentChoice, item *list, int length){
  char input;
  unsigned int amount=list[currentChoice].quantity;
  unsigned int maxamount=amount;
  showDropMenu(list, length, currentChoice, amount);
  input=ugetchar();
  while (input!='\n' && input!=0x1b){
    if(input=='s'){
      amount=(amount+1)%(maxamount+1);
    }else if(input=='w'){
      amount=(amount-1)%(maxamount+1);
    }
    showDropMenu(list, length, currentChoice, amount);
    input=ugetchar();
  }
  if(input==0x1b){
    amount=0x00;
  }
  return amount;
}



void myListController(item *list, u_char *items){
  int currentChoice=0;
  while(1==1){
    int cancelPosition=256;
    for(int x=0; x<256; x++){
      if(list[x].id==255){
        cancelPosition=x;
        break;
      }
    }
    if((*items)>cancelPosition+1){
      cancelPosition=(*items)-1;
    }
    printf("AAAAAAAAAAAAAAA\n%d", *items);
    action a = myListHandle(currentChoice, cancelPosition, list, items);
    //printf("BBBBBBBBBBBBBBBB\n %d %d", a.id, a.input);
    if(a.id==0xff){
      return;
    }
    currentChoice=a.id;
    if(a.input=='d'){
      int amount=dropMenuHandler(currentChoice, list, cancelPosition);
      removeItem(list, items, a.id, amount);
    }
    if(a.input=='m'){
      int firstItemMove=a.id;
      int secondItemMove = selectSecondItemMove(firstItemMove, cancelPosition, list);
      if (list[firstItemMove].id!=0xff && list[secondItemMove].id!=0xff){
        swapItems(list, items, firstItemMove, secondItemMove);
      }
    }
  }
}
