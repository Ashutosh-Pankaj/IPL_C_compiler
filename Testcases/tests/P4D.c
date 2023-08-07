struct A1{
    int x,y,z;
};
struct A2{
    int a,b,c;
};

int func(struct A1 p, struct A2 q){
    int res;
    struct  A1 temp1;
    
    printf("%d %d %d %d %d %d\n",p.x,p.y,p.z,q.a,q.b,q.c);
    res = p.x * p.y - p.z / q.a + q.b * q.c;

    p = temp1;
    return res;
}
 int main(){
    struct A1 M;
    struct A2 N;
    int answer;

    M.x = 1; M.y = 2; M.z = 3;
    N.a = 1; N.b = 2; N.c = 3;

    answer = func(M,N);
    printf("%d",answer);
    printf("%d %d %d %d %d %d\n",M.x,M.y,M.z,N.a,N.b,N.c);
    return 0;
 }
