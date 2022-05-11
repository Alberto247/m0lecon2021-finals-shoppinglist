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
