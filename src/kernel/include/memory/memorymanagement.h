#ifndef OS__KERNEL_MEMORY_MANAGEMENT_H
#define OS__KERNEL_MEMORY_MANAGEMENT_H

#include "../common/type.h"
#include "../common/string.h"
#include "../io/terminal.h"



namespace OS { namespace KERNEL { namespace MEMORY {

     
    typedef struct MemoryChunk
    {
        MemoryChunk *next;
        MemoryChunk *prev;
        bool allocated;
        size_t size;
    } memory_chunk_t;

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
    
    };
}}}

void* malloc(size_t size);
void free(void* ptr);
void* operator new(size_t size);
void* operator new[](size_t size);

void operator delete(void* ptr);
void operator delete[](void* ptr);
void operator delete(void* ptr, unsigned long size);

#endif