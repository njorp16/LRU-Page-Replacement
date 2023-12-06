#ifndef PAGETABE_H
#define PAGETABLE_H

#define PAGE_TABLE_SIZE 32

typedef struct {
   int frame_num;
   int valid;
   int referenced;
   int last_used;
}PageTableEntry;

typedef struct {
   PageTableEntry entries[PAGE_TABLE_SIZE];
}PageTable;

void init_page_table(PageTable *pt);

#endif //PAGETABLE_H
