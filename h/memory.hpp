//
// Created by os on 1/10/23.
//

#ifndef OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_MEMORY_HPP
#define OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_MEMORY_HPP

#include "../lib/hw.h"

class Memory
{
public:
    struct FreeMem {
        FreeMem* next;
        FreeMem* prev;
        size_t size;
        uint8 zauzet;
    };



    static void Inicijalizacija();

    static void* mem_alloc(size_t size);

    static int mem_free(void* ptr);

    static int tryToJoin(FreeMem* cur);

    static FreeMem* mem_head;
};


#endif //OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_MEMORY_HPP
