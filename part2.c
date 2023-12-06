#include <stdio.h>
#include <stdlib.h>
#include "pagetable.h"

#define PAGE_TABLE_SIZE 32
//nextFreeFrame = 1
//each time need a new frame, return nextFreeFrame++
//do a check to see if there are free frames available (we have 8, 0-7)

//getNextFrame function - returns either a frame number, or sentinal value indicating that there are no more free frames
//function caller looks at returned value, and if it is that sentinal value, then we know to implement LRU
//for a physical address, the high 5 bits are the page number, and the low 7 bits are the offset

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <infile> <outfile>\n", argv[0]);
        return 1;
    }

    FILE *infile = fopen(argv[1], "rb");
    if (infile == NULL) {
        perror("Error opening input file");
        return 2;
    }

    FILE *outfile = fopen(argv[2], "wb");
    if (outfile == NULL) {
        perror("Error opening output file");
        fclose(infile);
        return 3;
    }

   //Counter Variable that represents free frames
   int freeFrames=1;
   int time_counter = 0;
   int MAX_FRAMES = 8;
   int pageFaults = 0;
   //initialize page table
   PageTable pt;
   init_page_table(&pt);

   unsigned long long address, physicalAddress;
   while (fread(&address, sizeof(address), 1, infile) == 1) {
        //Page Number and Offset
        unsigned int pageNum = address >> 7;
        unsigned int offset = address & 0x7F;
        
        //Update last_used field for LRU tracking
        pt.entries[pageNum].last_used = time_counter++;

        //Checking if page table entry is valid
        if (!pt.entries[pageNum].valid) {
            pageFaults++;
            printf("Page fault at address: %016llx (Page Number: %u)\n", address, pageNum);
           //Handle Page Fault
           if (freeFrames < MAX_FRAMES) {
              //Assign new frame
              unsigned int frameNum = pt.entries[pageNum].frame_num = freeFrames++;
              
           } else {
             //Use LRU Page Replacement(function call)
             int lru_page = find_lru_page(&pt);
             //Invalidate the LRU page
             pt.entries[lru_page].valid = 0;
             //Reuse frame of the LRU page for the new page
             pt.entries[pageNum].frame_num = pt.entries[lru_page].frame_num;

           }

           

           //Set page table entry for the new page
           pt.entries[pageNum].valid = 1;
           //pt.entries[pageNum].last_used = time_counter;
           pt.entries[pageNum].referenced = 1;
        }

        //Physical Address Translation
        unsigned int frameNum = pt.entries[pageNum].frame_num;
        physicalAddress = ((unsigned long long)frameNum << 7 | offset);
        printf("%016llx -> %016llx\n", address, physicalAddress);
        fwrite(&physicalAddress, sizeof(physicalAddress), 1, outfile);
    }


    fclose(infile);
    fclose(outfile);
    printf("Translation completed successfully.\n");
    printf("Total page faults: %d\n", pageFaults);

    
    return 0;
}
