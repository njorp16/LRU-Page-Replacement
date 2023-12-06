#include <stdio.h>
#include <limits.h>
#include "pagetable.h"
#define PAGE_TABLE_SIZE 32

int find_lru_page(PageTable *pt) {
    int lru_index = -1;
    int min_time = INT_MAX;
    int i;
    for (i=0; i<PAGE_TABLE_SIZE; i++) {
        if (pt->entries[i].valid && pt->entries[i].last_used < min_time) {
           min_time = pt->entries[i].last_used;
           lru_index = i;
        }
    }

    return lru_index;




}
