#Partial template specialization
```cpp
template <typename T, int size>
void print(StaticArray<T, size> &array) {
	for (int count{ 0 }; count < size; ++count)
		std::cout << array[count] << ' ';
}

// overload of print() function for partially specialized StaticArray<char, size>
template <int size> // size is still a templated expression parameter
void print(StaticArray<char, size> &array) { // we're explicitly defining type char here
	for (int count{ 0 }; count < size; ++count)
		std::cout << array[count];
}
```
Note that as of C++14, partial template specialization can only be used with classes, not template functions (functions must be fully specialized).
Our void print(`StaticArray<char, size> &array`) example works because the print function is not partially specialized (it’s just an overloaded function using a class parameter that’s partially specialized).

##Partial template specialization for pointers
```cpp
template <class T>
class Storage {
private:
    T m_value;
public:
    Storage(T value) {
         m_value = value;
    }
    ~Storage() {}

    void print() {
        std::cout << m_value << '\n';
    }
};

template <typename T>
class Storage<T*> { // this is a partial-specialization of Storage that works with pointer types
private:
    T* m_value;
public:
    Storage(T* value) {// for pointer type T
         // For pointers, we'll do a deep copy
         m_value = new T(*value); // this copies a single value, not an array
    }
    ~Storage() {
        delete m_value; // so we use scalar delete here, not array delete
    }

    void print() {
        std::cout << *m_value << '\n';
    }
};
```
