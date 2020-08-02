# Moving Objects
In some circumstances, an object is immediately destroyed after it is copied. In those cases, moving, rather than copying the object can provide a significant performance boost.
A second reason to move rather than copy occurs in classes such as the IO or `unique_ptr` classes. These classes have a resource that may not be shared.

### Rvalue References
To support move operations, the new standard introduced a new kind of reference, an **rvalue reference**. An rvalue reference is a reference that must be bound to  an rvalue. An rvalue refernce is obtained by using `&&` rather than `&`.
They may be bound only to an object that is about to be destroyed. As a result, we are free to "move" resources from an rvalue reference to another object.

Generally speaking, an lvalue expression refers to an object's identity whereas an rvalue expression refers to an object's value. We canot directly bind an rvalue reference to an lvalue:
```cpp
int i = 42;
int &r = i;               // ok, r refers to i
int &&rr = i;             // error: cannot bind an rvalue reference to an lvalue

int &r2 = i*42;           // error: i*42 is an rvalue
const int &r3 = i*42;     // ok: we can bind a reference to const to an rvalue
int &&rr2 = i*42;         // ok: bind rr2 to the result of the multiplication
```

Functions that return lvalue references, along with the assignment, subscript, deference, and prefix increment/decrement operators, are all examples of expressions that return lvalues. We can bind an lvalue reference to the result of any of these expressions.
Funcitons that return a nonreference type, along the the arithmetic, relational, bitwise, and postfix increment/decrement operators, all yield rvalues. We cannot bind an lvalue reference to these expressions, but we can bind either an lvalue reference to `const` or an rvlaue reference to such expressions.

#### Lvalues Persist; Rvalues Are Ephemeral
Lvalues have persistent state, whereas rvalues are either literals or temporaries, we know that
* The referred-to object is about to be destroyed
* There can be no other users of the object
These facts mean that code that uses an rvalue reference is free to take over resources from the object to which the reference refers.

#### The Library `move` Function
Although we cannot directly bind an rvalue reference to an lvalue, we can explicitly cast an lvalue to its corresponding rvalue reference type. We can also obtain an rvalue reference bound to an lvalue by calling a new library function named `move` which is defined in the `utility` header.
```cpp
int &&rr3 = std::move(rr1);   // ok
```
It is essential to realize that the call to `move` promises that we do not intend to use `rr1` again except to assign to it or to destroy it.

### Move Constructor and Move Assignment
To enable move operations for our own types, we define a move constructor and a move-assignment operator. Like the copy constructor, the move constructor has an initial parameter that is a reference to the class type. Differently from the copy constructor, the reference parameter in the move constructor is an rvalue refernece.

In addition to moving resources, the move constructor must ensure that the moved-from object is left in a state such that destroying that object will be harmless. In particular, once its resources are moved, the original object must no longer point to those moved resources -- responsibility for those resources has been assumed by the newly created object.

#### Move Operations, Library Containers, and Exceptions
Because a move operation executes by "stealing" resources, it ordinarily does not itself allocate any resources. As a result, move operations odrinarily will not throw any exception. When we write a move operation that cannot throw, we should inform the library of that fact.
One way to inform the library is to specify `noexcept` on our constructor. We must specify `noexcept` on both the declaration in the class header and on the definition if that definition appears outside the class. Unless the library knows  that our move constructor won't throw, it will do extra work to cater to the possibility that moving an object of our class type might throw.
> Move constructors and move assignment operators that cannot throw exceptions should be marked as `noexcept`.

We need to indicate that a move operation doesn't throw because of two interrelated facts: First, although move operations usually don't throw exceptions, they are permitted to do so. Second, the library containers provide guarantees as to what they do if an exception happens.

#### Move-Assignment Operator
The move-assignment operator does the same work as the destructor and the move constructor. As with the move constructor, if our move-assignment operator won't throw any exceptions, we should make it `noexcept`. Like a copy-assignment operator, a move-assignment operator must guard against self-assignment.
```cpp
StrVec &StrVec::operator=(StrVec &&rhs) noexcept {
   // direct test for self-assignment
  if (this != &rhs) {
    free();                         // free existing elements
    elements = rhs.elements;        // take over resources from rhs
    first_free = rhs.first_free;
    cap = rhs.cap;
    // leave rhs in a destructible state
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
  }
  return *this;
}
```
We do the check because that rvalue could be the result of calling `move`. As in any other assignment operator, it is crucial that we not free the left-hand resources before using those (possibly same) resources from the right-hand operand.

#### A Moved-from Object Must Be Destructible
> After a move operation, the "moved-from" object must remain a valid, destructible object but users may make no assumptions about its value.

#### The Synthesized Move Operations
For some classes the compiler does not synthesize the move operations *at all*. In particular, if a class defines its own copy constructor, copy-assignment operator, or destructor, the move constructor and move-assignment operator are not synthesized.
When a class doesn't have a move operation, the corresponding copy operation is used in place of move through normal function matching.

The compiler will synthesize a move constructor or a move-assignment operator *only* if the class doesn't define any of its own copy-control members and if every non*static* data members of the class can be moved. The compiler can move members of built-in type. It can also move members of a class typeof the class can be moved. The compiler can move members of built-in type if the member's class has the corresponding move operations:
```cpp
// the compiler will synthesize the move operations for X and hasX
struct X {
  int i;          // built-in types can be moved
  std::string s;  // string defines its own move operations
};

struct hasX {
  X mem;          // X has synthesized move operations
};

X x, x2 = std::move(x);         // use the synthesized move constructor
hasX hx, hx2 = std::move(hx);   // use the synthesized move constructor
```
If we explicitly ask the compiler to generate a move operation by useing `= default`, and the compiler is unable to move all the members, then the move operation will be defined as deleted.
* Unlike the copy constructor, the move constructor is defined as deleted if the class has a member that defines its own copy constructor but does not als define a move constructor (meaning, that memeber does not have move operations), or if the class has a member that doesn't define its own copy operations and for which the compiler is unable to synthesize a move constructor. Similarily for move-assignment.
* The move constructor or move-assignment operator is defined as deleted if the class has a member whose own move constructor or move-assignment operator is deleted or accessible.
* Like a copy constructor, the move constructor is defined as deleted if the destructor is deleted or inaccessible.
* Like a copy assignment operator, the move-assignment operator is defined as deleted if the class has a `const` or reference member.

For example, assuming `Y` is a class that defines its own copy constructor but does not also define its own move constructor.
```cpp
struct hasY {
  hasY() = default;
  hasY(hasY&&) = default;
  Y mem;    // hasY will have a deleted move constructor
};

hasY hy, hy2 = std::move(hy);   // error: move constructor is deleted
```
If a class defines either a move constructor and/or a move-assignment operator, then the synthesized copy constructor and copy-assignment operator for that class will be defined as deleted.

#### Rvalues Are Moved, Lvalues are Copied ...
When a class has both a move constructor and a copy constructor, the compiler uses ordinary function matching to determine which constructor to use. Similarily for assignment.
```cpp
StrVec v1, v2;
v1 = v2;                    // v2 is an lvalue; copy assignment
StrVec getVec(istream &);   // getVec returns an rvalue
v2 = getVec(cin);           // getVec(cin) is an rvalue; move assignment;
```

#### ...But Rvalues Are Copied If There Is No More Constructor
What if a class has a copy constructor but does not define a move constructor?
In this case, the compiler will not synthesize the move constructor, which means the class has a copy constructor but no move constructor. If a class has no move constructor, function matching ensures that objects of that type are copied, even if we attempt to move them by calling `move`:
```cpp
class Foo {
public:
  Foo() = default;
  Foo(const Foo&);        // copy constructor
  // other member, but Foo does not define a move constructor
};

Foo x;
Foo y(x);                 // copy constructor; x is an lvalue
Foo z(std::move(x));      // copy constructor, because there is no more constructor
```
The call to `move(x)` in the initialization of `z` returns a `Foo&&` bound to x. The copy constructor for `Foo` is viable because we can convert a `Foo&&` to a `const Foo&`. It is worth noting that using the copy constructor in place of a move constructor is almost surely safe.

#### Copy-and-Swap Assignment Operators and Move
```cpp
class HasPtr {
public:
  // added move constructor
  HasPtr(HasPtr&& p) noexcept:ps(p.ps), i(p.i), {p.ps = 0;}
  // assignment operator is both the move- and copy-assignment operator
  HasPtr& operator=(HasPtr rhs) {
    swap(*this, rhs);
    return *this;
  }
};
```
That operator has a nonreference parameter, which means the parameter is copy initialized. Depending on the type of the argument, copy initialization uses either the copy constructor or the move constructor; lvalues are copied and rvalues are moved. As a result, this single operator acts as both the copy-assignment and move-assignment operator.
```cpp
hp = hp2;               // hp2 is an lvalue; copy constructor used to copy hp2;
hp = std::move(hp2);    // move constructor moves hp2;
```
> All five copy-control members should be thought of as a unit: Ordinarily, if a class defines any of these operations, it usually should define them all. As we've seen, some classes *must* define the copy constructor, copy-assignment operator, and destructor to work correctly. Such classes typically have a resource that the copy members must copy. Ordinarily, copying a resource entails some amount of overhead. Classes that define the move constructor and move-assignment operator can avoid this overhead in those circumstances where a copy isn't necessary.

> Don't be too quick to move
> Because a moved-from object has indeterminate state, calling `std::move` on an object is a dangerous operation. When we call `move`, we must be absolutely certain that there can be no other users of the moved-from object.
> Judiciously used inside class code, `move` can offer significant performance benefits. Casually used in ordinary user code, moving an object is more likely to lead ot mysterious and hard-to-find bugs than to any improvement in the performance of the application.

### Rvalue References and Member Functions
Member functions other than constructors and assigment can benefit from providing both copy and move versions.
Overloaded  functions that distinguish bewteen moving and copying a parameter tyically have one version that takes a `const T&` and one that takes a `T&&`
```cpp
class StrVec {
public:
  void push_back(const std::string&);         // copy the element
  void push_back(std::string&&);              // move the element
};

void StrVec::push_back(const std::string& s) {
  chk_n_alloc();    // ensure that there is room for another element
  // construct   a copy of s in the element to which first_free points
  alloc.construct(first_free++, s);
}

void StrVec::push_back(string &&s) {
  chk_n_alloc;      // reallocates the StrVec if necessary
  alloc.construct(first_free++, std::move(s));
}
```
The difference is that the rvalue reference version of `push_back` calls `move` to pass its paremeter to `constsruct`. As we've seen, the `construct` function uses the type of its second and subsequent arguments to determine which constructor to use. Because `move` returns an rvalue reference, the type of the argument to `construct` is `string&&`. Therefore, the `string` move constructor will be used to construct a new last element.

