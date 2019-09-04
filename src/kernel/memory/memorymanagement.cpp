#include "../include/memory/memorymanagement.h"


namespace OS { namespace KERNEL { namespace MEMORY {

    MemoryManager* MemoryManager::Instance = NULL;

    MemoryManager::MemoryManager(size_t start, size_t size){
        
        Instance = this;
    
        if(size < sizeof(MemoryChunk))
        {
            first = 0;
        }
        else
        {
            first = (MemoryChunk*)start;
            
            first -> allocated = false;
            first -> prev = 0;
            first -> next = 0;
            first -> size = size - sizeof(MemoryChunk);
        }
        }
    MemoryManager::~MemoryManager()
    {
        if(Instance == this)
            Instance = 0;
    }

    void* MemoryManager::malloc(size_t size) {

        MemoryChunk* allocation_result = NULL;

        for(MemoryChunk* chunk = first; chunk != NULL && allocation_result == NULL; chunk = chunk->next)
            if(chunk->size > size && !chunk->allocated)
                allocation_result = chunk;

        //no free heap memory / bug (more likely a bug)
        if(allocation_result == NULL)
            return NULL;

        if(allocation_result->size >= size + sizeof(MemoryChunk) + 1)
        {
            MemoryChunk* temp_chunk = (MemoryChunk*)((size_t)allocation_result + sizeof(MemoryChunk) + size);
            temp_chunk->allocated = false;
            temp_chunk->size = allocation_result->size - size - sizeof(MemoryChunk);
            temp_chunk->prev = allocation_result;
            temp_chunk->next = allocation_result->next;

            if(temp_chunk->next != NULL)
                temp_chunk->next->prev=temp_chunk;

            allocation_result->size = size;
            allocation_result->next = temp_chunk;
        }

        allocation_result->allocated = true;

        //return a pointer to the data alloc start address
        //to do this get the result - memory header (memory_chunk_t)
        return (void*)(((size_t)(allocation_result) + sizeof(MemoryChunk)));
    }

    void MemoryManager::free(void* ptr) {
        //this is the reverse of malloc()

        //find the memory chunk -> address of data - sizeof(memory_chunk_t) == chunk start address
        MemoryChunk* chunk = (MemoryChunk*)((size_t)ptr - sizeof(MemoryChunk));
        //deallocate the memory
        chunk->allocated = false;

        uint32_t* chunk_data_ptr = (uint32_t*)chunk + sizeof(MemoryChunk);



        uint32_t* data_address = (uint32_t*)ptr;
        //TEST NULLIFY ALL MEMORY
        for (int i = 0; i < chunk->size; ++i) {
            *data_address = 0;
            data_address++;
        }

        if(chunk->prev != NULL && !chunk->prev->allocated)
        {
            chunk->prev->next = chunk->next;
            chunk->prev->size += chunk->size + sizeof(MemoryChunk);

            if(chunk->next != NULL)
                chunk->next->prev = chunk->prev;

            chunk = chunk->prev;
        }

        if(chunk->next != NULL && !chunk->next->allocated){
            chunk->size += chunk->next->size + sizeof(MemoryChunk);
            chunk->next = chunk->next->next;
            if(chunk->next != NULL)
                chunk->next->prev = chunk;
        }
        }

    
}}}

void* operator new(size_t size)
{
    if(OS::KERNEL::MEMORY::MemoryManager::Instance == 0)
        return 0;
    return OS::KERNEL::MEMORY::MemoryManager::Instance->malloc(size);
}

void* operator new[](size_t size)
{
    if(OS::KERNEL::MEMORY::MemoryManager::Instance == 0)
        return 0;
    return OS::KERNEL::MEMORY::MemoryManager::Instance->malloc(size);
}

void* operator new(size_t size, void* ptr)
{
     if(OS::KERNEL::MEMORY::MemoryManager::Instance == 0)
        return 0;
    return OS::KERNEL::MEMORY::MemoryManager::Instance->malloc(size);
}

void* operator new[](size_t size, void* ptr)
{
     if(OS::KERNEL::MEMORY::MemoryManager::Instance == 0)
        return 0;
    return OS::KERNEL::MEMORY::MemoryManager::Instance->malloc(size);
}

void operator delete(void* ptr)
{
    if(OS::KERNEL::MEMORY::MemoryManager::Instance != 0)
        OS::KERNEL::MEMORY::MemoryManager::Instance->free(ptr);
}

void operator delete[](void* ptr)
{
    if(OS::KERNEL::MEMORY::MemoryManager::Instance != 0)
        OS::KERNEL::MEMORY::MemoryManager::Instance->free(ptr);
}