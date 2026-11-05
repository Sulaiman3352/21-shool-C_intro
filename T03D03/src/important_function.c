#include <stdio.h>
#include <math.h>

int main(){
    float x;
    if (scanf("%f", &x) == 1){
    float y = 7e-3 * pow(x, 4) + ((22.8 * pow(x, 0.33) - 1e3) * x + 3) / (x * x / 2) - x * pow((10 + x),(2/x)) - 1.01;
    printf("%f",y);
    }else{
        printf ("n/a");
    }
    return 0;
}