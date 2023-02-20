#ifndef REFERENCECOUNT_H_CSQ4
#define REFERENCECOUNT_H_CSQ4
#include <memory>

template <typename T>
class ref : std::shared_ptr<T> {
public:
    ref() : std::shared_ptr<T>(nullptr) {}
    inline ref(T *ptr) : std::shared_ptr<T>(ptr) {}
    inline ref(T val) : std::shared_ptr<T>(new T(val)) {}
    inline ref(std::shared_ptr<T> ptr) : std::shared_ptr<T>(ptr) {}
    inline ref(const ref<T> &sp) : std::shared_ptr<T>(sp) {}

    inline ref<T> &operator=(const ref<T> &sp) {
        this->std::shared_ptr<T>::operator=(sp);
        return *this;
    }

    inline T *operator->() const {
        return this->get();
    }

    inline T &operator*() const {
        return *(this->get());
    }

    inline void reset(T *ptr) {
        this->reset(ptr);
    }
    inline ref<T> operator++(int){
        return ref<T>(T(this->get()+(1)));
    }
    inline ref<T> operator+(const ref<T> &rhs) {
        return ref<T>(new T(this->get()->op_add(*this->get(),*rhs.get())));
    }
    inline ref<T> operator-(const ref<T> &rhs) {
        return ref<T>(new T(this->get()->op_sub(*this->get(),*rhs.get())));
    }
    inline ref<T> operator*(const ref<T> &rhs) {
        return ref<T>(new T(this->get()->op_mul(*this->get(),*rhs.get())));
    }
    inline ref<T> operator/(const ref<T> &rhs) {
        return ref<T>(new T(this->get()->op_div(*this->get(),*rhs.get())));
    }
    inline bool operator>(const ref<T> &rhs) {
        return ((this->get()->op_greater(*this->get(),*rhs.get())));
    }
    inline bool operator<(const ref<T> &rhs) {
        return ((this->get()->op_lesser(*this->get(),*rhs.get())));
    }
    inline bool operator>=(const ref<T> &rhs) {
        return ((this->get()->op_greaterEqual(*this->get(),*rhs.get())));
    }
    inline bool operator<=(const ref<T> &rhs) {
        return ((this->get()->op_lesserEqual(*this->get(),*rhs.get())));
    }
    inline bool operator!=(const ref<T> &rhs) {
        return ((this->get()->op_notEqual(*this->get(),*rhs.get())));
    }
    inline bool operator==(const ref<T> &rhs) {
        return (this->get()->op_equal(*this->get(),*rhs.get()));
    }

    auto operator[](int index);
};

#endif // REFERENCECOUNT_H_CSQ4
