struct A{
    int a;
};

int func(struct A x, int n){
    if(n==0)
        return x.a;
    else ;
    
    printf("%d %d\n",x.a,n);
    x.a = 2 * func(x,n-1);
    return x.a;
}

int main(){
    int p;
    struct A obj;
    obj.a = 1;
    obj.a = func(obj,5);
    printf("%d\n",obj.a);
    return 0;    
}
