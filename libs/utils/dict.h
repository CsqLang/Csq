#if !defined(DICT_UTILS_H)
#define DICT_UTILS_H
    #include "array.h"
    //This class stores data in the form of key-value pair same as map.
    template<typename K,typename V>
    struct dict{
            array<K> keys;
            array<V> values;
            //Constructors
            dict(){}
            dict(array<K> keys,array<V> values){
                this->keys = keys;
                this->values = values;
            }
            //This operator reads the value on the basis of key.
            auto operator[](K key){
                V val;
                bool in__ = false;
                for(int i=0;i<this->keys.len();i++){
                    if(key == this->keys[i]){
                        val = this->values[i];
                        in__ = true;
                        break;
                    }
                }
                return val;
            }
            auto operator=(dict<K,V> d){
                this->keys = d.keys;
                this->values = d.values;
            }
            //This method adds the pair.
            auto add(K key,V val){keys.add(key),values.add(val);}
            //This method updates the value.
            auto update(K key,K val){
                bool there = 0;
                for(int i=0;i<keys.len();i++){
                    if(key == keys[i]){
                        values.update(i,val);
                        there = 1;
                    }
                }
                if(there == 0){
                    keys.add(key);
                    values.add(val);
                }
            }
            //This method returns a str representation of the dictionary
            auto readall(){
                str s = "{ ";
                for(int i=0;i<this->keys.len();i++){
                    s += to_str(keys[i]) + ":";
                    s += to_str(values[i])+",";
                    s += " ";
                }
                return str(s+"}");
            }

            auto pop(){
                this->keys.pop();
                this->values.pop();
            }
    };
#endif // DICT_UTILS_H
