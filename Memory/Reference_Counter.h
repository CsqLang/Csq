#if !defined(Reference_Counter_H)
#define Reference_Counter_H

template<class T>
class SmartPointer{
  public:
    T* ptr;
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
        ptr = new T(*(op.ptr));
        ref_count++;
      }
      else if(ref_count != 0){
        delete ptr;
        ref_count = 0;
        ptr = new T(*(op.ptr));
        ref_count++;
      }
    }
    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    ~SmartPointer() {
      delete ptr;
    }
};
