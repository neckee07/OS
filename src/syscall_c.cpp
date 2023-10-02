//
// Created by os on 1/10/23.
//

#include "../h/syscall_c.hpp"
#include "../h/printing.hpp"

int thread_create(
        thread_t *handle,
        void(*start_routine)(void *),
        void *arg
)
{
    __asm__ volatile ("mv a6, a2");//zezaju 3 i 4
    __asm__ volatile ("mv a2, a1");
    __asm__ volatile ("mv a1, a0");
    uint64 vrednost = 0x11;
    __asm__ volatile ("mv a0, %0"::"r" (vrednost));

    __asm__ volatile ("ecall");

    __asm__ volatile("mv %0, a0":"=r"(vrednost));

    return vrednost;

}

int thread_exit()
{




    uint64 vrednost = 0x12;
    __asm__ volatile ("mv a0, %0"::"r" (vrednost));

    __asm__ volatile ("ecall");

    __asm__ volatile("mv %0, a0":"=r"(vrednost));

    return vrednost;
}

void thread_dispatch()
{

    __asm__ volatile("ecall");
}

void thread_join (thread_t handle){
    __asm__ volatile ("mv a1, a0");
    uint64 vrednost = 0x21;
    __asm__ volatile ("mv a0, %0"::"r" (vrednost));

    __asm__ volatile ("ecall");
}

int sem_open(
        sem_t *handle,
        unsigned init
)
{
    __asm__ volatile ("mv a2, a1");
    __asm__ volatile ("mv a1, a0");
    uint64 vrednost = 0x13;
    __asm__ volatile ("mv a0, %0"::"r" (vrednost));

    __asm__ volatile ("ecall");

    __asm__ volatile("mv %0, a0":"=r"(vrednost));

    return vrednost;
}

int sem_close (sem_t handle){

    __asm__ volatile ("mv a1, a0");
    uint64 vrednost = 0x14;
    __asm__ volatile ("mv a0, %0"::"r" (vrednost));

    __asm__ volatile ("ecall");

    __asm__ volatile("mv %0, a0":"=r"(vrednost));

    return vrednost;

}

int sem_wait (sem_t id){
    __asm__ volatile ("mv a1, a0");
    uint64 vrednost = 0x15;
    __asm__ volatile ("mv a0, %0"::"r" (vrednost));

    __asm__ volatile ("ecall");

    __asm__ volatile("mv %0, a0":"=r"(vrednost));

    return vrednost;
}

int sem_signal (sem_t id){
    __asm__ volatile ("mv a1, a0");
    uint64 vrednost = 0x16;
    __asm__ volatile ("mv a0, %0"::"r" (vrednost));

    __asm__ volatile ("ecall");

    __asm__ volatile("mv %0, a0":"=r"(vrednost));

    return vrednost;
}

void putc(char chr){
    __asm__ volatile ("mv a1, a0");
    uint64 vrednost = 0x17;
    __asm__ volatile ("mv a0, %0"::"r" (vrednost));

    __asm__ volatile("ecall");
}

char getc(){

    uint64 vrednost = 0x18;
    __asm__ volatile ("mv a0, %0"::"r" (vrednost));

    __asm__ volatile ("ecall");
    char vrednost1;
    __asm__ volatile("mv %0, a0":"=r"(vrednost1));

    return vrednost1;
}

void* mem_alloc(size_t size){
    __asm__ volatile ("mv a1, a0");
    uint64 vrednost = 0x19;
    __asm__ volatile ("mv a0, %0"::"r" (vrednost));

    __asm__ volatile ("ecall");

    void* vracanje;
    __asm__ volatile("mv %0, a0":"=r"(vracanje));

    return vracanje;

}

int mem_free(void* ptr){
    __asm__ volatile ("mv a1, a0");
    uint64 vrednost = 0x20;
    __asm__ volatile ("mv a0, %0"::"r" (vrednost));

    __asm__ volatile ("ecall");

    __asm__ volatile("mv %0, a0":"=r"(vrednost));

    return vrednost;
}