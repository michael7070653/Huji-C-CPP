#include "test_bus_lines.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#define ZERO 0
#define ONE 1
#define EQUAL 0



//TODO add implementation here


void check_size(BusLine *start_sort, BusLine *end_sort,
                BusLine *start_org,BusLine *end_org,
                int *size_or,int *size_sort)
                {


    for (int j = 0;(start_org + j) <= end_org;j++)
    {
        (*size_or)++;
    }


    for (int i = 0;(start_sort +i) <=end_sort;i++)
    {
        (*size_sort)++;
    }
}


///CHECK IF TWO ARR
int is_equal (BusLine *start_sorted,
              BusLine *end_sorted, BusLine *start_original,
              BusLine *end_original)
{
    /// CHECK IF SIZE ARR EQUAL.
    int size_org = ZERO;
    int size_sort = ZERO;
    check_size(start_sorted,end_sorted,
               start_original,end_original,&size_org,&size_sort);
    if (size_org!=size_sort)
    {

        return EXIT_FAILURE;
    }
    ///CHECK IF ORIGINAL = SORT
    int run = ZERO;

    for(int i = 0;(start_original + i) <= end_original;i++)
    {
        int bool = ZERO;

        for(int j = 0;(start_sorted +j )<=end_sorted;j++)
        {
            if(strcmp((start_original + i)->name,
                      (start_sorted +j)->name) == EQUAL)
            {
                bool = ONE;
                run++;
                break;
            }

        }
        if (bool == ZERO)
        {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;

}







int is_sorted_by_distance (BusLine *start, BusLine *end)
{
    int i = 0;
    while (start + i < end)
    {
        if ((start+i)->distance > ((start+i)+ONE)->distance)
        {
            return EXIT_FAILURE;
        }
        i++;
    }
    return EXIT_SUCCESS;

}


int is_sorted_by_duration (BusLine *start, BusLine *end)
{
    int i = 0;
    while (start + i < end)
    {
        if ((start+i)->duration > ((start+i)+ONE)->duration)
        {
            return EXIT_FAILURE;
        }
        i++;
    }



    return EXIT_SUCCESS;
}




int is_sorted_by_name (BusLine *start, BusLine *end)
{
    int i = 0;
    while (start + i < end)
    {
        if ((start+i)->name > ((start+i)+ONE)->name)
        {
            return EXIT_FAILURE;
        }
        i++;
    }
    return EXIT_SUCCESS;
}


