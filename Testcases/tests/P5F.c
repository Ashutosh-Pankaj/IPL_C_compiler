struct node{
  int cost, sold, type;
};
int isbig(struct node *ptr){
  if(ptr->cost*ptr->sold <= 1000){
    if(ptr->type==1) return 1;
    else return 0;
  }
  else{
    if(ptr->type==2) return 0;
    else return 1;
  }
}
void sellitems(struct node box, int sell){
  struct node *boxptr;
  boxptr = &box;
  printf("Currently sold %d boxes\n",boxptr->sold);
  while(sell>0){
    boxptr->sold = boxptr->sold+1;
    printf("Currently sold %d boxes\n",boxptr->sold);
    if(isbig(boxptr)){
      printf("Box is big now\n");
      if(box.type==1) box.type=0;
      else box.type=1;
    }
    else printf("Box isn't big now\n");
    sell = sell-1;
  }
}
int main(){
  struct node box;
  box.cost=10;
  box.sold=8;
  box.type=1;
  sellitems(box, 5);
  return 0;
}
