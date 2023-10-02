//
// Created by os on 1/11/23.
//

#include "../h/semafor.hpp"
#include "../h/tcb.hpp"
#include "../h/syscall_c.hpp"


Semafor *Semafor::createSem(unsigned broj)
{
    return new Semafor(broj);
}

void Semafor::block()
{

    blocked->addLast(TCB::running);

    TCB::running->setFinished(true);

    thread_dispatch();

}

int Semafor::wait()
{

    uint64 ret = -1;
    if (--val < 0)
    {

        block();
        if (!desilo)
        {
            ret++;
        }
    }
    return ret;

}

void Semafor::odblock()
{
    while (blocked->peekFirst())
    {
        TCB *t = blocked->removeFirst();
        t->setFinished(false);
        Scheduler::put(t);
        desilo = true;
    }

}

void Semafor::unblock()
{
    TCB *t = blocked->removeFirst();
    t->setFinished(false);
    Scheduler::put(t);

}

int Semafor::signal()
{

    uint64 ret = -1;

    if (++val <= 0)
    {
        ret++;
        if (blocked->peekFirst())
            unblock();
    }
    return ret;

}

Semafor::~Semafor()
{
    delete blocked;
}
