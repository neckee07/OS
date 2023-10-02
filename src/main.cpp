//
// Created by marko on 20.4.22..
//

#include "../h/tcb.hpp"
#include "../h/printing.hpp"
#include "../h/riscv.hpp"
#include "../h/memory.hpp"
#include "../h/syscall_c.hpp"
#include "../h/semafor.hpp"
#include "../h/userMain.hpp"


int main()
{
    Memory::Inicijalizacija();
    Riscv::w_stvec((uint64) &Riscv::supervisorTrap);
    //Riscv::ms_sstatus(Riscv::SSTATUS_SIE);
    TCB *threads;
    thread_create(&threads, nullptr, nullptr);
    TCB::running = threads;
    
//Gasi se tajmer
    __asm__ volatile ("csrc sie, %[mask]" : : [mask] "r"(2));
    Riscv::ms_sstatus(Riscv::SSTATUS_SIE);
//prelazak u korisnicki
    uint64 broj = 27;
    __asm__ volatile("mv a0, %0" : : "r" (broj));
   __asm__ volatile ("ecall");



    userMain();
//
//    Semaphore *mutex;
//    //Semaphore mutex;
//    TCB *threads[5];
//    sem_open(&mutex,1);
//
//    thread_create(&threads[0], nullptr, nullptr);
//    //threads[0] = TCB::createThread(nullptr);
//    TCB::running = threads[0];
//
//
//    thread_create(&threads[1], workerBodyA, nullptr);
//    printString("ThreadA created\n");
//    thread_create(&threads[2], workerBodyB, nullptr);
//    printString("ThreadB created\n");
//    thread_create(&threads[3], workerBodyC, nullptr);
//    printString("ThreadC created\n");
//    thread_create(&threads[4], workerBodyD, nullptr);
//    printString("ThreadD created\n");
//
//
//    while (!(threads[1]->isFinished() &&
//             threads[2]->isFinished() &&
//             threads[3]->isFinished() &&
//             threads[4]->isFinished()))
//    {
//
//
//        thread_dispatch();
//        //TCB::yield();
//
//    }
//
//    for (auto &thread: threads)
//    {
//        delete thread;
//    }
    printString("Finished\n");

    return 0;
}
