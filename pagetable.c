#define PAGE_TABLE_SIZE 32

typedef struct {
    int frame_num;
    int valid;
    int referenced;
    int last_used;
    //int dirty;
}PageTableEntry;

typedef struct {
    PageTableEntry entries[PAGE_TABLE_SIZE];
}PageTable;

void init_page_table(PageTable *pt) {
    int i;
    for (i = 0; i < PAGE_TABLE_SIZE; i++) {
        pt->entries[i].frame_num = -1; // Indicates an invalid frame number
        pt->entries[i].valid = 0;         // Initially invalid
        pt->entries[i].referenced = 0;    // Not referenced
        pt->entries[i].last_used = 0;
        //pt->entries[i].dirty = 0;
    }
}
