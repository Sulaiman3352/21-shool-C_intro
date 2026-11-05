#include <stdio.h>

int max(int a,int b);

int main(){
    int x, y;

    if (scanf("%d %d", &x, &y) == 2){
        int max_r= max(x,y);
        printf ("%d",max_r);
    }else{
        printf ("n/a");
    }
    return 0;
}

int max(int a,int b){
    if (a > b) {
        int res=a;
        return res; 
    }else
    {
        int res=b;
        return res; 
    }
}