#if !defined(Reference_Counter_H)
#define Reference_Counter_H

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
      return (*ptr).val;
    }
    auto operator-(SmartPointer<T> op){
      return this->op_sub(op);
    }
    auto operator*(SmartPointer<T> op){
      return this->op_mul(op);
    }
    auto operator/(SmartPointer<T> op){
      return this->op_div(op);
    }
    auto operator%(SmartPointer<T> op){
      return this->op_mod(op);
    }
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    ~SmartPointer() {
      delete ptr;
    }
};

// template <typename T>
// class SmartPointer:T{
//  public:
//   SmartPointer(T* ptr) : ptr_(ptr), ref_count_(new int(1)) {}
//   SmartPointer(T v) : ptr_(new T(v)), ref_count_(new int(1)) {}
//   SmartPointer(const SmartPointer<T>& other) :
//       ptr_(other.ptr_), ref_count_(other.ref_count_) {
//     ++(*ref_count_);
//   }
// SmartPointer(){}
//   SmartPointer<T>& operator=(const SmartPointer<T>& other) {
//     if (this != &other) {
//       if (--(*ref_count_) == 0) {
//         delete ptr_;
//         delete ref_count_;
//       }
//       ptr_ = &((T)(*other.ptr_));
//       ref_count_ = other.ref_count_;
//       ++(*ref_count_);
//     }
//     return *this;
//   }
//   void operator++(int){
//     this->ptr_ =  new int(*ptr_+1);
//   }
//   void operator--(int){
//     this->ptr_ =  new int(*ptr_-1);
//   }
//   auto operator+(SmartPointer<T> v){
//     return this->op_add(v);
//   }
//   auto operator-(SmartPointer<T> v){
//     return this->op_sub(v);
//   }
//   auto operator*(SmartPointer<T> v){
//     return this->op_mul(v);
//   }
//   auto operator/(SmartPointer<T> v){
//     return this->op_div(v);
//   }

//   ~SmartPointer() {
//     if (--(*ref_count_) == 0) {
//       delete ptr_;
//       delete ref_count_;
//     }
//   }

//   T& operator*() const { return *ptr_; }
//   T* operator->() const { return ptr_; }

//  private:
//   T* ptr_;
//   int* ref_count_;
// };

#endif // Reference_Counter_H
