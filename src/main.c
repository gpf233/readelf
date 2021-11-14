#include "func.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

FILE *elfptr;
Elf64_Ehdr ehdr;
Elf64_Shdr *shdrptr;
Elf64_Phdr *phdrptr;

int main(int argc, char** argv) {
    // check arg
    if (argc != 3) {
        perror("argc error");
        exit(1);
    }
    // open elf file
    if ((elfptr = fopen(argv[2], "r")) == NULL) {
        perror("fopen error");
        exit(1);
    }
    // fill elf header
    fread(&ehdr, sizeof(ehdr), 1, elfptr);
    // fill section headers
    fseek(elfptr, ehdr.e_shoff, SEEK_SET);
    if ((shdrptr = malloc(ehdr.e_shentsize * ehdr.e_shnum)) == NULL) {
        perror("malloc error");
        exit(1);
    }
    fread(shdrptr, ehdr.e_shentsize, ehdr.e_shnum, elfptr);
    // fill program headers
    fseek(elfptr, ehdr.e_phoff, SEEK_SET);
    if ((phdrptr = malloc(ehdr.e_phentsize * ehdr.e_phnum)) == NULL) {
        perror("malloc error");
        exit(1);
    }
    fread(phdrptr, ehdr.e_phentsize, ehdr.e_phnum, elfptr);
    // parse
    if (strcmp(argv[1], "-h") == 0) {
        e();
    } else if (strcmp(argv[1], "-S") == 0) {
        s();
    } else if (strcmp(argv[1], "-l") == 0) {
        p();
    }
    // free
    fclose(elfptr);
    free(shdrptr);
    free(phdrptr);
    elfptr = NULL;
    return 0;
}
