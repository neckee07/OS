//
// Created by marko on 20.4.22..
//

#include "../h/riscv.hpp"
#include "../h/tcb.hpp"
#include "../lib/console.h"
#include "../h/printing.hpp"
#include "../h/semafor.hpp"
#include "../h/memory.hpp"


void Riscv::popSppSpie()
{
    __asm__ volatile("csrw sepc, ra");
    __asm__ volatile("sret");
}


void Riscv::handleSupervisorTrap()
{
    uint64 scause = r_scause();
    uint64 arg0;
    __asm__ volatile ("mv %0, a0" : "=r" (arg0));
    if (scause == 0x0000000000000009UL && arg0 == 27)
    {
        uint64 sepc = r_sepc() + 4;
        //uint64 sstatus = r_sstatus();
        mc_sstatus(SSTATUS_SPP);
        //w_sstatus(sstatus);
        w_sepc(sepc);
    } else if (scause == 0x0000000000000008UL || scause == 0x0000000000000009UL)
    {
        // interrupt: no; cause code: environment call from U-mode(8) or S-mode(9)
        uint64 volatile sepc = r_sepc() + 4;
        uint64 volatile sstatus = r_sstatus();
        uint64 arg;
        __asm__ volatile("mv %0, a0" : "=r" (arg));
        if (arg == 0x11)
        {
            thread_t *mojthread;
            __asm__ volatile ("mv %0, a1": "=r" (mojthread));
            void (*mojafunkcija)(void *);
            __asm__ volatile ("mv %0, a2": "=r" (mojafunkcija));
            void *mojarg;
            __asm__ volatile ("mv %0, a6" : "=r" (mojarg));

            *mojthread = TCB::createThread(mojafunkcija, mojarg);
            if (mojthread != 0)
            {
                uint64 vrednost = 0;
                __asm__ volatile ("mv a0, %0"::"r" (vrednost));

            } else
            {
                uint64 vrednost = -1;
                __asm__ volatile ("mv a0, %0"::"r" (vrednost));

            }

        } else if (arg == 0x12)
        {
            TCB::running->setFinished(true);
            TCB::dispatch();
            uint64 vrednost = 0;
            __asm__ volatile ("mv a0, %0"::"r" (vrednost));
        } else if (arg == 0x13)
        {
            sem_t *mojsem;
            __asm__ volatile ("mv %0, a1": "=r" (mojsem));
            unsigned broj;
            __asm__ volatile ("mv %0, a2": "=r" (broj));
            *mojsem = Semafor::createSem(broj);


            if (mojsem != 0)
            {
                uint64 vrednost = 0;
                __asm__ volatile ("mv a0, %0"::"r" (vrednost));

            } else
            {
                uint64 vrednost = -1;
                __asm__ volatile ("mv a0, %0"::"r" (vrednost));

            }

        } else if (arg == 0x14)
        {
            sem_t mojsem;
            __asm__ volatile ("mv %0, a1": "=r" (mojsem));
            mojsem->odblock();
            delete mojsem;

            uint64 mojbroj = 0;
            __asm__ volatile ("mv a0, %0"::"r" (mojbroj));

        } else if (arg == 0x15)
        {
            sem_t mojsem;
            __asm__ volatile ("mv %0, a1": "=r" (mojsem));
            uint64 mojbroj = mojsem->wait();
            __asm__ volatile ("mv a0, %0"::"r" (mojbroj));
        } else if (arg == 0x16)
        {
            sem_t mojsem;
            __asm__ volatile ("mv %0, a1": "=r" (mojsem));
            uint64 mojbroj;
            mojbroj = mojsem->signal();
            __asm__ volatile ("mv a0, %0"::"r" (mojbroj));
        } else if (arg == 0x17)
        {
            char mojchar;
            __asm__ volatile ("mv %0, a1": "=r" (mojchar));
            __putc(mojchar);
        } else if (arg == 0x18)
        {
            char mojchar = __getc();
            __asm__ volatile ("mv a0, %0"::"r" (mojchar));
        } else if (arg == 0x19)
        {
            size_t mojsize;
            __asm__ volatile ("mv %0, a1": "=r" (mojsize));
            void *mojmem = Memory::mem_alloc(mojsize);
            __asm__ volatile ("mv a0, %0"::"r" (mojmem));
        } else if (arg == 0x20)
        {
            void *mojptr;
            __asm__ volatile ("mv %0, a1": "=r" (mojptr));
            int mojbroj = Memory::mem_free(mojptr);
            __asm__ volatile ("mv a0, %0"::"r" (mojbroj));
        } else if (arg == 0x21)
        {
            thread_t mojthread;
            __asm__ volatile ("mv %0, a1": "=r" (mojthread));

            TCB::join(mojthread);
        } else
        {
            TCB::timeSliceCounter = 0;
            TCB::dispatch();
        }
        w_sstatus(sstatus);
        w_sepc(sepc);

    } else if (scause == 0x8000000000000001UL)
    {
        // interrupt: yes; cause code: supervisor software interrupt (CLINT; machine timer interrupt)
        mc_sip(SIP_SSIP);
        TCB::timeSliceCounter++;
        if (TCB::running != 0)
            if (TCB::timeSliceCounter >= TCB::running->getTimeSlice())
            {
                uint64 volatile sepc = r_sepc();
                uint64 volatile sstatus = r_sstatus();
                TCB::timeSliceCounter = 0;
                TCB::dispatch();
                w_sstatus(sstatus);
                w_sepc(sepc);
            }
    } else if (scause == 0x8000000000000009UL)
    {
        // interrupt: yes; cause code: supervisor external interrupt (PLIC; could be keyboard)
        console_handler();
    } else
    {
        if (scause == 0x0000000000000002UL)printString("Illegalna instrukcija\n");
        if (scause == 0x0000000000000005UL)printString("Nedozvoljena adresa citanja\n");
        if (scause == 0x0000000000000007UL)printString("Nedozvoljena adresa upisa\n");

        while (1)
        {

        }

    }
}