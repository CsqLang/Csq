#ifndef REFERENCECOUNT_H_CSQ4
#define REFERENCECOUNT_H_CSQ4
#include <stdio.h>
#include <stdlib.h>
#include <atomic>

class ReferenceCounter{
private:
    std::atomic<int> count;

public:
    ReferenceCounter() : count(1) {}

    void addReference() {
        count++;
    }

    int removeReference() {
        return --count;
    }

    int getCount() const {
        return count.load();
    }
};

template <typename T>
class ref : T{
private:
    T *ptr;
    ReferenceCounter *refCounter;
public:
    ref() : ptr(nullptr), refCounter(new ReferenceCounter()) {}
    ref(T *ptr = nullptr) : ptr(ptr), refCounter(new ReferenceCounter()) {}
    ref(T &obj) : ptr(new T(obj)), refCounter(new ReferenceCounter()) {}
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
        return this->op_add(*ptr, *rhs.ptr);
    }
    ref<T> operator-(const ref<T> &rhs) {
        return this->op_sub(*ptr, *rhs.ptr);
    }
    ref<T> operator*(const ref<T> &rhs) {
        return this->op_mul(*ptr, *rhs.ptr);
    }
    ref<T> operator/(const ref<T> &rhs) {
        return this->op_div(*ptr, *rhs.ptr);
    }
    auto operator%(ref<T> op){
    return this->op_mod(*ptr, *op.ptr);
    }
    auto operator>(ref<T> op){
    return this->op_greater(*ptr, *op.ptr);
    }
    auto operator<(ref<T> op){
    return this->op_lesser(*ptr, *op.ptr);
    }
    auto operator>=(ref<T> op){
    return this->op_greaterEqual(*ptr, *op.ptr);
    }
    auto operator<=(ref<T> op){
    return this->op_lesserEqual(*ptr, *op.ptr);
    }
    auto operator !=(ref<T> op){
    return this->op_notEqual(*ptr, *op.ptr);
    }
    auto operator ==(ref<T> op){
    return this->op_equal(*ptr, *op.ptr);
    }

    auto operator[](int index);

};

#endif // REFERENCECOUNT_H_CSQ4
