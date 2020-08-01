# Copy Control and Resource Management
Ordinarilly, classes that manage resources that do not reside in the class must define the copy-control members. Such classes will need destructors to free the resources allocated by the object.
In order to define these members, we first have to decide what copying an object of our type will mean. In general, we have two choices: We can define the copy operations to make  the class be have like a value or like a pointer.
* Classes that behave like values have their own state. When we copy a valuelike object, the copy and the original are independent of each other.
* Classes taht behave like pointers share state. When we copy objects of such classes, the copy and the original use the same underlying data.

### Classes That Act Like Values
To provide valuelike behavior, each object has to have its own copy of the resourc that the class manages.

#### Valuelike Copy-Assignment Operator
Assignment operators typically combine the actions of the destructor and the copy constructor. Like the destructor, assignment destroys the left-hand operand's resources. Like the copy constructor, assignment copies data from the right-hand operand. However, it is crucially important that these actions be done in a sequence that is correct even if an object is assigned to itself.
> There are two points to keep in mind when you write an assignment operator.
> * Assignment operators must work correctly if an object is assigned to itself.
> * Most assignment operators share work with the destructor and copy constructor.
> A good pattern to use when you write an assignment operator is to first copy the right-hand operand into a local temporary. After the copy is done, it is safe to destroy the existing members of the left-hand operand. Once the left-hand operand is destroyed, copy the data from the temporary into the members of the left-hand operand.
```cpp
// WRONG way to write an assignment operator
HasPtr&
HasPtr::operator=(const HasPtr &rhs) {
  delete ps;      // free the string to which this object points
  // if rhs and *this are the same object, we're copy from deleted memory
  ps = new string(*(rhs.ps));
  i = rhs.i;
  return *this;
}
```
> It is crucially important for assignment operators to work correctly, even when an object is assigned to itself. A good way to do so is to copy the right-hand operand before destroying the left-hand operand.

### Defining Classes That Act Like Pointers
The easiest way to make a class act like a pointer is to use `shared_ptr`s to manage the resources in the class. Copying (or assigning) a `shared_ptr` copies (assigns) the pointer to which the `shared_ptr` points. The `shared_ptr` class itself keeps track of how many users are sharing the pointed-to object. When there are no more users, the `shared_ptr` class takes care of freeing the resource.
However, sometimes we want to manage a resource directly. In such cases, it can be useful to use a **reference count**.

#### Reference Counts
* In addition to initializing the object, each constructor (other than the copy constructor) creates a counter. This counter will keep track of how many objects share state with the object we are creating. When we create an object, there is only one such object, so we initialize the counter to 1.
* The copy constructor does not allocate a new counter; instead, it copies the data members of its given object, including the counter. The copy constructor increments this shared counter, indicating that there is another user of that object's state.
* The destructor decrements the counter, indicating that there is one less user of the shared state. If the count goes to zero, the destructor deletes that state.
* The copy-assignment operator increments the right-hand operand's counter and decrements the counter of the left-hand  operand. If the counter for teh left-hand operand goes to zero, there are no more users. In this case, the copy-assignment operator must destroy the state of the left-hand operand.

The only wrinkle is where to put the reference count.
One way to sovle this problem is to store the counter in the dynamic memory. When we create an object, we'll also allocate a new counter. When we copy or assign an object, we'll copy the pointer to the counter. That way the copy and the original will point to the same counter.

#### Defining a Reference-Counted Class
```cpp
class HasPtr {
public:
  // constructor allocates a new string and a new counter, which is set to 1
  HasPtr(const std::string &s = std::string()) :
    ps(new std::string(s)), i(0), use(new std::size_t(1)){}
  // copy constructor copies all three data members and increments the counter
  HasPtr(const HasPtr &p) :
    ps(p.ps), i(p.i), use(p.use) {++*use;}
  HasPtr& operator=(const HasPtr&);
  ~HasPtr();
private:
  std::string *ps;
  int i;
  std::size_t *use;   // member to keep track of how many objects share *ps;
};
```

#### Pointerlike Copy Members "Fiddle" the Reference Count
```cpp
HasPtr& HasPtr::operator=(const HasPtr& rhs) {
  ++*rhs.use;
  if (--*use == 0) {
    delete ps;
    delete use;
  }
  ps = rhs.ps;
  i = rhs.i;
  sue = rhs.use;
  return *this;
}
```
