struct A{
    int XYZ, ABC;
};

int main(){
    struct A obj;
    obj.XYZ = 1;
    obj.ABC = 2;
    printf("%d %d\n",obj.ABC,obj.XYZ);
    obj.ABC = obj.XYZ;
    obj.ABC = obj.XYZ*obj.ABC;
    printf("%d %d\n",obj.ABC,obj.XYZ);
    return 0;
}
