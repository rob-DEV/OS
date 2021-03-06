#include "../include/mm/memorymanagement.h"



namespace OS { namespace KERNEL { namespace MEMORY {


    void printMemChunk(memory_chunk_t* memChunk) {
 
        #if MEMORY_DEBUG
        
        OS::KERNEL::Terminal::getInstance()->printf("\nPrinting Memory Chunk at 0x%x\n", memChunk);
        OS::KERNEL::Terminal::getInstance()->printf("MAGIC: 0x%x\n", memChunk->magic);
        OS::KERNEL::Terminal::getInstance()->printf("Size: %d\n", memChunk->size);
        OS::KERNEL::Terminal::getInstance()->printf("Allocated: %d\n", memChunk->allocated);
        OS::KERNEL::Terminal::getInstance()->printf("Previous: 0x%x\n", memChunk->prev);
        OS::KERNEL::Terminal::getInstance()->printf("Next: 0x%x\n", memChunk->next);
            
        #endif

    }

    MemoryManager* MemoryManager::Instance = NULL;

    MemoryManager::MemoryManager(size_t memory_start, size_t memory_end){
        
        Instance = this;
        m_HeapStart = memory_start + sizeof(MemoryChunk);
        m_HeapEnd = memory_end;

        m_SizeBytes = m_HeapEnd - m_HeapStart;
    
        if(m_SizeBytes < sizeof(MemoryChunk))
        {
            first = 0;
        }
        else
        {
            first = (MemoryChunk*)memory_start;
            
            first -> allocated = false;
            first -> prev = NULL;
            first -> next = NULL;
            first -> size = m_SizeBytes - sizeof(MemoryChunk);
        }
    }
    MemoryManager::~MemoryManager()
    {
        kputs("Memory Manager: destructor called\n");
        if(Instance == this)
            Instance = 0;
    }

    void* MemoryManager::malloc(size_t size) {

        MemoryChunk *result = 0;
    
        for(MemoryChunk* chunk = first; chunk != 0 && result == 0; chunk = chunk->next)
            if(chunk->size > size && !chunk->allocated)
                result = chunk;
            
        if(result == 0)
            return 0;
        
        if(result->size >= size + sizeof(MemoryChunk) + 1)
        {
            MemoryChunk* temp = (MemoryChunk*)((size_t)result + sizeof(MemoryChunk) + size);
            
            temp->allocated = false;
            temp->size = result->size - size - sizeof(MemoryChunk);
            temp->prev = result;
            temp->next = result->next;
            
            //VALID MEMBLOCK SIGNATURE
            temp->magic = MEMORY_CHUNK_MAGIC;


            if(temp->next != 0)
                temp->next->prev = temp;
            
            result->size = size;
            result->next = temp;
        }
        
        result->allocated = true;
        return (void*)(((size_t)result) + sizeof(MemoryChunk));
    }

    void MemoryManager::free(void* ptr) {
        

        //access memory chunk check MAGIC before attempting to free
        memory_chunk_t* ptr_mem_chunk = (memory_chunk_t*)(ptr - sizeof(memory_chunk_t));
        

        //memory block not valid
        if(ptr_mem_chunk->magic != MEMORY_CHUNK_MAGIC)
            return;

        //free memory
        #if MEMORY_DEBUG
        OS::KERNEL::Terminal::getInstance()->printf("Freeing memory at 0x%x\n", ptr);
        #endif
        printMemChunk(ptr_mem_chunk);
        printMemChunk(ptr_mem_chunk->prev);
        printMemChunk(ptr_mem_chunk->next);

        //allocated set to false then malloc can reallocate to this block
        ptr_mem_chunk->allocated = false;

        #if ZERO_DEALLOC_MEMORY

        //zero deallocated memory
        char* ptrToZero = (char*)ptr;
        for (size_t i = 0; i < ptr_mem_chunk->size; i++)
        {
            *ptrToZero = 0;
            ptrToZero++;
        }
        

        #endif

        //check for free blocks in neighbouring elements and merge together
        if(ptr_mem_chunk->prev != 0 && !ptr_mem_chunk->prev->allocated) {
            ptr_mem_chunk->prev->next = ptr_mem_chunk->next;
            ptr_mem_chunk->prev->size += ptr_mem_chunk->size + sizeof(MemoryChunk);
            if(ptr_mem_chunk->next != 0)
                ptr_mem_chunk->next->prev = ptr_mem_chunk->prev;
            
            ptr_mem_chunk = ptr_mem_chunk->prev;

        }

        if(ptr_mem_chunk->next != 0 && !ptr_mem_chunk->next->allocated) {
            ptr_mem_chunk->size += ptr_mem_chunk->next->size + sizeof(MemoryChunk);
            ptr_mem_chunk->next = ptr_mem_chunk->next->next;
            if(ptr_mem_chunk->next != 0)
                ptr_mem_chunk->next->prev = ptr_mem_chunk;
        }

    }

    void MemoryManager::printInfo() {
        kputs("\nMemory Manager Info\n");

        kprintf("Total Memory : %dMB\n", m_SizeBytes / 1024 / 1024);

        //calc used memory
        uint32_t memoryUsedBytes = 0;
        for(MemoryChunk* chunk = first; chunk != 0; chunk = chunk->next)
            if(chunk->allocated)
                memoryUsedBytes += chunk->size;
        
        kprintf("Memory In Use : %dB\n", memoryUsedBytes);
        uint32_t kbRamUsed = uint32_t((float)memoryUsedBytes / (float)(1024*1024));
        //kprintf("Memory In Use : %dMB\n", kbRamUsed);

        kprintf("Memory Available : %dB\n", (m_SizeBytes - memoryUsedBytes));
        uint32_t kbRamAvail = uint32_t((m_SizeBytes - memoryUsedBytes) / (float)(1024*1024));
        //kprintf("Memory Available : %dMB\n", kbRamAvail);

        kputs("Memory Manager Info End\n");
    }
    
}}}

void* malloc(size_t size) {
    if(OS::KERNEL::MEMORY::MemoryManager::Instance == 0)
        return 0;
    return OS::KERNEL::MEMORY::MemoryManager::Instance->malloc(size);
}

void free(void* ptr) {

    if(OS::KERNEL::MEMORY::MemoryManager::Instance == 0)
        return;

    OS::KERNEL::MEMORY::MemoryManager::Instance->free(ptr);
}

void* operator new(size_t size) {
    if(OS::KERNEL::MEMORY::MemoryManager::Instance == 0)
        return 0;
    return OS::KERNEL::MEMORY::MemoryManager::Instance->malloc(size);
}

void* operator new[](size_t size) {
    if(OS::KERNEL::MEMORY::MemoryManager::Instance == 0)
        return 0;
    return OS::KERNEL::MEMORY::MemoryManager::Instance->malloc(size);
}



void operator delete(void* ptr) {
    if(OS::KERNEL::MEMORY::MemoryManager::Instance != 0)
        OS::KERNEL::MEMORY::MemoryManager::Instance->free(ptr);
}

void operator delete[](void* ptr) {



    if(OS::KERNEL::MEMORY::MemoryManager::Instance != 0)
        OS::KERNEL::MEMORY::MemoryManager::Instance->free(ptr);
    //get block and free
    //kprintf("DELETE[] magic : %x", ((OS::KERNEL::MEMORY::memory_chunk_t*)(ptr - sizeof(OS::KERNEL::MEMORY::memory_chunk_t)))->magic);
    //ensure all objects have there destructors called
    uint32_t chuck_size = ((OS::KERNEL::MEMORY::memory_chunk_t*)(ptr - sizeof(OS::KERNEL::MEMORY::memory_chunk_t)))->size;
    uint32_t number_of_objects = chuck_size / sizeof(void*);

    uint32_t ptrAddress = (uint32_t)ptr;

    kputs("Here");
    if(OS::KERNEL::MEMORY::MemoryManager::Instance != 0)
        OS::KERNEL::MEMORY::MemoryManager::Instance->free(ptr);
}

void operator delete(void* ptr, unsigned long size) {
    if(OS::KERNEL::MEMORY::MemoryManager::Instance != 0)
        OS::KERNEL::MEMORY::MemoryManager::Instance->free(ptr);
}