#include "tests.h"
#include <string.h>

#define K_3 3
#define K_2 2
#define MINUS_K (-1)
#define MINUS_3K (-3)
#define K_29 29


// See full documentation in header file
int test_encode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc";
  char out[] = "def";
  encode (in, K_3);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_encode_cyclic_lower_case_special_char_positive_k ()
{
    char in[] = "x!y!z";
    char out[] = "z!a!b";
    encode (in, K_2);
    return strcmp (in, out) != 0;
  // your code goes here
}

// See full documentation in header file
int test_encode_non_cyclic_lower_case_special_char_negative_k ()
{
    char in[] = "c!d!e";
    char out[] = "b!c!d";
    encode (in, MINUS_K);
    return strcmp (in, out) != 0;
    // your code goes here
}

// See full documentation in header file
int test_encode_cyclic_lower_case_negative_k ()
{
    char in[] = "zab!";
    char out[] = "wxy!";
    encode (in, MINUS_3K);
    return strcmp (in, out) != 0;
    // your code goes here

  // your code goes here
}

// See full documentation in header file
int test_encode_cyclic_upper_case_positive_k ()
{
    char in[] = "ABC";
    char out[] = "DEF";
    encode (in, K_29);
    return strcmp (in, out) != 0;
  // your code goes here
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_positive_k ()
{
  char in[] = "def";
  char out[] = "abc";
  decode (in, K_3);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_cyclic_lower_case_special_char_positive_k ()
{
  // your code goes here

    char in[] = "a!b!c";
    char out[] = "y!z!a";
    decode (in, K_2);
    return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decode_non_cyclic_lower_case_special_char_negative_k ()
{
    char in[] = "a!!bc";
    char out[] = "b!!cd";
    decode (in, MINUS_K);
    return strcmp (in, out) != 0;
  // your code goes here
}

// See full documentation in header file
int test_decode_cyclic_lower_case_negative_k ()
{

    char in[] = "xyz";
    char out[] = "abc";
    decode (in, MINUS_3K);
    return strcmp (in, out) != 0;
  // your code goes here
}

// See full documentation in header file
int test_decode_cyclic_upper_case_positive_k ()
{

    char in[] = "XUZ";
    char out[] = "URW";
    decode (in, K_29);
    return strcmp (in, out) != 0;
  // your code goes here
}
