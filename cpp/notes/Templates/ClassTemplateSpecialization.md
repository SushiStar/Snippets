# Class template specialization
Class template specialization allows us to specialize a template class for a particular data type (or data types, if there are multiple parameters). In this case, we're going to use class template specialization to write a customized version of another type that will take precedence over the generic class.
This works analogously to how a specialized function takes precedence over a generic template function.

Class template specialization are treated as completely independent classes, even though they are allocated in the same way as the tempalted classs. This means that we can change anything and everything about our specialization class, including the way it's implemented and even the function it makes public, just as if it were an independent class.
```cpp
template <class T>
class Storage8 {
private:
    T m_array[8];
public:
    void set(int index, const T &value) {
        m_array[index] = value;
    }
    const T& get(int index) {
        return m_array[index];
    }
};

template <> // the following is a template class with no templated parameters
class Storage8<bool> { // we're specializing Storage8 for bool
// What follows is just standard class implementation details
private:
    unsigned char m_data;
public:
    Storage8() : m_data(0) {}

    void set(int index, bool value) {
        // Figure out which bit we're setting/unsetting
        // This will put a 1 in the bit we're interested in turning on/off
        unsigned char mask = 1 << index;
        if (value)  // If we're setting a bit
            m_data |= mask;  // Use bitwise-or to turn that bit on
        else  // if we're turning a bit off
            m_data &= ~mask;  // bitwise-and the inverse mask to turn that bit off
	}

    bool get(int index) {
        // Figure out which bit we're getting
        unsigned char mask = 1 << index;
        // bitwise-and to get the value of the bit we're interested in
        // Then implicit cast to boolean
        return (m_data & mask);
    }
};
```
First, note that we start off with `template<>`. The template keyword tells the compiler what follows is templated, and the empty angle braces means that there aren't any template prameters. In this case, there aren't any template parameters because we're replacing the only template praemter (typename T) with a specific type (bool).
All of the other changes are just class implementation details.
Now, when we declare a class of type `Storage8<T>`, where T is not a bool, we’ll get a version stenciled from the generic templated `Storage8<T>` class. When we declare a class of type `Storage8<bool>`, we’ll get the specialized version we just created.
