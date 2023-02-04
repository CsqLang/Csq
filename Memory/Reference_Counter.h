#if !defined(REFERENCECOUNT_H_CSQ4)
#define REFERENCECOUNT_H_CSQ4
#include <stdio.h>
#include <stdlib.h>
class ReferenceCounter {
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
class SmartPointer {
private:
    T *ptr;
    ReferenceCounter *refCounter;

public:
    SmartPointer(T *ptr) : ptr(ptr), refCounter(new ReferenceCounter()) {}
    SmartPointer(const SmartPointer<T> &sp) :
        ptr(sp.ptr), refCounter(sp.refCounter) {
        refCounter->addReference();
    }

    ~SmartPointer() {
        if (refCounter->removeReference() == 0) {
            delete ptr;
            delete refCounter;
        }
    }

    SmartPointer<T> &operator=(const SmartPointer<T> &sp) {
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
};


#endif // REFERENCECOUNT_H_CSQ4
