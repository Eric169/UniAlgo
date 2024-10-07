#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <limits.h>
//compile with gcc name.c -lm if needed
int main(){
    float f = 10+3;
    printf("10 + 3 = %0.f\n", f);
    f = 10 - 3;
    printf("10 - 3 = %0.f\n", f);
    f = 10 / 3;
    printf("10 / 3 = %0.f\n", f);
    f = 10 * 3;
    printf("10 * 3 = %0.f\n", f);
    f = 10 % 3;
    printf("10 %% 3 = %0.f\n", f);

    int z = INT_MAX + 1;//overflow
    printf("INT_MAX + 1 = %d\n", z);
    z = INT_MIN - 1;//underflow
    printf("INT_MIN - 1 = %d\n", z);
    long long a = LLONG_MAX + 1;//overflow
    printf("LLONG_MAX + 1 = %lld\n", a);
    a = LLONG_MIN - 1;//underflow
    printf("LLONG_MIN - 1 = %lld\n", a);
    unsigned int b = -1;//signed in unsigned
    printf("-1 in unsigned int = %u\n", b);
    int c = 13.56688;//truncation, implicit conversion
    printf("13.56688 in int = %d\n", c);
    int d = 1;
    d = d++; //side effect
    printf("d = d++ --> %d\n", d);
    int e = 10 / 3;//implicit conversion
    printf("10 / 3 = %d\n", e);

    //relational operators
    int l = 10, g = 11;
    printf("%d > %d: %s\n", l, g, (l>g) ? "true" : "false");
    printf("%d >= %d: %s\n", l, g, (l>=g) ? "true" : "false");
    printf("%d < %d: %s\n", l, g, (l<g) ? "true" : "false");
    printf("%d <= %d: %s\n", l, g, (l<=g) ? "true" : "false");
    printf("%d == %d: %s\n", l, g, (l==g) ? "true" : "false");
    printf("%d != %d: %s\n", l, g, (l!=g) ? "true" : "false");

    //logical
    int h=1, i=0;
    printf("!%d = %d\n", h, !h);
    printf("%d && %d = %d\n", h, i, h&&i);
    printf("%d || %d = %d\n", h, i, h||i);
    
    //bitwise
    int j = 1;
    i = 4;
    printf("%d << %d = %d\n", j, i, j<<i);
    printf("%d >> %d = %d\n", i, j, i>>j);
    printf("%d ^ %d = %d\n", j, i, j^i);
    printf("%d & %d = %d\n", i, j, i&j);
    printf("%d | %d = %d\n", j, i, j|i);
    printf("~%d = %d\n", i, ~i);

    double x = 0.5;
    printf("Arcocoseno di %.1f = %f\n", x, acos(x));
    printf("Arcoseno di %.1f = %f\n", x, asin(x));
    x = 1.0;
    printf("Coseno di %.1f = %f\n", x, cos(x));
    x = 2.0;
    printf("e^%.1f = %f\n", x, exp(x));
    x = exp(x);
    printf("Logaritmo naturale di %f = %f\n", x, log(x));
    x = 100;
    printf("Logaritmo in base 10 di %.1f = %.1f\n", x, log10(x));
    x = 3;
    double y = 4.23;
    printf("%.1f^%.1f = %f\n", x, y, pow(x,y));
    printf("Radice quadrata di %.2f = %f\n", y, sqrt(y));
    x = 3.1;
    printf("%.1f approssimato per eccesso = %.1f\n", x, ceil(x));
    x = 3.9;
    printf("%.1f approssimato per difetto = %.1f\n", x, floor(x));
    return 0;
}