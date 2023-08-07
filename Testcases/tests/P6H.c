struct stellar_system
{
    int stellar_system_name;
    int habitable;
    int planet_count;
};

struct galaxy
{
    int stellar_system_number;
    int name;
    struct stellar_system system_code[100];
};


int main()
{
    int i, j;
    struct galaxy galaxy[10];
    for(i=0;i<10;i=i+1)
    {
        galaxy[i].name = 1;
        galaxy[i].stellar_system_number = i;
        for(j=0;j<i;j=j+1)
        {
            galaxy[i].system_code[j].stellar_system_name = j; 
            galaxy[i].system_code[j].habitable = j;
            galaxy[i].system_code[j].planet_count = j+1;
        }
    }

    for(i=0;i<10;i=i+1)
    {
        for(j=0;j<i;j=j+1)
        {
            printf("%d ",galaxy[i].system_code[j].stellar_system_name); 
            printf("%d ",galaxy[i].system_code[j].habitable);
            printf("%d\n",galaxy[i].system_code[j].planet_count);
        }
    }
    return 0;
}
