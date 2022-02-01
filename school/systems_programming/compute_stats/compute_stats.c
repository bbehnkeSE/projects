#include <stdio.h>
#include <stdlib.h>

struct numlist
{
    float *list;    /* points to a list of numbers */
    int   len;      /* number of items in list     */
    float min,      /* the minimal value in list   */
          max,      /* the maximal value in list   */
          avg;      /* the mean of the numbers     */
};

void compute_stats(struct numlist *listptr)
{
    /* find min value */
    listptr->min = listptr->list[0];
    for(int i = 1; i < listptr->len; ++i)
        if(listptr->list[i] < listptr->min)
            listptr->min = listptr->list[i];

    /* find max value */
    listptr->max = listptr->list[0];
    for(int i = 1; i < listptr->len; ++i)
        if(listptr->list[i] > listptr->max)
            listptr->max = listptr->list[i];

    /* calculate average */
    for(int i = 0; i < listptr->len; ++i)
        listptr->avg += listptr->list[i];
    
    listptr->avg /= listptr->len;
}


int main()
{
    float numbers[] = { 3.2, -10, 191.5, 93, 94, 10, 78, 22, -177 };
    const int size  = sizeof(numbers)/sizeof(numbers[0]);   // Gets size of array

    struct numlist *nums = malloc(sizeof(struct numlist));  // Allocates memory for the struct ptr
    nums->list = numbers;
    nums->len  = size;


    // Prints array
    printf("Numbers: [");
    for(int i = 0; i < size; ++i)
    {
        printf("%.2f", nums->list[i]);
        if(i < size - 1)
            printf(", ");

    }
    printf("]\n");

    compute_stats(nums);
    printf("min value is: %.2f\n", nums->min);
    printf("max value is: %.2f\n", nums->max);
    printf("avg value is: %.2f\n", nums->avg);

    free(nums);     // frees memory
    return 0;
}