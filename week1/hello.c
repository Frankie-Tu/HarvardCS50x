#include <stdio.h>
#include <cs50.h>

int main(void)
{
    char *myName = get_string("What is your name?: ");
    printf("hello, %s\n", myName);
}
