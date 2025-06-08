#include <stdio.h>
#include <math.h>
#define PI 3.1416
#define DENSITY 21500 
int main() {
    double rad;
    scanf("%lf", &rad);
    
    double vol = (4.0 / 3.0) * PI * pow(rad,3);
    double res = DENSITY * vol;
    printf("%.0lf", round(res)); // No newline at the end
    return 0;
}
