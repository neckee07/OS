//
// Created by os on 1/11/23.
//

#ifndef OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_SEMAFOR_HPP
#define OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_SEMAFOR_HPP

#include "tcb.hpp"

class Semafor
{

public:
    static Semafor *createSem(unsigned broj);

    int wait();

    int signal();

    int value() const { return val; }

protected:
    void block();

    void unblock();

    void odblock();

private:

    Semafor(unsigned init = 1) : val(init) {
        blocked = new List<TCB>;
    }

public:
    virtual ~Semafor();

private:
    bool desilo = false;
    int val;
    List<TCB> *blocked;

    friend class Riscv;
};


#endif //OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_SEMAFOR_HPP
