struct A{
    int a,b,c;
};
struct B{
    int x,y,z;
    struct A p;
};
 int main(){
    struct B obj;
    obj.x = 0;
    obj.p.a = 0;
    printf("%d %d\n", obj.x++, obj.p.a+8);
    return 0;
 }
