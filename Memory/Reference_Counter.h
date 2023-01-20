#if !defined(Reference_Counter_H)
#define Reference_Counter_H
template <typename T>
class SmartPointer{
 public:
  SmartPointer(T* ptr) : ptr_(ptr), ref_count_(new int(1)) {}
  SmartPointer(T v) : ptr_(new T(v)), ref_count_(new int(1)) {}
  SmartPointer(const SmartPointer<T>& other) :
      ptr_(other.ptr_), ref_count_(other.ref_count_) {
    ++(*ref_count_);
  }
SmartPointer(){}
  SmartPointer<T>& operator=(const SmartPointer<T>& other) {
    if (this != &other) {
      if (--(*ref_count_) == 0) {
        delete ptr_;
        delete ref_count_;
      }
      ptr_ = other.ptr_;
      ref_count_ = other.ref_count_;
      ++(*ref_count_);
    }
    return *this;
  }
  void operator+=(SmartPointer<T> v){
    this->ptr_ =  new int(*ptr_+(*v));
  }
  void operator++(int){
    this->ptr_ =  new int(*ptr_+1);
  }
  void operator--(int){
    this->ptr_ =  new int(*ptr_-1);
  }
  SmartPointer<T> operator+(SmartPointer<T> v){
      return SmartPointer<T>((*ptr_)+(*v));
  }
  // void operator:(array<T> arr){
  //   for(T v : arr){

  //   }
  // }

  ~SmartPointer() {
    if (--(*ref_count_) == 0) {
      delete ptr_;
      delete ref_count_;
    }
  }

  T& operator*() const { return *ptr_; }
  T* operator->() const { return ptr_; }

 private:
  T* ptr_;
  int* ref_count_;
};

#endif // Reference_Counter_H
