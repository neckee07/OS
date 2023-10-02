//
// Created by os on 1/10/23.
//

#ifndef OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_SYSCALL_C_HPP
#define OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_SYSCALL_C_HPP

#include "tcb.hpp"

class TCB;
typedef TCB* thread_t;

int thread_create (
        thread_t* handle,
        void(*start_routine)(void*),
        void* arg
);

int thread_exit ();

void thread_dispatch ();

void thread_join (thread_t handle);


class Semafor;
typedef Semafor* sem_t;



int sem_open (
        sem_t *handle,
        unsigned init
);

int sem_close (sem_t handle);

int sem_wait (sem_t id);

int sem_signal (sem_t id);

void putc(char chr);

char getc();

void* mem_alloc(size_t size);

int mem_free(void* ptr);

#endif //OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_SYSCALL_C_HPP
