//
// Created by marko on 20.4.22..
//

#include "../h/tcb.hpp"
#include "../h/riscv.hpp"
#include "../h/syscall_cpp.hpp"

TCB *TCB::running = nullptr;

uint64 TCB::timeSliceCounter = 0;

TCB *TCB::createThread(Body body, void* data)
{

    return new TCB(body, TIME_SLICE, data);
}

void TCB::yield()
{
    __asm__ volatile ("ecall");

}

void TCB::dispatch()
{
    TCB *old = running;

    if (!old->isFinished()) { Scheduler::put(old); }
    running = Scheduler::get();

    TCB::contextSwitch(&old->context, &running->context);
}

void TCB::join(thread_t handle) {
    while(!handle->isFinished())
    {
        TCB::dispatch();
    }
}

void TCB::threadWrapper()
{
    Riscv::popSppSpie();
    if(running->body != nullptr){
        running->body(running->data);
    }else
        if(running->nitHandle != nullptr)
            running->nitHandle->run();//nastaviti sutra sa data ovde
    running->setFinished(true);
    //TCB::yield();
    Thread::dispatch();
    //thread_dispatch();
}
