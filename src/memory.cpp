//
// Created by os on 1/10/23.
//

#include "../h/memory.hpp"


Memory::FreeMem *Memory::mem_head;

void Memory::Inicijalizacija()
{
    mem_head = (Memory::FreeMem *) HEAP_START_ADDR;
    size_t size = (size_t) HEAP_END_ADDR - (size_t) HEAP_START_ADDR;
    mem_head->size = size;
    mem_head->next = nullptr;
    mem_head->prev = nullptr;
    mem_head->zauzet = 0;
}

void *Memory::mem_alloc(size_t size)
{
    FreeMem *tek = mem_head;
    size_t pravisize = 0;
    FreeMem *novi = nullptr;

    if ((size + (sizeof(FreeMem))) <= MEM_BLOCK_SIZE)
    {
        pravisize = MEM_BLOCK_SIZE;
    } else if ((size + (sizeof(FreeMem))) > MEM_BLOCK_SIZE)
    {
        if ((size + (sizeof(FreeMem))) % MEM_BLOCK_SIZE == 0)
        {
            uint64 veciza = (size + (sizeof(FreeMem))) / MEM_BLOCK_SIZE;
            pravisize = MEM_BLOCK_SIZE * veciza;
        } else
        {
            uint64 veciza = (size + (sizeof(FreeMem))) / MEM_BLOCK_SIZE + 1;
            pravisize = MEM_BLOCK_SIZE * veciza;
        }
    }

    for (; tek != nullptr; tek = tek->next)
    {
        if (pravisize < tek->size && tek->zauzet == 0)
        {

            tek->size -= pravisize;
            novi = (FreeMem *) ((char *) tek + tek->size);
            novi->next = tek->next;
            if (tek->next != nullptr)
                tek->next->prev = novi;
            tek->next = novi;
            novi->zauzet = 1;
            novi->prev = tek;
            novi->size = pravisize;




            break;

        }
    }


    if (novi != 0) return (void *) ((char *) novi + sizeof(FreeMem));
    return nullptr;
}


int Memory::mem_free(void *ptr)
{

    if((uint64) ptr <= 0)
        return -1;

    FreeMem *newSeg = (FreeMem *) ((char *) ptr - sizeof(FreeMem));
    newSeg->zauzet = 0;
    if (newSeg->next)
    {
        if (newSeg->next->zauzet == 0)
        {
            FreeMem *tek = newSeg->next;
            newSeg->size += tek->size;
            newSeg->next = tek->next;
            tek->prev = nullptr;
            tek->next = nullptr;

        }
    }

    if (newSeg->prev)
    {
        if (newSeg->prev->zauzet == 0)
        {
            FreeMem *tek = newSeg->prev;
            tek->size += newSeg->size;
            tek->next = newSeg->next;
            newSeg->next = nullptr;
            newSeg->prev = nullptr;
        }
    }


    return 0;


}


