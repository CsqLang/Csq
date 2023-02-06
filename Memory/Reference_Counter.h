#ifndef REFERENCECOUNT_H_CSQ4
#define REFERENCECOUNT_H_CSQ4
#include <stdio.h>
#include <stdlib.h>

class ReferenceCounter{
private:
    int count;

public:
    ReferenceCounter() : count(1) {}

    void addReference() {
        count++;
    }

    int removeReference() {
        return --count;
    }

    int getCount() const {
        return count;
    }
};

template <typename T>
class ref  : T {
private:
    T *ptr;
    ReferenceCounter *refCounter;

public:
    ref(T *ptr) : ptr(ptr), refCounter(new ReferenceCounter()) {}
    ref(const ref<T> &sp) :
        ptr(sp.ptr), refCounter(sp.refCounter) {
        refCounter->addReference();
    }

    ~ref() {
        if (refCounter->removeReference() == 0) {
            delete ptr;
            delete refCounter;
        }
    }

    ref<T> &operator=(const ref<T> &sp) {
        if (this != &sp) {
            if (refCounter->removeReference() == 0) {
                delete ptr;
                delete refCounter;
            }

            ptr = sp.ptr;
            refCounter = sp.refCounter;
            refCounter->addReference();
        }

        return *this;
    }

    T *operator->() const {
        return ptr;
    }

    T &operator*() const {
        return *ptr;
    }
    void reset(T *ptr) {
        if (refCounter->removeReference() == 0) {
            delete this->ptr;
            delete refCounter;
        }

        this->ptr = ptr;
        refCounter = new ReferenceCounter();
    }
    ref<T> operator+(const ref<T> &rhs) {
        return ref<T>(new T((this->op_add(new T(*ptr),new T(*rhs)))));
    }
    ref<T> operator-(const ref<T> &rhs) {
        return ref<T>(new T((this->op_sub(new T(*ptr),new T(*rhs)))));
    }
    ref<T> operator*(const ref<T> &rhs) {
        return ref<T>(new T((this->op_mul(new T(*ptr),new T(*rhs)))));
    }
    ref<T> operator/(const ref<T> &rhs) {
        return ref<T>(new T((this->op_div(new T(*ptr),new T(*rhs)))));
    }
};

#endif // REFERENCECOUNT_H_CSQ4
