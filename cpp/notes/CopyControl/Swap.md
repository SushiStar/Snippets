# Swap
Defining `swap` is particularly important for classes that we plan to use with algorithms that reorder elements.

#### `swap` Functions Should Call `swap`, Not `std::swap`
```cpp
class HasPtr {
  friend void swap(HasPtr&, HasPtr&);
  // other members as before
};

inline
void swap(HasPtr &lhs, HasPtr &rhs) {
  using std::swap;
  swap(lhs.ps, rhs.ps);     // swap the pointers
  swap(lhs.i, rhs.i);       // swap the int members
}

void swap(Foo &lhs, Foo rhs) {
  using std::swap;
  swap(hls.h, rhs.h);        // uses the HasPtr version of swap
  // swap other members of type Foo;
}
```
If there is a type specific version of `swap`, that version will be a better match than the one defined in `std`. As a result, if there is a type-specific version of `swap`, calls to `swap` will match that type-specific version. If there is no type-specific version, then-assuming there is a `using` declaration  for `swap` in scope -- calls to `swap` will use the version in `std`.

#### Using `swap` in Assignment Operators
This technique *swaps* the left-hand operand with a *copy* of the right-hand operand.
```cpp
// note rhs is passed by value, which means the HasPtr copy constructor
// copies the string in the right-hand operand into rhs
HasPtr& HasPtr::operator=(HasPtr rhs) {
  // swap the contents of the left-hand operand with the local variable rhs
  swap(*this, rhs);     // rhs now points to the memory this object had used
  return *this;         // rhs is destoryed, which deletes the pointer in rhs
}
```
The interesting thing about this technique is that it automatically handles self assignment and is automatically exception safe. By copying the right-hand operand before changing the left-hand operand, it handles self assignment in the same way.
