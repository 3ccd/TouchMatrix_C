//
// Created by chiic on 2021/11/30.
//

#ifndef TOUCHMATRIX_SINGLETON_H
#define TOUCHMATRIX_SINGLETON_H

template<class T>
class Singleton{

public:
    static inline T& GetInstance(){
        static T instance;
        return instance;
    }

protected:
    Singleton()= default;
    virtual ~Singleton()= default;

private:
    void operator=(const Singleton& obj){}
    Singleton(const Singleton &obj)= default;

};

#endif //TOUCHMATRIX_SINGLETON_H
