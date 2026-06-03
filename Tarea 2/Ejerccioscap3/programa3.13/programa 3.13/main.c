#include <stdio.h>

int main()
{
    int I;
    long long PRI = 0, SEG = 1, SIG;

    printf("\t %lld \t %lld", PRI, SEG);

    for (I = 3; I <= 50; I++)
    {
        SIG = PRI + SEG;
        PRI = SEG;
        SEG = SIG;
        printf("\t %lld", SIG);
    }

    return 0;
}
