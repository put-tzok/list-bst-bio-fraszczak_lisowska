#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int ns[] = { 10000,20000,30000,40000,50000,60000,70000,80000,90000,100000 };

// each list node contains an integer key value and pointer to next list node
struct node {
    int key;
    struct node *next;
}n;

// list's beginning is called the head of list

struct node *head = NULL;

//////INSERT/////
struct node* list_insert(int value) {
struct node *ptr, *ptr_1;
    ptr_1=(struct node*)malloc(sizeof(struct node));
    ptr_1->next=NULL;
    ptr_1->key=value;
    ptr=head;
    if(ptr!=NULL){
        while(ptr->next){
            ptr=ptr->next;
        }
        ptr->next=ptr_1;
    }else{
        head=ptr_1;
    }

    return ptr_1;
}

///////SEARCH//////
struct node* list_search(int value) {
    struct node *iter;
    iter=(struct node*)malloc(sizeof(struct node));
    iter=head;
        while (iter !=NULL && iter->key != value){
            iter=iter->next;
        }

    return iter;
}

/////////DELETE////////
void list_delete(int value) {
    struct node *ptr,*ptr_1;
    ptr=(struct node*)malloc(sizeof(struct node));
    ptr_1=(struct node*)malloc(sizeof(struct node));
    ptr=head;

        if(ptr!=NULL){
            if(ptr->key==value){
                ptr=ptr->next;
                head=ptr;
            }else{
                ptr_1=head->next;

                while(ptr_1!=NULL&&ptr_1->key!=value){
                    ptr=ptr_1;
                    ptr_1=ptr_1->next;
                }

                if(ptr_1!=NULL){
                    ptr->next=ptr_1->next;
                }
            }
        }
}


///////LIST SIZE//////
unsigned int list_size() {
    int size=0;
    struct node *iter=head;

    while (iter!=NULL){
      size=size+1;
      iter=iter->next;
    }

    return size;
}

/*
 * Fill an array with increasing values.
 *
 * Parameters:
 *      int *t:     pointer to the array
 *      int n:      number of elements in the array
 */
void fill_increasing(int *t, int n) {
    for (int i = 0; i < n; i++) {
        t[i] = i;
    }
}

/*
 * Reorder array elements in a random way.
 *
 * Parameters:
 *      int *t:     pointer to the array
 *      int n:      number of elements in the array
 */
void shuffle(int *t, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % i;
        int temp = t[i];
        t[i] = t[j];
        t[j] = temp;
    }
}

int main() {
    bool no_yes[] = { false, true };

    for (unsigned int i = 0; i < sizeof(no_yes) / sizeof(*no_yes); i++) {
        bool enable_shuffle = no_yes[i];

        for (unsigned int j = 0; j < sizeof(ns) / sizeof(*ns); j++) {
            unsigned int n = ns[j];

            // always create an array of size `n` and fill it with increasing values
            int *t = malloc(n * sizeof(*t));
            fill_increasing(t, n);

            // if true, reorder array elements randomly
            if (enable_shuffle) {
                shuffle(t, n);
            }

            // insert elements in the order present in array `t`
            clock_t insertion_time = clock();
            for (unsigned int k = 0; k < n; k++) {

                struct node *iter = list_insert(t[k]);
                assert(iter != NULL);       // inserted element cannot be NULL
                assert(iter->key == t[k]);  // inserted element must contain the expected value
            }
            insertion_time = clock() - insertion_time;

            // reorder array elements before searching
            shuffle(t, n);

            // search for every element in the order present in array `t`
            clock_t search_time = clock();
            for (unsigned int k = 0; k < n; k++) {
                struct node *iter = list_search(t[k]);
                assert(iter != NULL);       // found element cannot be NULL
                assert(iter->key == t[k]);  // found element must contain the expected value
            }
            search_time = clock() - search_time;

            // reorder array elements before deletion
            shuffle(t, n);

            // delete every element in the order present in array `t`
            for (unsigned int k = 0, l = n; k < n; k++, l--) {
                assert(list_size() == l);   // list size must be equal to the expected value
                list_delete(t[k]);
            }
            assert(list_size() == 0);       // after all deletions, the list size is zero
            assert(head == NULL);           // after all deletions, the list's head is NULL

            free(t);

            printf("%d\t%s\t%f\t%f\n", n, enable_shuffle ? "true" : "false",
                    (double)insertion_time / CLOCKS_PER_SEC,
                    (double)search_time / CLOCKS_PER_SEC);
        }
    }
    return 0;
}
