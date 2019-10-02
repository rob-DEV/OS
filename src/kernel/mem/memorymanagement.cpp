#include "../include/mem/memorymanagement.h"



namespace OS { namespace KERNEL { namespace MEMORY {

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
        OS::KERNEL::Terminal::getInstance()->print("Memory Manager: destructor called\n");
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
        if(ptr_mem_chunk->magic = MEMORY_CHUNK_MAGIC)
            return;

        //free memory



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
}

void operator delete(void* ptr, unsigned long size) {
    if(OS::KERNEL::MEMORY::MemoryManager::Instance != 0)
        OS::KERNEL::MEMORY::MemoryManager::Instance->free(ptr);
}