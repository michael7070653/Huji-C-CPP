#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


#define BASE 10
#define ONE 1



#define MAX_LINE_20 20
#define MAX_LINE_60 61
#define MAX_DURATION 100
#define MIN_DURATION 10
#define MAX_DIST 1000
#define MIN_DIST 0
#define FAILED_READ_BUSES 1
#define NUM_ARGS_VALID 2
#define FAILED_COMPARE 0
#define GOOD_EXTRACT 0
#define GOOD_CHECK 0


int check_valid_command_arg(int argc, char *argv[]);

//int check_valid_name(char name[MAX_LINE]);



/**
 * TODO add documentation.
 */



///TEST CODE



void print_arr(BusLine *start, int n)
{
    int i = 0;
    while (i <= n)
    {
        fprintf(stdout,"%s,%d,%d\n",(start+i )->name,
                (start+i )->distance, (start+i )->duration);
        i++;
    }
}

/// check validity command arg





void test_case_dist(BusLine *start_sort, BusLine *end_sort,
                    BusLine *start_org,BusLine *end_org)
{
    if (is_sorted_by_distance(start_sort,end_sort) ==0){
        fprintf(stdout,"TEST 1 PASSED:"
                       " The array is sorted by distance\n");
    }
    else
    {
        fprintf(stdout,"TEST 1 FAILED:"
                       " The array is not sorted by distance\n");
    }


    if (is_equal(start_sort,
                 end_sort,start_org, end_org) == 0)
    {
        fprintf(stdout,"TEST 2 PASSED:"
                       " The array has the same items after sorting\n");
    }
    else
    {
        fprintf(stdout,"TEST 2 FAILED:"
                       " The array has not have same items after sorting\n");

    }

}
void test_case_duration(BusLine *start_sort,
                        BusLine *end_sort,BusLine *start_org,BusLine *end_org)
{
    if (is_sorted_by_duration(start_sort,end_sort) ==0){
        fprintf(stdout,"TEST 3 PASSED:"
                       " The array is sorted by duration\n");
    }
    else
    {
        fprintf(stdout,"TEST 3 FAILED:"
                       " The array is not sorted by duration\n");
    }
    if (is_equal(start_sort,
                 end_sort,start_org,end_org) == 0)
    {
        fprintf(stdout,"TEST 4 PASSED:"
                       " The array has the same items after sorting\n");
    }
    else
    {
        fprintf(stdout,"TEST 4 FAILED:"
                       " The array has not have same items after sorting\n");

    }

}

void test_case_name(BusLine *start_sort,
                    BusLine *end_sort,BusLine *start_org,BusLine *end_org)
{
    if (is_sorted_by_name(start_sort,end_sort) ==0){
        fprintf(stdout,"TEST 5 PASSED: The array is sorted by name\n");
    }
    else
    {
        fprintf(stdout,"TEST 5 FAILED: The array is not sorted by name\n");
    }
    if (is_equal(start_sort,
                 end_sort,start_org,end_org) == 0)
    {
        fprintf(stdout,"TEST 6 PASSED:"
                       " The array has the same items after sorting\n");
    }
    else
    {
        fprintf(stdout,"TEST 6 FAILED:"
                       " The array has not have same items after sorting\n");

    }

}



/// HERE I DO ALL TEST.

int test_case(BusLine *start, BusLine *end, int n)
{


    BusLine *copy_bus = malloc(n * sizeof (BusLine));

    if (copy_bus==NULL){
        return EXIT_FAILURE;
    }
    ///COPY
    memcpy(copy_bus,start,n * sizeof(BusLine));
    ///
    quick_sort(start,end,DISTANCE);
    test_case_dist(start,end,
                   copy_bus,copy_bus + n - 1);

    quick_sort(start,end,DURATION);
    test_case_duration(start,
                       end,copy_bus,copy_bus + n - 1);

    bubble_sort(start, end);
    test_case_name(start,
                   end,copy_bus,copy_bus + n - 1);

    free(copy_bus);
    return EXIT_SUCCESS;
}







int check_valid_command_arg(int argc, char *argv[])
{
    if (argc != NUM_ARGS_VALID)
    {
        return EXIT_FAILURE;
    }

    if(strcmp(*(argv + 1),"by_distance") != 0
    && strcmp(*(argv + 1),"by_duration") != 0
       && strcmp(*(argv + 1),"by_name") !=0
       && strcmp(*(argv + 1),"test")!= 0)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


/// check validity of input n

int check_valid_input_k(char buffer[MAX_LINE_20], long *x,char *endptr)
{
    // Will be used to check for conversion errors

    fprintf(stdout,"Enter number of lines. Then enter\n");
    if (fgets(buffer, MAX_LINE_20, stdin) == NULL) {
        fprintf(stdout,"ERROR:f gets.\n");
        return EXIT_FAILURE;
    }

    // Use strtol to convert the string to a long integer
    *x = strtol(buffer, &endptr, BASE);
    // Check for conversion errors
    if (*endptr == '\0' || (*endptr == '\n' && endptr != buffer)) {
    } else {
        fprintf(stdout,"ERROR: please enter int > 0\n");
        return EXIT_FAILURE;
    }
    if (*x <= 0) {
        fprintf(stdout,"ERROR: please enter int > 0\n");
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}


/// set n from user
void get_k(long *k,char *end,char buffer[MAX_LINE_20])
{
    int bool  = 0;
    while (bool == 0)
    {
        if(check_valid_input_k(buffer,k,end) == 0)
        {
            bool = 1;
        }

    }
}







/// check validity of input name


int check_valid_name(char *name) {
    for (; *name != '\0'; name++) {
        if (!(((*name >= 'a' && *name <= 'z')
        || (*name >= '0' && *name <= '9')))) {
            return EXIT_FAILURE;
        }
    }
    return EXIT_SUCCESS;
}

/// check validity of input distance
int check_valid_distance(const int *dist )
{

    if (*dist< MIN_DIST|| *dist > MAX_DIST)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

/// check validity of input duration
int check_valid_duration(const int* dur)
{

    //check the val
    if (*dur < MIN_DURATION || *dur > MAX_DURATION)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}




///extract info from user
int extract_info(char *input,
                 char *line_name, int *distance, int *duration)
                 {
    // Assuming input format: "<line_name>, distance, duration"
    int result = sscanf(input, "%[^,],%d,%d", line_name, distance, duration);
    if (result != 3) {
        return EXIT_FAILURE; // Return 0 to indicate failure
    }

    return EXIT_SUCCESS; // Return 1 to indicate success
}



///build n bus from user



int build_bus(BusLine *start ,int n,int *dist, int* dur)
{
    int i = 0;
    for( ; i < n  ; i++)
    {   char buffer[MAX_LINE_60];
        char line_name[MAX_LINE_20];
        int bool = 0;
        while(bool == 0){
            fprintf(stdout,"Enter line info. Then enter\n");
            if(fgets(buffer,MAX_LINE_60,stdin) == NULL)
            {
                return EXIT_FAILURE;
            }
            if (extract_info(buffer,line_name,
                             dist,dur)!= GOOD_EXTRACT)
            {
                return EXIT_FAILURE;
            }
            if (check_valid_name(line_name)!= GOOD_CHECK)
            {
                fprintf(stdout,"ERROR: bus name should"
                               " contains only digits and small chars\n");
                continue;
            }
            if(check_valid_distance(dist) !=GOOD_CHECK)
            {
                fprintf(stdout,"ERROR: distance should be"
                               " an integer between 10 and 100 (includes)\n");
                continue;
            }
            if (check_valid_duration(dur)!=GOOD_CHECK )
            {
                fprintf(stdout,"ERROR: duration should be"
                               " an integer between 10 and 100 (includes)\n");
                continue;
            }
            bool = 1;
            strcpy((start+i)->name,line_name);
            (start+ i)->distance = *dist;
            (start + i)->duration = *dur;
        }
    }

    return EXIT_SUCCESS;
}







///sort the bus
// strat is pointer ""first bus""=strcut
void sort(BusLine *start, BusLine *end,char *argv)
{
    if(strcmp(argv,"by_duration") == GOOD_CHECK)
    {
        quick_sort(start,end,DURATION);
    } else if(strcmp(argv,"by_distance") == GOOD_CHECK)
    {
        quick_sort(start,end,DISTANCE);
    }
    else{
        bubble_sort(start,end);
    }
}



int main(int argc, char *argv[])
{
    if (check_valid_command_arg(argc, argv))
    {
        fprintf(stdout,"USAGE: not valid arg!\n");
        return EXIT_FAILURE;
    }

    char buffer[MAX_LINE_20];
    long n;
    char *endptr;
    endptr =NULL;
    // Will be used to check for conversion errors
    get_k(&n,endptr,buffer);
    int k = (int) n;

    BusLine* bus_struct = malloc(n * sizeof(BusLine));
    if (bus_struct == NULL){
        fprintf(stdout,"Error open arr\n");
        return EXIT_FAILURE;
    }
    int dist =0;
    int dur = 0;
    if (build_bus(bus_struct,k,&dist,&dur) == FAILED_READ_BUSES)
    {
        free(bus_struct);
        return EXIT_FAILURE;
    }
    if(strcmp("test",argv[ONE]) != FAILED_COMPARE)
    {
        sort(bus_struct,bus_struct+ n - 1,argv[ONE]);
        print_arr(bus_struct,k - 1);
    }
    else
    {
        if(test_case(bus_struct,bus_struct + k - 1,k) != GOOD_CHECK)
        {
            free(bus_struct);
            return EXIT_FAILURE;
        }

    }
    free(bus_struct);
    return EXIT_SUCCESS;
}



