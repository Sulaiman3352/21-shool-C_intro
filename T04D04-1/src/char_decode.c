#include <stdio.h>

#define SIZE 32

int main()
{
    int arg;
    char string[SIZE];
    int i = 0;
    printf("chose an operation mode (0–encoding or 1–decoding): ");
    scanf("%d",&arg);

    if ( arg == 0){
        printf("Text to translate: ");
        fgets(string,SIZE,stdin);
        while(string[i] != '\n')
        {
            printf("%2x ",string[i]);
            i++;
        }
        putchar(string[i]);
    }else if (arg == 1){
        char output[SIZE];
        int c;
        int x = 0;

        printf("Type hex digits, 0 to end: ");
        while(x < SIZE)
        {
            scanf("%2x",&c);
            output[x] = (char)c;
            if(c == 0) break;
            x++;
        }
        printf("\n%s\n",output);
    }
    return(0);
}