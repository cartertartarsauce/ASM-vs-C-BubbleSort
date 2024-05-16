#include "c_bubbleSort.h"

//c++ BUBBLESORT
void c_bubbleSort(long long a[], int length)
{
    long long i, j, temp;

    for (i = 0; i < length; i++)
    {
        for (j = 0; j < length - i - 1; j++)
        {
            if (a[j + 1] < a[j])
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}

