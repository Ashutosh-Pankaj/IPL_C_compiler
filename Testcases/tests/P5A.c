struct node{
  int val;
  struct node *next;
};
int main(){
  struct node head, *headptr, tail, *tailptr;
  head.val=5;
  head.next=0;
  tail.val=10;
  tail.next=0;
  printf("Assigned values: Head %d, Tail %d\n", head.val, tail.val);
  headptr = &head;
  tailptr = &tail;
  printf("Pointer access values: Head %d, Tail %d\n", headptr->val, tailptr->val);
  headptr->val=20;
  headptr->next=tailptr;
  printf("Changed values %d and %d\n",headptr->val,tailptr->val);
  return 0;
}
