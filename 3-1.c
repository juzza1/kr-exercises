#include <stdio.h>

int main()
{

    return 0;
}

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high && x != v[mid]) {
        mid = (low + high) / 2;
        if (x < v[mid]) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }
    if (x == v[mid]) {
        return mid;
    } else {
        return -1;
    }
}
