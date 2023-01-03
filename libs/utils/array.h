#if !defined(ARRAY_H_CSQ)
#define ARRAY_H_CSQ
    #include <bits/c++config.h>

    namespace std
    {
    /// initializer_list
    template<class _E>
        class initializer_list
        {
        public:
        typedef _E 		value_type;
        typedef const _E& 	reference;
        typedef const _E& 	const_reference;
        typedef size_t 		size_type;
        typedef const _E* 	iterator;
        typedef const _E* 	const_iterator;

        private:
        iterator			_M_array;
        size_type			_M_len;

        // The compiler can call a private constructor.
        constexpr initializer_list(const_iterator __a, size_type __l)
        : _M_array(__a), _M_len(__l) { }

        public:
        constexpr initializer_list() noexcept
        : _M_array(0), _M_len(0) { }

        // Number of elements.
        constexpr size_type
        size() const noexcept { return _M_len; }

        // First element.
        constexpr const_iterator
        begin() const noexcept { return _M_array; }

        // One past the last element.
        constexpr const_iterator
        end() const noexcept { return begin() + size(); }
        };

    /**
     *  @brief  Return an iterator pointing to the first element of
     *          the initializer_list.
     *  @param  __ils  Initializer list.
     */
    template<class _Tp>
        constexpr const _Tp*
        begin(initializer_list<_Tp> __ils) noexcept
        { return __ils.begin(); }

    /**
     *  @brief  Return an iterator pointing to one past the last element
     *          of the initializer_list.
     *  @param  __ils  Initializer list.
     */
    template<class _Tp>
        constexpr const _Tp*
        end(initializer_list<_Tp> __ils) noexcept
        { return __ils.end(); }
    }
    //This is the class which have the features of dynamic array.
    template<typename T>
    class basic_array{
         public:
            T* arr;
            // capacity is the total storage
            int capacity;
            // current is the number of elements
            int current;
         public:
            (basic_array)(){
                arr = new T[1];
                capacity = 1;
                current = 0;
            }
            auto update(int index, T value){
                arr[index] = value;
            }
            auto push(T data){
                // if the number of elements is equal to the
                // capacity, that means we don't have space to
                // accommodate more elements. We need to double the
                // capacity
                if (current == capacity) {
                    T* temp = new T[2 * capacity];
        
                    // copying old array elements to new array
                    for (int i = 0; i < capacity; i++){
                        temp[i] = arr[i];
                    }
        
                    // deleting previous array
                    delete[] arr;
                    capacity *= 2;
                    arr = temp;
                }
                // Inserting data
                arr[current] = data;
                current++;
            }
            auto operator[](int index){
                return this->arr[index];
            }
            auto erase(T e){
                int i;
                for (i=0; i<this->current; i++)
                    if (this->arr[i] == e)
                        break;
                // If element found in array
                if (i < this->current)
                {
                    // reduce size of array and move all
                    // elements on space ahead
                    this->current = this->current - 1;
                    for (int j=i; j<this->current; j++)
                        arr[j] = arr[j+1];
                }
            }
            auto pop(){current--;}
            T* begin() { return &this->arr[0];}
            const T* begin() const { return &this->arr[0];}
            T* end() { return &this->arr[this->current]; }
            const T* end() const { return &this->arr[this->current];}
            // ~basic_array(){delete[] arr;}
    };//basic_array

    /*This class is extended version for basic_array class, this class own many features which can be used to work with dynamic array easily. but note array are not dynamic but as i like the name array i named it array.*/
    template<typename T>
    class array{
         private:
            auto abs(double value){
                double nv = value;
                if(value < 0){
                    nv = nv*(-1);
                }
                return nv;
            }
         public:
            basic_array<T> arr;
         public:
            array(){}
            array(std::initializer_list<T> il){
                for(auto i : il){
                    this->arr.push(i);
                }
            }
            array(const array<T>& arr){
                for(auto i : arr){
                    this->arr.push(i);
                }
            }  
            array(T arr[],int size){
                for(int i=0;i<(size);i++){
                    this->arr.push(arr[i]);
                }
            }
            //Iterators for for each loop.
            T* begin() { return &this->arr.arr[0];}
            const T* begin() const { return &this->arr.arr[0];}
            T* end() { return &this->arr.arr[this->arr.current]; }
            const T* end() const { return &this->arr.arr[this->arr.current];}
            //This method returns the length of the array.
            auto len(){return this->arr.current;}
            //Reading data
            auto operator[](int index){
                T ret;
                if(index<arr.current){
                    ret = arr[index];
                }
                return ret;
            }
            //Adding data
            auto operator+=(T element){arr.push(element);}
            auto operator=(array<T> arr){
                for(int i = 0; i<arr.len();i++){
                   this->arr.push(arr[i]);
                }
            }
            auto operator==(array<T> arr){
                bool state = 1;
                for(int i=0;i<arr.len();i++){
                    if(this->arr[i]!=arr[i]){state = 0;}
                }
                return state;
            }
            auto add(T element){arr.push(element);}
            template<typename... Args>
            auto add(T e1,Args... args){
                arr.push(e1);
                add(args...);
            }
            //Operator for slicing
            auto operator()(int from,int till,int steps=1){
                array<T> n;
                for(int i=from-1;i<till;i+=steps){
                    n.add(this->arr[i]);
                }
                return n;
            }
            auto operator()(int till,int steps=1){
                array<T> n;
                for(int i=0;i<till;i+=steps){
                    n.add(this->arr[i]);
                }
                return n;
            }
            //This method will allocate the memory.
            auto allocate(int size){
                arr.capacity = size;
                arr.current = size;
            }
            //Update data
            auto update(int index,T element){
                arr.update(index,element);
                
            }
            //This method returns the count of the element inside the array.
            auto count(T element){
                int count = 0;
                for(int i = 0; i < this->arr.current; i++){
                    switch (this->arr[i] == element)
                    {
                        case 1:
                            count++;
                        case 0:
                            continue; 
                    }
                }
                return count;
            }
        
            //This method pop the elements.
            auto pop(){return this->arr.pop();}
            //This method erase the given element from the array.
            auto erase(T element){
                this->arr.erase(element);
            }

            //This method returns an array of indexes on which the given element is present.
            auto find(T element){
                array<int> index;
                for(int i=0;i<this->len();i++){
                    if(this->arr[i] == element){
                        index.add(i);
                        // break;
                    }
                }
                return index;
            }
            //This method replaces the occurence of element in the array.
            auto replace(T real_element, T new_element){
                for(int i=0;i<this->arr.current;i++){
                    if(this->arr[i] == real_element){
                        this->arr.update(i,new_element);
                    }
                }
            }

            //Typecasting array to int
            //But only works for str to int conversion.
            // auto toint(){
            //     array<int> arr;
            //     for(auto i : this->arr){
            //         arr.add(toint(str(i)));
            //     }
            //     return arr;
            // }
            //But only works for str to double conversion.
            //This method will return unique values.
            auto unique(){
                int res = 1;
                array<T> e;
                // Pick all elements one by one
                for (int i = 0; i < this->len(); i++) {
                    int j = 0;
                    for (j = 0; j < i; j++)
                        if (arr[i] == arr[j])
                            break;

                    // If not printed earlier, then print it
                    if (i == j)
                        e.add(arr[i]);
                }
                return e;
            };
    };// array

bool in(array<str> arr,str target){
    bool state = false;
    for(auto i : arr){
        if(i == target){
            state = true;
            break;
        }
    }
    return state;
}

#endif // ARRAY_H_CSQ
