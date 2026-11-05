#include <stdio.h>

int sum(int a, int b);
int diff(int a, int b);
int prod(int a, int b);
int div(int a, int b);

int main()
{
    int x, y;
    
    if (scanf("%d %d", &x, &y) == 2){
        int sum_r = sum(x, y);
        int diff_r = diff(x,y);
        int prod_r = prod(x,y);
        int div_r = div(x,y);
        printf ("%d %d %d %d",sum_r,diff_r,prod_r,div_r);
    }else{
        printf ("n/a");
    }
    return 0;
}

int sum(int a, int b){
    int c = a+b;
    return  c ;
}

int diff(int a, int b){
    int c = a-b;
    return  c ;
}

int prod(int a, int b){
    int c = a*b;
    return  c ;
}

int div(int a, int b){
    int c = a/b;
    return  c ;
}