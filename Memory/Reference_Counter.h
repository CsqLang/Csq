#ifndef REFERENCECOUNT_H_CSQ4
#define REFERENCECOUNT_H_CSQ4
#include <memory>

template <typename T>
class ref : std::shared_ptr<T> {
public:
    ref() : std::shared_ptr<T>(nullptr) {}
    inline ref(T *ptr) : std::shared_ptr<T>(ptr) {}
    inline ref(T &obj) : std::shared_ptr<T>(std::make_shared<T>(obj)) {}
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

    inline ref<T> operator+(const ref<T> &rhs) {
        return this->op_add(this->get(), rhs.get());
    }
    inline ref<T> operator-(const ref<T> &rhs) {
        return this->op_sub(this->get(), rhs.get());
    }
    inline ref<T> operator*(const ref<T> &rhs) {
        return this->op_mul(this->get(), rhs.get());
    }
    inline ref<T> operator/(const ref<T> &rhs) {
        return this->op_div(this->get(), rhs.get());
    
    }
    inline auto operator%(ref<T> op){
    return this->op_mod(this->get(), op.get());
    }
    inline auto operator>(ref<T> op){
    return this->op_greater(this->get(), op.get());
    }
    inline auto operator<(ref<T> op){
    return this->op_lesser(this->get(), op.get());
    }
    inline auto operator>=(ref<T> op){
    return this->op_greaterEqual(this->get(), op.get());
    }
    inline auto operator<=(ref<T> op){
    return this->op_lesserEqual(this->get(), op.get());
    }
    inline auto operator !=(ref<T> op){
    return this->op_notEqual(this->get(), op.get());
    }
    inline auto operator ==(ref<T> op){
    return this->op_equal(this->get(), op.get());
    }

    auto operator[](int index);
};

#endif // REFERENCECOUNT_H_CSQ4
