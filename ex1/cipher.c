#include "cipher.h"

#include <ctype.h>

#define NUM_LETTER 26
#define END_BIG_LETTER 90
#define START_BIG_LETTER 64

/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.




int set_k(int k);

char encode_helper(char s[], int i , int k);


// set k to the right value

//funk mode 26
int set_k(int k)
{
    int x = k;
    if (x > NUM_LETTER)
    {
        while (x > NUM_LETTER)
        {
            x = x - NUM_LETTER;
        }
    }
    else if( x < 0 )
    {
        while (x < 0)
        {
            x = x + NUM_LETTER ;
        }
    }

    return x;

}







char encode_helper(char s[], int i , int k)

{

    int new_k = set_k(k);
    if (s[i] + new_k <= END_BIG_LETTER)
    {
        return s[i] + new_k;
    }
    else
    {
        return (s[i] + new_k) % END_BIG_LETTER + START_BIG_LETTER;
    }

}







void encode (char s[], int k)
{
    // find size of s
    int size = 0;
    //in this part I make the Encode
    while (s[size] != '\0')
    {
        if (islower(s[size]))
            //if (s[size]>= 97 && s[size] <=122)
        {
            s[size] = toupper(s[size]);
            s[size] = encode_helper(s, size, k);
            s[size] = tolower(s[size]);
        }
        else if (isupper(s[size]))
        {
            s[size] = encode_helper(s,size, k);
        }
        size++;

    }

}

// See full documentation in header file
void decode (char s[], int k)
{
    encode(s, -k);
}


