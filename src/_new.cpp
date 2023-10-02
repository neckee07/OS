//
// Created by marko on 20.4.22..
//

#include "../lib/mem.h"
#include "../h/memory.hpp"
#include "../h/syscall_c.hpp"


using size_t = decltype(sizeof(0));

void *operator new(size_t n)
{
    return mem_alloc(n);
}

void *operator new[](size_t n)
{
    return Memory::mem_alloc(n);
}

void operator delete(void *p) noexcept
{
    Memory::mem_free(p);
}

void operator delete[](void *p) noexcept
{
    Memory::mem_free(p);
}