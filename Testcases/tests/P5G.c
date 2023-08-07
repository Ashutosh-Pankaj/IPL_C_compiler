int main(){
  int i, *j, k, **l;
  i=1;
  j=&i;
  printf("Outside loop: %d\n",*j);
  for(k=0; k<10; k=k+1){
    j=&k;
    if(k==5) printf("Inside loop: %d\n",*j);
    else ;
  }
  l = &j;
  printf("Outside loop: %d\n", **l);
  return 0;
}
