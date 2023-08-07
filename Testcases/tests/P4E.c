struct A{
    int x,y,z;
};
 int add(struct A obj){
   printf("%d %d %d\n",obj.x,obj.y,obj.z);
    return obj.x + obj.y * obj.z;
 }

 int main(){
    struct A O;
    int x;
    O.x = 1; O.y = 2; O.z=3;
    x = add(O);
    printf("%d\n",x);
   printf("%d %d %d\n",O.x,O.y,O.z);
    return 0;
 }
