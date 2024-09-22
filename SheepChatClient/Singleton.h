#ifndef SINGLETON_H
#define SINGLETON_H
#include "global.h"

template<typename T>
class Singleton{
public:
    static std::shared_ptr<T> getInstance(){
        static std::once_flag flag_;
        std::call_once(flag_,[&](){
            instance_ = std::shared_ptr<T>(new T);
        });
        return instance_;
    }

    ~Singleton(){
        std::cout<<"~Singleton"<<std::endl;
    }

    void PrintAddress() {
        std::cout << instance_.get() << std::endl;
    }
protected:
    Singleton() = default;

    Singleton(Singleton<T>&) = delete;
    Singleton& operator=(Singleton<T>&) = delete;

    static std::shared_ptr<T> instance_;
};

template<typename T>
std::shared_ptr<T> Singleton<T>::instance_ = nullptr;

#endif // SINGLETON_H
