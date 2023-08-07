struct A{
    int a;
};
struct B{
    int b; 
};
struct C{
    int c;
};

struct C func(struct A m, struct B n){
    struct C temp;
    printf("%d %d\n",m.a,n.b);
    temp.c = m.a / n.b;
    n.b = 1;
    return temp;
}

int main(){
    struct A x;
    struct B y;
    struct C z;

    x.a = 5; y.b = 2; z.c = 3;
    printf("%d %d %d\n",x.a,y.b,z.c);
    z = func(x,y);
    printf("%d %d %d\n",x.a,y.b,z.c);
    return 0;
}
