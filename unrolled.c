#include <string.h>
#include <stdio.h>
#include <pthread.h>

#include "unrolled.h"

int total_size = 0;

// linked list data structure contains array of size N
struct unrolled_ll
{
    struct unrolled_ll * next;
    struct unrolled_ll * prev;

    // array of size N but what type -> going with size_t *
    size_t n;
    size_t ** array;

};


// remove element from unrolled linked list at i value
// i = position in the list
// if node no longer has elements -> node removed + prev node should link to next value
void * unrolled_ll_remove(struct unrolled_ll * list, size_t i)
{
    // printf("entering remove\n");
    // Error case : If the value i is outside of the range of contents in the list, this function should return NULL.
    if (list == NULL || i > total_size){printf("error occurred in remove\n");return NULL;}
   
    // mutex to ensure only 1 thread mod
    pthread_mutex_t new_mutex;
    pthread_mutex_lock(&new_mutex);

    int k, legit_number = 0;
    if(list->next == NULL)
    {
        // search list
        // printf("searching array\n");
        int array_length = list->n;
        for (int s = 0; s < array_length; s++)
        {
            // compare if equal -> remove
            if (legit_number == i && (list->array[s] != NULL))
            {
                // removed
                list->array[s] = NULL;
                // printf("removed\n");
                break;
            }
            // checking for jagged placing 
            if (list->array[s] != NULL){legit_number++;}
        }

        //check if empty
        int is_empty = 1;
        for (int s = 0; s < array_length; s++)
        {if (list->array[s] != NULL){is_empty++;}}

        if (is_empty == 1)
        {
            // printf("list is now empty\n");
            if(list->prev == NULL){
                // first note
                list->next->prev = NULL;
            }else{
                list->prev->next = list->next;
                list->next->prev = list->prev;
                total_size = total_size - list->n;
                // total size update ??
            }
          
        }
    }

    while (list->next != NULL)
    {
        k += list->n;
        // printf("searching array when not null next element\n");

        // won't exist
        if (k < i){}

        else
        {
            // search list
            int array_length = list->n;
            for (int s = 0; s < array_length; s++)
            {
                // compare if equal -> remove
                if ((legit_number == i) && (list->array[s] != NULL))
                {
                    // removed
                    list->array[s] = NULL;
                    // printf("removed\n");
                    break;
                }
                if (list->array[s] != NULL){ legit_number++; }
            }

            //check if empty
            int is_empty = 1;
            for(int s = 0; s< array_length; s++){
                if(list->array[s] != NULL){is_empty++;}
            }

            if(is_empty == 1)
            {
                // printf("list has been made empty; ptrs updated to reflect\n");
                if (list->prev == NULL)
                {
                    // first note
                    list->next->prev = NULL;
                    total_size = total_size - list->n;
                    // pthread_mutex_unlock(&new_mutex);
                    break;
                }
                else
                {
                    list->prev->next = list->next;
                    list->next->prev = list->prev;
                    total_size = total_size - list->n;
                    // pthread_mutex_unlock(&new_mutex);
                    break;
                }
            }
        }
        list = list->next;
    }
    pthread_mutex_unlock(&new_mutex);
}


// retrieve element from the unrolled linked list -> use i
// i value == position it is in your list
void * unrolled_ll_get(struct unrolled_ll * list, size_t i)
{
    // Error case : If the value i is outside of the range of contents in the list -> return NULL.
    // printf("entering get\n");
    if (list == NULL || i > total_size){printf("something is wrong\n");return NULL;}

    int k, legit_number = 0;
    if(list->next == NULL)
    {
        // printf("next is null\n");
        k += list->n;

        // search list
        int array_length = list->n;
        for (int s = 0; s < array_length; s++)
        {
            // comparing
            // printf("legit num = %d, s = %d, i = %lu\n",legit_number, s, i);
            // printf("%d,", *(size_t *)list->array[s]);
            if (legit_number == i && (size_t *)list->array[s] != NULL)
            {
                // printf("found the value\n");
                return list->array[s];
            }
            // testing jagged array
            if (list->array[s] != NULL){legit_number++;}
            
        }
        
    }

    while(list->next != NULL)
    {
        k += list->n;

        //error situation
        if(k < i){}

        else{
            // search list
            // printf("searching array when next is not null\n");
            int array_length = list->n;
            for(int s = 0; s < array_length; s++)
            {
                // compare
                if ((legit_number == i) && (list->array[s] != NULL)){
                    // printf("found the value\n");
                    return list->array[s];
                }
                // how many elements are not null
                if(list->array[s] != NULL){legit_number++;}
            }
        }
        list = list->next;
    }

    // printf("element was not found\n");
    return NULL;

}

// adds an element to the end of the list if last node is at capacity -> 
// make new node + add the element to the list
void unrolled_ll_append(struct unrolled_ll *list, void * element)
{
    // printf("entering append\n");

    // mutex
    pthread_mutex_t new_mutex;
    pthread_mutex_lock(&new_mutex);

    // error
    if(list == NULL || element == NULL){printf("something is null\n");return;}

    if(list->next == NULL)
    {
        // printf("linked list sizes are same\n");
        // test if there is space in the linked_list
        for (int i = 0; i < list->n ; i++)
        {
            // makes everything null
            if(list->array == NULL){
                // printf("the array is null\n");
                list->array = malloc(sizeof(size_t)*list->n);
                for(int j = 0; j<list->n; j++){list->array[j] = NULL;}
            }
            
            // is null + can add a new element
            if (list->array[i] != NULL){
                // printf("somethings in this bloc = %d\n", *list->array[i]);

            }
            else{
                list->array[i] = (size_t *)element;
                break;
                // printf("added new block\n");
                // pthread_mutex_unlock(&new_mutex);
            }
               
            // testing if final element in section
            if ((list->array[list->n - 1] != NULL) && (i == list->n - 1))
            {
                // printf("filled up + creating new block\n");
                // make new node

                struct unrolled_ll * new_node = malloc(sizeof(struct unrolled_ll));
                new_node->array = malloc(sizeof(size_t) * list->n);
                new_node->array[0] = (size_t *)element;
                
                new_node->next = NULL;
                new_node->prev = list;

                new_node->n = list->n;
                total_size = total_size + list->n;

                list->next = new_node;
                // printf("created new block\n");
                pthread_mutex_unlock(&new_mutex);
                return;
            }
        }
    }

    while(list->next != NULL)
    {
        // iterate through until "equals" condition is met
        if(list->n < total_size){ list = list->next;}

        else if(list->n == total_size)
        {
            // printf("linked list sizes are same");
            // test if there is space in the linked_list
            for(int i = 0; i< list->n ; i++){
                // makes everything null
                if (list->array == NULL)
                {
                    // printf("the array is null\n");
                    list->array = malloc(sizeof(size_t) * list->n);
                    for (int j = 0; j < list->n; j++){list->array[j] = NULL;}
                }

                // is null + can add a new element
                if (list->array[i] != NULL)
                {
                    // printf("somethings in this bloc = %d\n", *list->array[i]);
                }
                else
                {
                    list->array[i] = (size_t *)element;
                    // printf("added new block\n");
                    break;
                    // pthread_mutex_unlock(&new_mutex);
                }
               
                // testing if final element in section
                if ((list->array[list->n - 1] != NULL) && (list->array[i] == list->array[list->n - 1]))
                {
                    // printf("filled up + creating new block\n");
                    // make new node

                    struct unrolled_ll * new_node;
                    new_node->array = malloc(sizeof(list->n) * sizeof(size_t));
                    new_node->array[0] = element;
                    new_node->n = list->n;
                    new_node->next = NULL;
                    total_size = total_size + list->n;

                    list->next = new_node;
                    // printf("created new block\n");
                    pthread_mutex_unlock(&new_mutex);
                    return;
                }

            }

            list = list->next;
        }

        else
        {
            // total size < n 
            // printf("error has occurred\n");
            pthread_mutex_unlock(&new_mutex);
            return;
        }

    }

    pthread_mutex_unlock(&new_mutex);
}

// dealloc memory
// make sure that unrolled linked list -> thread safe + performant
void unrolled_ll_destroy(struct unrolled_ll * list)
{
    // mutex
    pthread_mutex_t new_mutex;

    pthread_mutex_lock(&new_mutex);

    while(list->next != NULL){

        int node_total = list->n;
        for(int i = 0; i< node_total; i++){

            if(list->array[i] != NULL){
                // printf("freeing the integer array\n");
                // don't need to be freed according to spec
                // free(list->array[i]);
            }
            
        }
        free(list->array);
        list = list->next;
        free(list);
        // printf("successfully removed node\n");
    }

    pthread_mutex_unlock(&new_mutex);
}

// construct unrolled linked list ->  each node contains n elements
// should return a heap allocated unrolled linked list
struct unrolled_ll * unrolled_ll_new(size_t n)
{
    pthread_mutex_t new_mutex;
    pthread_mutex_lock(&new_mutex);

    // will have nothing in linked
    if(n == 0){printf("not valid init\n");return NULL;}

    //first node is created
    struct unrolled_ll * list = malloc(sizeof(struct unrolled_ll));
    list->next = NULL;
    list->prev = NULL;
    list->n = n;
    total_size = n;
    list->array = malloc(sizeof(size_t) * n);
    list->array = NULL;
    // printf("successfully made new list\n");

    pthread_mutex_unlock(&new_mutex);
    return list;
}

int main()
{
    // testcases 

    /* error  CHECK */
    // struct unrolled_ll * error_init;
    // error_init = unrolled_ll_new(0);
    // error_init = unrolled_ll_new(NULL);

    /* short sequence  SHORT + QUICK FUNCTIONALITY CHECK*/
    // struct unrolled_ll * new_list;
    // new_list = unrolled_ll_new(3);

    // int i = 1;int new_value = 9;int new_value2 = 10;

    // unrolled_ll_append(new_list, &i);
    // unrolled_ll_append(new_list, &new_value);
    // unrolled_ll_append(new_list, &new_value2);

    // unrolled_ll_get(new_list, 0); 
    // unrolled_ll_get(new_list, 1);
    // unrolled_ll_get(new_list, 2);

    // unrolled_ll_remove(new_list, 0);
    // unrolled_ll_remove(new_list, 1);
    // unrolled_ll_remove(new_list, 2);

    // unrolled_ll_destroy(new_list);

    // // long sequence
    // int long_seq = 1;
    // int long_seq2 = 8;
    // int long_seq3 = 9;
    // int long_seq4 = 10;

    return 0;

}