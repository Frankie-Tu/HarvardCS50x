#include <cs50.h>
#include <stdio.h>

void mario(void);
void loop_print(char symbol, int times);

/*
 * print mario pyramid
 * enter height:5
 *     #  #    
 *    ##  ##   
 *   ###  ###  
 *  ####  ####  
 * #####  #####
 */
int main(void)
{
    mario();
}

void mario(void)
{
    int height;
    do
    {    
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8); // valid heights only 1 to 8
    
    for (int x = 1; x <= height; x++)
    { 
    	loop_print(' ', height - x);
    	loop_print('#', x);
    	printf("  ");
    	loop_print('#', x);
    	printf("\n");
    }
}

void loop_print(char symbol, int times)
{
    for (int x = 0; x < times; x++)
    {
        printf("%c", symbol);
    }
}
