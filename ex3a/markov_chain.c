
#include "markov_chain.h"
#include "linked_list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SAME_DATA 0
#define DATA_IN_DATABASE 0
#define DATA_NOT_IN_DATABASE 1
#define ALLOCATE_IN_LIST_FAIL 1
#define MEMORY_ALLOCATION_FAIL NULL
#define IN_FREQ_LIST 0
#define NOT_IN_FREQ_LIST 1
#define FREQ_ARR_SIZE  sizeof(MarkovNodeFrequency)
#define EMPTY_ARR 0
#define FAIL_STR_ALLOCATE "Allocation failure: exit program"


///function call//


int check_in_freq_list(MarkovNodeFrequency *point_to_freq_list,
                       int size, char *data);



///Get random number between 0 and max_number [0, max_number).
 ///param max_number maximal number
 /// to return (not including)///@return Random number
///
int get_random_number(int max_number)
{
    return rand() % max_number;
}




/**
* Check if data_ptr is in database. If so
 * , return the markov_node wrapping it in
 * the markov_chain, otherwise return NULL.
 * @param markov_chain the chain to look in its database
 * @param data_ptr the state to look for
 * @return Pointer to the Node wrapping given state, NULL if state not in
 * database.
 */
Node* get_node_from_database(MarkovChain *markov_chain, char *data_ptr)
{

    Node *head = markov_chain->database->first;
    while (head!= NULL)
    {
        if (strcmp(head->data->data, data_ptr) == SAME_DATA)
        {
            return head;
        }
        head = head->next;
    }
    return NULL;
}










/// in this function i add Node to markov chain database

Node* add_to_database(MarkovChain *markov_chain, char *data_ptr)
{
    ///check if node is already in database
    Node *head = get_node_from_database(markov_chain, data_ptr);
    if (head != NULL)
    {
        return head;
    }

    ///create new markov node
    MarkovNode *new_markov = malloc(sizeof(MarkovNode));
    if(!new_markov)
    {
        fprintf(stdout,"%s", FAIL_STR_ALLOCATE);
        return NULL;
    }
    char *new_alloc_word = malloc(strlen(data_ptr) +  1);
    if (!new_alloc_word)
    {
        fprintf(stdout,"%s", FAIL_STR_ALLOCATE);
        free(new_markov);
        return NULL;
    }

    memcpy(new_alloc_word,data_ptr,strlen(data_ptr)+1);
    *new_markov = (MarkovNode) {new_alloc_word,
                                NULL,0,
                                0};

    int check_add_to_database = add(markov_chain->database,
                                    new_markov);
    if(!check_add_to_database)
    {
        return markov_chain->database->last;
    }
    fprintf(stdout,"%s", FAIL_STR_ALLOCATE);
    free(new_markov->data);
    free(new_markov);///CHECK_VALGRIND OR SIGMANT FAULT
    return NULL;
}


/// HERE I CHECK IF NODE IS ALREADY IN FREQ LIST ,IF IN ADD 1.
int check_in_freq_list(MarkovNodeFrequency *point_to_freq_list,
                       int size, char *data)
{
    for(int i = 0; i < size; i++)
    {
        if(strcmp((point_to_freq_list + i)
        ->markov_node->data, data) == SAME_DATA)
        {
            /// NODE is already in freq_list and we add 1.
            (point_to_freq_list + i)->frequency++;
            return IN_FREQ_LIST;
        }
    }
    return NOT_IN_FREQ_LIST;
}




void put_second_node_in_first(MarkovNode *first_node,
                              MarkovNode *second_node,
                              MarkovNodeFrequency *temp_reallocate)
{
    first_node->frequencies_list = temp_reallocate;
    (first_node->frequencies_list + first_node->size_arr)
    ->markov_node = second_node;
    (first_node->frequencies_list + first_node->size_arr)
    ->frequency = 1;
    first_node->num_words_after ++;
    first_node->size_arr ++;
}


///allocate new place in freq list of node 1
bool allocate(MarkovNode *first_node, MarkovNode *second_node)
{

    MarkovNodeFrequency *temp_reallocate =
            realloc(first_node->frequencies_list,
                    (first_node->size_arr + 1) * FREQ_ARR_SIZE);

    if (temp_reallocate == MEMORY_ALLOCATION_FAIL)
    {
        fprintf(stdout,"%s", FAIL_STR_ALLOCATE);
        return false;
    }
    put_second_node_in_first(first_node,second_node,temp_reallocate);
    return true;
}




/**
 * Add the second markov_node to the counter list of the first markov_node.
 * If already in list, update it's counter value.
 * @param first_node
 * @param second_node
 * @return success/failure: true if the process was successful, false if in
 * case of allocation error.
 */


bool add_node_to_counter_list(MarkovNode *first_node,
                              MarkovNode *second_node)
{
    char* second_node_data = second_node->data;
    int check_list = check_in_freq_list(
        first_node->frequencies_list,
                                   first_node->size_arr,
                                   second_node_data);
    if (check_list == IN_FREQ_LIST)
    {
        first_node->num_words_after ++;
        return true;
    }
    bool reallocate = allocate(first_node, second_node);
    if(reallocate == true)
    {
        return true;
    }
    return false;
}



void free_markov_node(Node *head)
{
    if(head->data->size_arr !=0)
    {
        free(head->data->frequencies_list);
    }
    free(head->data->data);
    free(head->data);
    free(head);
}



/**
 * Free markov_chain and all of it's content from memory
 * @param markov_chain markov_chain to free
 */
void free_markov_chain(MarkovChain ** ptr_chain)
{   if (!*ptr_chain)
    {
        return;
    }
    int size_list = (*ptr_chain)->database->size;
    Node *head = (*ptr_chain)->database->first;
    for (int i = 0; i < size_list; i++)
    {
        Node *temp = head->next;
        free_markov_node(head);
        head = temp;
    }
    head = NULL;
    free((*ptr_chain)->database);
    free(*ptr_chain);
    (*ptr_chain) = NULL;
}















int is_ends_with_period(const char *word)
{
    size_t length = strlen(word);

    // Check if the last character is a period
    if (length > 0 && word[length - 1] == '.') {
        return 1;  // True, the data ends with a period
    } else {
        return 0;  // False, the data does not end with a period
    }
}






/**
 * Get one random state from the given markov_chain's database.
 * @param markov_chain
 * @return
 */



MarkovNode* get_first_random_node(MarkovChain *markov_chain)
{
    int size = markov_chain->database->size;
    while (true)
    {
        Node *rand = markov_chain->database->first;
        int res = get_random_number(size);
        for(int i = 0; i < res;i++ )
        {
            rand = rand->next;
        }
        if(!is_ends_with_period(rand->data->data))
        {
            return rand->data;
        }
    }
}









/**
 * Choose randomly the next state, depend on it's occurrence frequency.
 * @param state_struct_ptr MarkovNode to choose from
 * @return MarkovNode of the chosen state
 */
MarkovNode* get_next_random_node(MarkovNode *state_struct_ptr)
{
    int next_rand = get_random_number(state_struct_ptr
        ->num_words_after);
    MarkovNodeFrequency *freq_list = state_struct_ptr->frequencies_list;
    int i = freq_list->frequency;

    while (i <= next_rand)
    {
        freq_list ++;
        i += freq_list->frequency;
    }
    return freq_list->markov_node;


}








/**
 * Receive markov_chain, generate and print random sentence out of it. The
 * sentence most have at least 2 words in it.
 * @param markov_chain
 * @param first_node markov_node to start with,
 *                   if NULL- choose a random markov_node
 * @param  max_length maximum length of chain to generate
 */


void generate_random_sequence(MarkovChain *markov_chain,
                              MarkovNode *first_node, int max_length)
{
    if (first_node == NULL)
    {
        first_node = get_first_random_node(markov_chain);
    }

    int x = 0;
    while (!is_ends_with_period(first_node->data) && x < max_length)
    {
        fprintf(stdout,"%s ",first_node->data);
        first_node = get_next_random_node(first_node);
        x++;
    }
    fprintf(stdout,"%s",first_node->data);
}









