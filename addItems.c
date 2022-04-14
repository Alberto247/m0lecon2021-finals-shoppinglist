#include "things.h"
char ugetchar(void);

char* itemList[256]={"box of tissues"
,"water"
,"shovel"
,"carrot"
,"toy top"
,"coffee pot"
,"sailboat"
,"grid paper"
,"egg beater"
,"bread"
,"tooth pick"
,"clock"
,"box of chocolates"
,"magnifying glass"
,"pillow"
,"toy car"
,"kitchen knife"
,"spool of wire"
,"light bulb"
,"feather"
,"eraser"
,"tv"
,"quilt"
,"tennis racket"
,"roll of gauze"
,"magnet"
,"miniature portrait"
,"wrench"
,"belt"
,"frying pan"
,"keyboard"
,"word search"
,"spool of string"
,"notebook"
,"video games"
,"photo album"
,"lotion"
,"chenille stick"
,"broccoli"
,"container of pudding"
,"bag of popcorn"
,"scarf"
,"pair of dice"
,"game CD"
,"bed"
,"whale"
,"postage stamp"
,"tiger"
,"credit card"
,"desk"
,"toilet paper tube"
,"bottle of sunscreen"
,"candlestick"
,"toothpaste"
,"box of crayons"
,"handheld game system"
,"pearl necklace"
,"wireless control"
,"cement stone"
,"toothpick"
,"candy cane"
,"chicken"
,"keys"
,"cell phone"
,"lip gloss"
,"tomato"
,"whip"
,"ice cube"
,"empty tin can"
,"rubber band"
,"conditioner"
,"bookmark"
,"can of peas"
,"key"
,"sticky note"
,"bag of cotton balls"
,"paperclip"
,"panda"
,"cowboy hat"
,"car"
,"water bottle"
,"paper"
,"beaded necklace"
,"speakers"
,"salt shaker"
,"clay pot"
,"turtle"
,"toothbrush"
,"pocketknife"
,"brush"
,"bottle of syrup"
,"wine glass"
,"washing machine"
,"mop"
,"bouquet of flowers"
,"purse/bag"
,"hand mirror"
,"ipod"
,"towel"
,"bottle of perfume"
,"squirrel"
,"sandal"
,"eye liner"
,"monitor"
,"button"
,"plate"
,"trucks"
,"package of glitter"
,"flowers"
,"shirt"
,"remote"
,"television"
,"canvas"
,"crow"
,"acorn"
,"football"
,"cow"
,"garden spade"
,"notepad"
,"grocery list"
,"pepper shaker"
,"floor"
,"domino set"
,"sun glasses"
,"bow tie"
,"spice bottle"
,"money"
,"balloon"
,"plush unicorn"
,"rat"
,"dictionary"
,"camera"
,"hand fan"
,"box of markers"
,"buckle"
,"sidewalk"
,"toy robot"
,"tweezers"
,"candle"
,"light"
,"crowbar"
,"hair ribbon"
,"couch"
,"thermometer"
,"phone"
,"empty jar"
,"flyswatter"
,"book of matches"
,"tube of lipstick"
,"lion"
,"martini glass"
,"piece of gum"
,"microphone"
,"pair of sunglasses"
,"craft book"
,"bar of soap"
,"bottle"
,"socks"
,"umbrella"
,"bandana"
,"fork"
,"candy bar"
,"pair of knitting needles"
,"clothes"
,"can of chili"
,"bag"
,"clothes pin"
,"hand bag"
,"harmonica"
,"ice cream stick"
,"plush frog"
,"scallop shell"
,"pop can"
,"baseball"
,"pants"
,"milk"
,"bottle cap"
,"glass"
,"bottle of ink"
,"zipper"
,"bottle of paint"
,"pair of rubber gloves"
,"ball of yarn"
,"lamp shade"
,"picture frame"
,"extension cord"
,"hair pin"
,"stockings"
,"dog"
,"mouse pad"
,"pocketwatch"
,"class ring"
,"vase"
,"rusty nail"
,"banana"
,"cat"
,"ocarina"
,"helmet"
,"mirror"
,"toy plane"
,"tube of lip balm"
,"white out"
,"bottle of nail polish"
,"washcloth"
,"thread"
,"multitool"
,"giraffe"
,"shark"
,"bottle of soda"
,"door"
,"music CD"
,"shawl"
,"incense holder"
,"wooden spoon"
,"stop sign"
,"box"
,"tea pot"
,"snail shell"
,"ladle"
,"plush bear"
,"cork"
,"shirt button"
,"key chain"
,"pencil"
,"lime"
,"paint brush"
,"stick"
,"handbasket"
,"fishing hook"
,"snowglobe"
,"box of Q-tips"
,"lace"
,"shoes"
,"fake flowers"
,"roll of stickers"
,"stick of incense"
,"feather duster"
,"toy soldier"
,"shopping bag"
,"plush octopus"
,"hammer"
,"purse"
,"outlet"
,"needle"
,"sheep"
,"radio"
,"rabbit"
,"ipod charger"
,"nail clippers"
,"chalk"
,"book of jokes"
,"spatula"
,"plush pony"
,"bell"
,"lighter", "Cancel"};

void showList(char** text, int length, int currentChoice){
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
      printf("---------------------------------\n");
    }else{
      printf("\n");
    }
    printf(" %-30s\n", text[x]);
    if(x==currentChoice){
      printf("---------------------------------\n");
    }else{
      printf("\n");
    }
  }
  printf("w/s move, Enter select, Esc exit");
}

int listMenuDown(int currentChoice){
  if(currentChoice!=255){
    currentChoice++;
  }
  showList(itemList, 256, currentChoice);
  return currentChoice;
}

int listMenuUp(int currentChoice){
  if(currentChoice!=0){
    currentChoice--;
  }
  showList(itemList, 256, currentChoice);
  return currentChoice;
}

int itemListHandle(int currentChoice){
  char input;
  showList(itemList, 256, currentChoice);
  input=ugetchar();
  while (input!='\n' && input!=0x1b){
    if(input=='s'){
      currentChoice=listMenuDown(currentChoice);
    }else if(input=='w'){
      currentChoice=listMenuUp(currentChoice);
    }
    input=ugetchar();
  }
  if(input==0x1b){
    currentChoice=0xff;
  }
  return currentChoice;
}

void showBuyMenu(char** text, int length, int currentChoice, unsigned int currentQuantity){
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
    printf(" %-30s", text[x]);
    if(x==currentChoice){
      printf("| Quantity: %02u |\n", currentQuantity);
      printf("---------------------------------------------------\n");
    }else{
      printf("\n");
      printf("\n");
    }
  }
  printf("w/s select quantity, Enter insert in list, Esc exit");
}

int addItemHandler(int currentChoice){
  char input;
  unsigned int amount=0;
  showBuyMenu(itemList, 256, currentChoice, amount);
  input=ugetchar();
  while (input!='\n' && input!=0x1b){
    if(input=='s'){
      amount=(amount+1)%100;
    }else if(input=='w'){
      amount=(amount-1)%100;
    }
    showBuyMenu(itemList, 256, currentChoice, amount);
    input=ugetchar();
  }
  if(input==0x1b){
    amount=0x00;
  }
  return amount;
}

void itemListController(item *list, u_char *items){
  int currentChoice=0;
  while(1==1){
    currentChoice=itemListHandle(currentChoice);
    if(currentChoice==0xff){
      return;
    }
    if ((*items)>=50){
      clrscr();
      printf("Your list is currently full, please remove something before adding new items!");
      sleep(3);
      return;
    }else{
      u_char amount=addItemHandler(currentChoice)%256;
      if(amount!=0){
        list[*items].id=currentChoice;
        list[*items].quantity=amount;
        (*items)++;
      }
    }
  }
}
