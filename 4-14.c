#include <stdio.h>
#define swap(t, x, y) t z; z = x; x = y; y = z;

int main()
{
    int x = 3;
    int y = 4;
    printf("x: %d, y: %d\n", x, y);
    swap(int, x, y);
    printf("Swapped - x: %d, y: %d\n", x, y);
    return 0;
}
