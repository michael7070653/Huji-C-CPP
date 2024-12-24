#include "cipher.h"
#include "tests.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX_LINE 1025
#define MAX_ARG 5
#define MIN_ARG 2
#define BASE 10
int check_num_arg(int num_arg);
int check_valid_args(int num_arg, char **words);
int check_test_decode();
int check_test_encode();
int check_test();


//this function check if num of args is 4 or 1.
//this funk check number or argument
int check_num_arg(int num_arg)
{
    if (num_arg != MIN_ARG && num_arg != MAX_ARG)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}

int check_valid_args(int num_arg, char* words[])
{
    int check_number_of_arg = check_num_arg(num_arg);
    if (check_number_of_arg == 1)
    {
        fprintf(stderr,"The program receives 1 or 4 arguments only.\n");
        return EXIT_FAILURE;
    }
    if (num_arg == MIN_ARG && strcmp(words[1],"test") != 0)
    {
        fprintf(stderr,"Usage: cipher test\n");
        return EXIT_FAILURE;
    }
    else if(num_arg == MAX_ARG)
    {   //here I check uf the command is valid
        char* coma_arg = words[1];
        if (strcmp("decode",coma_arg) != 0 && strcmp("encode",coma_arg) != 0)
        {
            fprintf(stderr,"The given command is invalid.\n");
            return EXIT_FAILURE;
        }
        //here i check if k is valid
        char *end ;
        strtol(words[2],&end,BASE);
        if (*end != '\0' || words[2] == end) {
            // Conversion failed or no digits were found
            fprintf(stderr,"The given shift value is invalid.\n");
            return EXIT_FAILURE; // Exit with an error code
        }
        //check if all good now open file
        FILE *my_file = fopen(words[3],"r+");
        FILE *out_file = fopen(words[4],"w");
        if (my_file == NULL || out_file == NULL)
        {
            fprintf(stderr,"The given file is invalid.\n");
            return EXIT_FAILURE;
        }
        fclose(my_file);
        fclose(out_file);
        return EXIT_SUCCESS;
    }
    return EXIT_SUCCESS;
}






//here we test Encode
int check_test_encode()
{
    int res_test;
    res_test = test_encode_non_cyclic_lower_case_positive_k ();
    if (res_test !=0)
    {
        return EXIT_FAILURE;
    }
    res_test =test_encode_cyclic_lower_case_special_char_positive_k ();
    if (res_test != 0)
    {
        return EXIT_FAILURE;
    }
    res_test =test_encode_non_cyclic_lower_case_special_char_negative_k();
    if (res_test != 0)
    {
        return EXIT_FAILURE;
    }
    res_test = test_encode_cyclic_lower_case_negative_k();
    if (res_test != 0)
    {
        return EXIT_FAILURE;
    }
    res_test = test_encode_cyclic_upper_case_positive_k();
    if (res_test != 0)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;

}
//here we test Decode
int check_test_decode()
{
    int res_test;
    res_test = test_decode_non_cyclic_lower_case_positive_k ();
    if (res_test != 0)
    {
        return EXIT_FAILURE;
    }
    res_test = test_decode_cyclic_lower_case_special_char_positive_k ();
    if (res_test != 0)
    {
        return EXIT_FAILURE;
    }
    res_test = test_decode_non_cyclic_lower_case_special_char_negative_k ();
    if (res_test != 0)
    {
        return EXIT_FAILURE;
    }
    res_test = test_decode_cyclic_lower_case_negative_k ();
    if (res_test != 0)
    {
        return EXIT_FAILURE;
    }
    res_test = test_decode_cyclic_upper_case_positive_k ();
    if (res_test != 0)
    {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


int check_test()
{
    int res_test_encode = check_test_encode();
    int res_test_decode = check_test_decode();
    if (res_test_decode == EXIT_SUCCESS && res_test_encode == EXIT_SUCCESS)
    {
        return EXIT_SUCCESS;
    }
    return EXIT_FAILURE;
}





int main (int argc, char *argv[])
{   // here I check the valid args/
    int check_arg = check_valid_args(argc, argv);
    char words[MAX_LINE] ={0};//write in the new file
    if (check_arg == 0)
    {
        if (argc == MAX_ARG)
        {
        char *end;
        long k = strtol(argv[2],&end,BASE);// k-> to int
        int num_k = (int) k;// k-> to int
        FILE *my_file = fopen(argv[3],"r"); // file to read
        FILE *out_file = fopen(argv[4], "w"); // file to write
            //loop until file end

        while (fgets(words,MAX_LINE,my_file))
        {
            if (strcmp(argv[1],"encode") == 0)
            {
                encode(words,num_k);
                fputs(words, out_file);
            }
            else
            {
                decode(words,num_k);
                fputs(words, out_file);
            }
        }
        fclose(my_file);
        fclose(out_file);
        return EXIT_SUCCESS;
        }
        else
            //here i do test if arg v ="test"
        {
            int res = check_test();//check tests
            if (res == 0)
            {
                return EXIT_SUCCESS;
            }
        }

    }
    return EXIT_FAILURE;
}
