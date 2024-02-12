#pragma once

#include <cinttypes>

#include "impl.hpp"

#ifdef _WIN32

    #include <windows.h>

    struct Thread {
        Thread(void(*f)(void*arg),void* arg) IMPL({
            Thread::_f = f;
            Thread::_arg = arg;
            this->_h = CreateThread( 0,0, Thread::_bootstrapper, 0, 0, &this->_id );
        })

        void kill() IMPL({
            DWORD code;
            GetExitCodeThread(this->_h,&code);
            TerminateThread(this->_h,code);
        })

        HANDLE _h;
        DWORD _id;

        static DWORD WINAPI _bootstrapper(LPVOID) IMPL({
            Thread::_f(Thread::_arg);
            return 0;
        })

        static void sleep(uint32_t ms) IMPL({
            Sleep(ms);
        })

        static void(*_f)(void*arg);
        static void* _arg;
    };

    void(*Thread::_f)(void*arg) = nullptr;
    void* Thread::_arg = nullptr;

#elif __linux__

    #include <pthread.h>

    TODO

#endif