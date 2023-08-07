struct storage
{
    int val;
    int values[10];
};

void foo(struct storage *s)
{
    s->values[5] = -1 * s->values[5];
}

int main()
{
    struct storage *some_name;
    int i;
    struct storage name;
    some_name = &name;
    some_name->val = 5;
    i = 0;
    while(i < 10)
    {
        some_name->values[i] = i + some_name->val;
        i = i+1;
    }
    foo(some_name);
    for(i = 0; i < 10; i = i+1)
    {
        printf("%d\n", some_name->values[i]);
    }
    return 0;
}
