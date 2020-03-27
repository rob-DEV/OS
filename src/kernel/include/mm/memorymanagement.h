
#ifndef OS__KERNEL_MEMORY_MANAGEMENT_H
#define OS__KERNEL_MEMORY_MANAGEMENT_H

#include "../com/type.h"
#include "../com/string.h"
#include "../io/terminal.h"

#define MEMORY_CHUNK_MAGIC 0x1337

#define MEMORY_DEBUG 0
#define ZERO_DEALLOC_MEMORY 0


namespace OS { namespace KERNEL { namespace MEMORY {

     
    typedef struct MemoryChunk
    {
        uint16_t magic;
        MemoryChunk *next;
        MemoryChunk *prev;
        bool allocated;
        size_t size;
    } memory_chunk_t;

    void printMemChunk(memory_chunk_t* memChunk);

    class MemoryManager {
    public:
        
        size_t m_HeapStart;
        size_t m_HeapEnd;
        size_t m_SizeBytes;

        MemoryChunk* first;

    public:
        static MemoryManager* Instance;

        MemoryManager(size_t first, size_t size);
        ~MemoryManager();

        bool terminalInstanceAllocated = false;

        void* malloc(size_t size);
        void free(void* ptr);

        void printInfo();
    
    };
}}}

void* malloc(size_t size);
void free(void* ptr);
void* operator new(size_t size);
void* operator new[](size_t size);

void operator delete(void* ptr);
void operator delete[](void* ptr);
//void operator delete(void* ptr, unsigned long size);

#endif