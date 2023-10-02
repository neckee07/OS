//
// Created by os on 1/13/23.
//

#include "../h/syscall_cpp.hpp"

Thread::Thread (void (*body)(void*), void* arg){
    thread_create(&myHandle, body, arg);
    myHandle->nitHandle = this;
}
Thread::~Thread (){
    delete myHandle;
}
int Thread::start (){
    Scheduler::put(myHandle);
    return 0;
}
void Thread::dispatch (){
    thread_dispatch();

}

void Thread::join() {
    if(myHandle)
        thread_join(this->myHandle);
}

Thread::Thread (){
    thread_create(&myHandle, nullptr, nullptr);
    myHandle->nitHandle = this;
}

int Thread::getId() {
    return myId;
}



Semaphore::Semaphore (unsigned init){
    sem_open(&myHandle, init);
}
Semaphore::~Semaphore (){
    sem_close(myHandle);
}
int Semaphore::wait (){
    int n = sem_wait(myHandle);
    return n;
}
int Semaphore::signal (){
    int n = sem_signal(myHandle);
    return n;
}

char Console::getc (){
    char c = ::getc();
    return c;
}
void Console::putc (char c){
    ::putc(c);
}