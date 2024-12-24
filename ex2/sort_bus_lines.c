#include "sort_bus_lines.h"
#include <stdlib.h>
#define ZERO 0
#define ONE 1
void swap(BusLine *bus_1, BusLine *bus_2);
//void print_arr(BusLine *start, BusLine *end);
void helper_quick_sort (BusLine *start, BusLine *end, SortType sort_type);


//TODO add implementation here



void quick_sort (BusLine *start, BusLine *end, SortType sort_type)
{

    helper_quick_sort(start, end, sort_type);}




void helper_quick_sort (BusLine *start, BusLine *end, SortType sort_type)
{
if (start < end)
    {
    /// CALL PARTITION
    BusLine *pivot_index = partition(start,end ,sort_type);

    ///LEFT AREA
    helper_quick_sort(start, pivot_index - ONE,sort_type);

    ///RIGHT AREA
    helper_quick_sort(pivot_index + ONE, end,sort_type);
    }

}












BusLine *partition (BusLine *start, BusLine *end, SortType sort_type)
{

    int pivot = sort_type == DISTANCE ? end->distance: end->duration;
    int low = - 1;///low -1

    for(int i = 0; start + i < end; i++)
    {
        int value = sort_type
                == DISTANCE ? (start + i)
                ->distance: (start + i)->duration;
        if (value < pivot)
        {
            low++;
            // Swap *low and *j
            swap(start + low,start + i);
        }
    }
    swap(end,start + low + ONE);
    return (start + low + ONE);

}

///SWAP WITH TWO BUSSES

void swap(BusLine *bus_1, BusLine *bus_2)
{
    BusLine temp = *bus_2;
    *bus_2 = *bus_1;
    *bus_1 = temp;
}


void helper_bubble_sort(BusLine *start, BusLine *end)
{

//    for (BusLine *head = start; start<= end; head++)
//    free(start);
    for(int j = 0; start + j <= end; j++)
    {
        int one_or_zero = ZERO;

//        for(BusLine *temp = start; temp < end; temp++)
        for(int i = 0; start + i < end;i++)
        {

            if(strcmp((start + i)->name, ((start + i)+ ONE)->name) > ZERO)
            {
                swap((start + i), (start + i) + ONE);
                one_or_zero = ONE;
            }

        }
        if(!one_or_zero)
        {
            break;
        }
    }
}





void bubble_sort (BusLine *start, BusLine *end)
{
    helper_bubble_sort(start,end);

}


