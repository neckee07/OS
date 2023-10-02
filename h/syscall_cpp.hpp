//
// Created by os on 1/13/23.
//

#ifndef OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_SYSCALL_CPP_HPP
#define OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_SYSCALL_CPP_HPP

#include "syscall_c.hpp"

class TCB;
typedef TCB* thread_t;

class Semafor;
typedef Semafor* sem_t;

static int id = 0;

class Thread {
public:
    Thread (void (*body)(void*), void* arg);
    virtual ~Thread ();
    int start ();
    static void dispatch ();
    int getId();
    void join();
    //static int sleep (time_t);
protected:
    Thread ();
    virtual void run () {}
private:
    int myId = id++;
    thread_t myHandle;
    friend class TCB;
};
class Semaphore {
public:
    Semaphore (unsigned init = 1);
    virtual ~Semaphore ();
    int wait ();
    int signal ();
private:
    sem_t myHandle;
};
//class PeriodicThread : public Thread {
//protected:
//    PeriodicThread (time_t period);
//    virtual void periodicActivation () {}
//};
class Console {
public:
    static char getc ();
    static void putc (char c);
};
#endif //OS1_VEZBE07_RISCV_CONTEXT_SWITCH_2_INTERRUPT_SYSCALL_CPP_HPP
