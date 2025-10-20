int n = 0U;

// recursive fibo_recursivennaci - not good in embedded apps due to being susceptible to stack overflow
int fibo_recursive(int n)
{
    if (n <= 1U)
        return n;

    return (fibo_recursive(n-1) + fibo_recursive(n-2));
}

int fibo_linear(int n)
{
    int a = 0U;
    int b = 1U;

    if (n <= 0)
        return 0;
    if (n == 1)
        return 1;

    for (int i = 2; i <= n; ++i)
    {
        int c = a + b;
        a = b;
        b = c;
    }

    return b;
}

int main(void)
{
    if (fibo_recursive(3) != fibo_linear(3))
    {
        // error occured
        while(1);
    }

    // worked fine
    while(1);
}
