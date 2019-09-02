#ifndef OS__KERNEL_MULTIBOOT_H
#define OS__KERNEL_MULTIBOOT_H

#include "type.h"

#define MULTIBOOT_SEARCH                      8192 // How many bytes from the start of the file we search for the header.
#define MULTIBOOT_HEADER_MAGIC          0x1BADB002 // The magic field should contain this.
#define MULTIBOOT_BOOTLOADER_MAGIC      0x2BADB002 // This should be in %eax.
#define MULTIBOOT_UNSUPPORTED           0x0000fffc // The bits in the required part of flags field we don't support.
#define MULTIBOOT_MOD_ALIGN             0x00001000 // Alignment of multiboot modules.
#define MULTIBOOT_INFO_ALIGN            0x00000004 // Alignment of the multiboot info structure.

// Flags set in the 'flags' member of the multiboot header.
#define MULTIBOOT_PAGE_ALIGN            0x00000001 // Align all boot modules on i386 page (4KB) boundaries.
#define MULTIBOOT_MEMORY_INFO           0x00000002 // Must pass memory information to OS.
#define MULTIBOOT_VIDEO_MODE            0x00000004 // Must pass video information to OS.
#define MULTIBOOT_AOUT_KLUDGE           0x00010000 // This flag indicates the use of the address fields in the header.

// Flags to be set in the 'flags' member of the multiboot info structure.
#define MULTIBOOT_INFO_MEMORY           0x00000001 // Is there basic lower/upper memory information?
#define MULTIBOOT_INFO_BOOTDEV          0x00000002 // Is there a boot device set?
#define MULTIBOOT_INFO_CMDLINE          0x00000004 // Is the command-line defined?
#define MULTIBOOT_INFO_MODS             0x00000008 // Are there modules to do something with?

// These next two are mutually exclusive
#define MULTIBOOT_INFO_AOUT_SYMS        0x00000010 // Is there a symbol table loaded?
#define MULTIBOOT_INFO_ELF_SHDR         0X00000020 // Is there an ELF section header table?

#define MULTIBOOT_INFO_MEM_MAP          0x00000040 // Is there a full memory map?
#define MULTIBOOT_INFO_DRIVE_INFO       0x00000080 // Is there drive info?
#define MULTIBOOT_INFO_CONFIG_TABLE     0x00000100 // Is there a config table?
#define MULTIBOOT_INFO_BOOT_LOADER_NAME 0x00000200 // Is there a boot loader name?
#define MULTIBOOT_INFO_APM_TABLE        0x00000400 // Is there a APM table?
#define MULTIBOOT_INFO_VIDEO_INFO 0x00000800 // Is there video information?

typedef unsigned short          multiboot_uint16_t;
typedef unsigned int            multiboot_uint32_t;
typedef unsigned long long multiboot_uint64_t;

typedef struct multiboot_aout_symbol_table {
    multiboot_uint32_t tabsize;
    multiboot_uint32_t strsize;
    multiboot_uint32_t addr;
    multiboot_uint32_t reserved;
} multiboot_aout_symbol_table_t;

typedef struct multiboot_elf_section_header_table {
    multiboot_uint32_t num;
    multiboot_uint32_t size;
    multiboot_uint32_t addr;
    multiboot_uint32_t shndx;
} multiboot_elf_section_header_table_t;

typedef struct multiboot_info {
    // Multiboot info version number
    multiboot_uint32_t flags;

    // Available memory from BIOS
    multiboot_uint32_t mem_lower;
    multiboot_uint32_t mem_upper;

    // "root" partition
    multiboot_uint32_t boot_device;

    // Kernel command line
    multiboot_uint32_t cmdline;

    // Boot-Module list
    multiboot_uint32_t mods_count;
    multiboot_uint32_t mods_addr;

    union
    {
        multiboot_aout_symbol_table_t aout_sym;
        multiboot_elf_section_header_table_t elf_sec;
    } u;

    // Memory Mapping buffer
    multiboot_uint32_t mmap_length;
    multiboot_uint32_t mmap_addr;

    // Drive Info buffer
    multiboot_uint32_t drives_length;
    multiboot_uint32_t drives_addr;

    // ROM configuration table
    multiboot_uint32_t config_table;

    // Boot Loader Name
    multiboot_uint32_t boot_loader_name;

    // APM table
    multiboot_uint32_t apm_table;

    // Video
    multiboot_uint32_t vbe_control_info;
    multiboot_uint32_t vbe_mode_info;
    multiboot_uint16_t vbe_mode;
    multiboot_uint16_t vbe_interface_seg;
    multiboot_uint16_t vbe_interface_off;
    multiboot_uint16_t vbe_interface_len;
} multiboot_info_t;

typedef struct multiboot_mmap_entry
{
    multiboot_uint32_t size;
    multiboot_uint64_t addr;
    multiboot_uint64_t len;
#define MULTIBOOT_MEMORY_AVAILABLE              1
#define MULTIBOOT_MEMORY_RESERVED               2
    multiboot_uint32_t type;
} __attribute__((packed)) multiboot_memory_map_t;

typedef struct multiboot_mod_list
{
    // the memory used goes from bytes 'mod_start' to 'mod_end-1' inclusive
    multiboot_uint32_t mod_start;
    multiboot_uint32_t mod_end;

    // Module command line
    multiboot_uint32_t cmdline;

    // padding to take it to 16 bytes (must be zero)
    multiboot_uint32_t pad;
} multiboot_module_t;

void parse_multiboot_info(uint32_t magic, multiboot_info_t* mbi);


#endif //OS__KERNEL_MULTIBOOT_H