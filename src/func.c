#include "func.h"

#include <stdio.h>

extern FILE *elfptr;
extern Elf64_Ehdr ehdr;
extern Elf64_Shdr *shdrptr;
extern Elf64_Phdr *phdrptr;

void e() {
    printf("ELF Header:\n");
    // Magic
    printf("  %-9s", "Magic:");
    for (uint8_t i = 0u; i < 0x10u; i++) {
        printf("%02x ", ehdr.e_ident[i]);
    }
    printf("\n");
    // Class
    printf("  %-35s", "Class:");
    for (int i = 1; i < 4; i++) {
        printf("%c", ehdr.e_ident[i]);
    }
    switch (ehdr.e_ident[4]) {
    case 0x00:
        printf("Invalid class");
        break;
    case 0x01:
        printf("32");
        break;
    case 0x02:
        printf("64");
        break;
    default:
        printf("error");
        break;
    }
    printf("\n");
    // Data
    printf("  %-35s", "Data:");
    printf("2's complement, ");
    switch (ehdr.e_ident[5]) {
    case 0x00:
        printf("Invalid data encoding");
        break;
    case 0x01:
        printf("little endian");
        break;
    case 0x02:
        printf("big endian");
        break;
    default:
        printf("error");
        break;
    }
    printf("\n");
    // Version
    printf("  %-35s", "Version:");
    printf("%d (current)\n", ehdr.e_ident[6]);
    // OS/ABI
    printf("  %-35s", "OS/ABI:");
    // TODO
    printf("\n");
    // ABI Version:
    printf("  %-35s", "ABI Version:");
    // TODO
    printf("\n");
    // Type
    printf("  %-35s", "Type:");
    switch (ehdr.e_type)
    {
    case 0x0000:
        printf("No file type");
        break;
    case 0x0001:
        printf("Relocatable file");
        break;
    case 0x0002:
        printf("Executable file");
        break;
    case 0x0003:
        printf("Shared object file");
        break;
    case 0x0004:
        printf("Core file");
        break;
    default:
        printf("error");
        break;
    }
    printf("\n");
    // Machine
    printf("  %-35s", "Machine:");
    printf("\n");
    // Version:
    printf("  %-35s", "Version:");
    printf("%#x", ehdr.e_version);
    printf("\n");
    // Entry point address
    printf("  %-35s", "Entry point address:");
    printf("%#lx", ehdr.e_entry);
    printf("\n");
    // Start of program headers
    printf("  %-35s", "Start of program headers:");
    printf("%lu (bytes into file)", ehdr.e_phoff);
    printf("\n");
    // Start of section headers
    printf("  %-35s", "Start of section headers:");
    printf("%lu (bytes into file)", ehdr.e_shoff);
    printf("\n");
    // Flags
    printf("  %-35s", "Flags:");
    printf("%#x", ehdr.e_flags);
    printf("\n");
    // Size of this header
    printf("  %-35s", "Size of this header:");
    printf("%hu (bytes)", ehdr.e_ehsize);
    printf("\n");
    // Size of program headers
    printf("  %-35s", "Size of program headers:");
    printf("%hu (bytes)", ehdr.e_phentsize);
    printf("\n");
    // Number of program headers
    printf("  %-35s", "Number of program headers:");
    printf("%hu", ehdr.e_phnum);
    printf("\n");
    // Size of section headers
    printf("  %-35s", "Size of section headers:");
    printf("%hu (bytes)", ehdr.e_shentsize);
    printf("\n");
    // Number of section headers
    printf("  %-35s", "Number of section headers:");
    printf("%hu", ehdr.e_shnum);
    printf("\n");
    // Section header string table index
    printf("  %-35s", "Section header string table index:");
    printf("%hu", ehdr.e_shstrndx);
    printf("\n");
}

void s() {
    printf("There are %d section headers, starting at offset %#lx:", ehdr.e_shnum, ehdr.e_shoff);
    printf("\n");
    printf("\n");
    printf("Section Headers:");
    printf("\n");
    printf("  [Nr] ");
    printf("%-17.17s %-16.16s %-16.16s  %-8.8s\n", "Name", "Type", "Address", "Offset");
    printf("       ");
    printf("%-16.16s  %-16.16s %-5.5s  %-4.4s  %-4.4s  %-5.5s\n", "Size", "EntSize", "Flags", "Link", "Info", "Align");
    char buffer[1024];
    for (int i = 0; i < ehdr.e_shnum; i++) {
        fseek(elfptr, shdrptr[ehdr.e_shstrndx].sh_offset + shdrptr[i].sh_name, SEEK_SET);
        fscanf(elfptr, "%s", buffer);
        printf("  [%2d] ", i);
        printf("%-17.17s %-16d %016lx  %08lx\n", buffer, shdrptr[i].sh_type, shdrptr[i].sh_addr, shdrptr[i].sh_offset);
        printf("       ");
        printf("%016lx  %016lx %-5lu  %4u  %4u     %-lu\n", shdrptr[i].sh_size, shdrptr[i].sh_entsize, shdrptr[i].sh_flags, shdrptr[i].sh_link, shdrptr[i].sh_info, shdrptr[i].sh_addralign);
    }
    // info
    printf("Key to Flags:\n\
  W (write), A (alloc), X (execute), M (merge), S (strings), I (info),\n\
  L (link order), O (extra OS processing required), G (group), T (TLS),\n\
  C (compressed), x (unknown), o (OS specific), E (exclude),\n\
  l (large), p (processor specific)\n");
}

void p() {
    printf("\n");
    printf("Elf file type is %hu\n", ehdr.e_type);
    printf("Entry point %#lx\n", ehdr.e_entry);
    printf("There are %hu program headers, starting at offset %lu\n", ehdr.e_phnum, ehdr.e_phoff);
    printf("\n");
    printf("Program Headers:\n");
    printf("  ");
    printf("%-14.14s %-18.18s %-18.18s %-18.18s\n", "Type", "Offset", "VirtAddr", "PhysAddr");
    printf("  ");
    printf("%-14.14s %-18.18s %-18.18s  %-5.5s  %-5.5s\n", "", "FileSiz", "MemSiz", "Flags", "Align");
    for (int i = 0; i < ehdr.e_phnum; i++) {
        printf("  ");
        printf("%-14d %#018lx %#018lx %#018lx\n", phdrptr[i].p_type, phdrptr[i].p_offset, phdrptr[i].p_vaddr, phdrptr[i].p_paddr);
        printf("  ");
        printf("%-14.14s %#018lx %#018lx  %-5d  %#lx\n", "", phdrptr[i].p_filesz, phdrptr[i].p_memsz, phdrptr[i].p_flags, phdrptr[i].p_align);
    }
}
