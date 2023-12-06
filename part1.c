#include <stdio.h>
#include <stdlib.h>

/*Part 1: Address Translation*/
//- Integer array representing the page table (2, 4, 1, 7, 3, 5, 6)
//- Take a virtual address and break it into p and d, where p is the page number and d is the offest bits
//- Use p to locate the correct page table entry
//- The page table entry will contain a corresponding framew number
//- Load those frame bits into the most significant bits, right above the offest in the physical address soace
//- Note: 1K physical memory (10 bits), 4KB virtual memory (12 bits), 128 bytes per page (7 bit offset)
//- Page number from Virtual Address: pageNum = vaddr >> 7
//- Offset = vaddr & 0x7F

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

    int pTable[7] = {2, 4, 1, 7, 3, 5, 6};

    unsigned long long address, physicalAddress;
    while (fread(&address, sizeof(address), 1, infile) == 1) {

        //Page Number and Offset
        unsigned int pageNum = address >> 7;
        unsigned int offset = address & 0x7F;

        //Physical Address Translation
        unsigned int frameNum = pTable[pageNum];
        physicalAddress = ((unsigned long long)frameNum << 7 | offset);
        printf("Logical Address is: %016llx, Physical Address is: %016llx\n", address, physicalAddress);
        fwrite(&physicalAddress, sizeof(physicalAddress), 1, outfile);
    }

    fclose(infile);
    fclose(outfile);
    printf("Translation completed successfully.\n");
    return 0;
}


