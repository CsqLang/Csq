#if !defined(Reference_Counter_H)
#define Reference_Counter_H

#define op_assign operator=
template<class T>
class SmartPointer : T{
  private:
    T* ptr = nullptr;
    int ref_count = 0;
  public:
    SmartPointer(){}
    SmartPointer(const SmartPointer<T>& inc){
      ptr = new T(*(inc.ptr));
      ref_count++;
    }
    SmartPointer(T* ptr){this->ptr = new T(*(ptr));ref_count++;}
    SmartPointer(T t){
      ptr = new T(t);
      ref_count++;
    }
    auto operator=(const SmartPointer<T>& op ){
      if(ref_count == 0){
        ptr = new T();
        ptr = op.ptr;
        ref_count++;
      }
      else if(ref_count != 0){
        delete ptr;
        ref_count = 0;
        ptr = new T(*(op.ptr));
        ref_count++;
      }
    }
    auto operator+(SmartPointer<T> op){
      return this->op_add((ptr),op);
    }
    auto operator-(SmartPointer<T> op){
      return this->op_sub((ptr),op);
    }
    auto operator*(SmartPointer<T> op){
      return this->op_mul((ptr),op);
    }
    auto operator/(SmartPointer<T> op){
      return this->op_div((ptr),op);
    }
    auto operator%(SmartPointer<T> op){
      return this->op_mod((ptr),op);
    }
    auto operator>(SmartPointer<T> op){
      return this->op_greater((ptr),op);
    }
    auto operator<(SmartPointer<T> op){
      return this->op_lesser((ptr),op);
    }
    auto operator>=(SmartPointer<T> op){
      return this->op_greaterEqual((ptr),op);
    }
    auto operator<=(SmartPointer<T> op){
      return this->op_lesserEqual((ptr),op);
    }
    auto operator !=(SmartPointer<T> op){
      return this->op_notEqual((ptr),op);
    }
    auto operator ==(SmartPointer<T> op){
      return this->op_equal((ptr),op);
    }
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    ~SmartPointer() {
      delete ptr;
    }
};
#endif // Reference_Counter_H
