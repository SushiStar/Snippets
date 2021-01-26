# Copy, Assign, and Destroy

### The Copy Constructor
A constructor is a copy constructor if its first parameter is a reference to the class type and any additional parameters have default values:
```cpp
   class Foo {
    public:
      Foo();                // default constructor
      Foo(const Foo& );     // copy constructor
   }
```
The first parameter is almost always a reference to `const`, although we can define the copy constructor to take a reference to take `nonconst`.
The copy constructor is used implicitly in several circumstances. Hence, the copy constructor usually should not be `explicit`.

#### The Synthesized Copy Constructor
When we do not define a copy constructor for a class, the compiler synthesizes one for us. Unlike the synthesized default constructor, a copy constructor is synthesized even if we define other constructors.
The synthesized copy constructor **memberwise copies** the members of its argument into the object being created. The compiler copies each `nonstatic` member in turn from the given object into the one being created.

Members of class type are copied by the copy constructor for that class; members of built-in type are copied directly.

```cpp
class Sales_data {
 public:
  // other members and constructors as before
  // declaration equivalent to the synthesized copy constructor
  Sales_data(const Sales_data&);
 private:
  std::string bookNo;
  int units_sold = 0;
  double revenue = 0.0;
};

// equivalent to the copy constructor that would be  synthesized for Sales_data
Sales_data::Sales_data (const Sales_data &orig) :
  BookNo(orig.bookNo),          // uses the string copy constructor
  units_sold(orig.units_sold),  // copies orig.units_sold
  revenue(orig.revenue)         // copies orig.revenue
  {}
```
#### Copy Initialization
```cpp
string dots(10, '.');         // direct initialization
string s(dots);               // direct initialization
string s2 = dots;             // copy initialization
string null_book = "sdfij"    // copy initialization
string nines = string(100, '9')   // copy initialization
```
When we use direct initialization, we are asking the compiler to use ordinary function matching to select the constructor that best matches the argument we provide.
When we use **copy initialization**, we are asking the compiler to copy the right-hand operand into the object being created, converting that operand if necessary.
When copy initialization happens and that copy initialization requires either the copy constructor or the move constructor.

Copy initialization happens not only when we define variables using an `=`, but also when we
  * Pass an object as an argument to a parameter of nonreference type
  * Return an object from a function that has a nonreference return type
  * Brace initialize the elements in an array or the members of an aggregate class

Whey copy constructor's own prameter must be a reference?
If that parameter were not a referencel, the the call would never succeed -- to call the copy constructor, we'd need to use the copy constructor to copy the argument, but to copy the argument, we'd need the copy constructor, and so on indefinitely.

#### Constraints on Copy Initialization
We cannot use an implicitly use an *explicit* constructor when we pass an argument or return a value from a function. If we want to use an *explicit* constructor, we must do so explicitly.
(*refer to ExplicitKeyword.md*)


### The Copy-Assignment Operator
It controls how objects of its calss are assigned. As with the copy constructor, the compiler synthesizes a copy-assignment operator if the class does not define its own.

#### Introducing Overloaded Assignment
Overloaded operators are functions that have the same name *operator* followed by the symbol for the operator being defined. Hence, the assignment operator is a function named `operator=`. The parameters in an overloaded operator represent the operands of the operator.
When an operator is a member function, the left-hand operand is bound to the implicit `this` parameter. The right-hand operand in a binary operator, such as assignment, is passed as an explicit parameter.
To be consistent with assignment for built-in types, assignment operators usually return a reference to their left-hand operand.

#### The Synthesized Copy-Assignment Operator
For some classes the synthesized copy-assignment operator disallows assignment. As an example, the following is equivalent to the synthesized `Sales_data` copy-assignment operator:
```cpp
// equivalent to the synthesized copy-assignment operator
Sales_data&
Sales_data::operator=(const Sales_data &rhs) {
  bookNo = rhs.bookNo;          // calls the string::operator=
  units_sold = rhs.units_sold;  // uses the built-in int assignment
  revenue = rhs.revenue;        // uses the built-in double assignment
  return *this;                 // return a reference to this object
}
```

### The Destructor
Destructors do whatever is needed to free the resources used by an object and destroy the non `static` data members of the object.
In a destructor, the function body is executed first and then the members are destroyed. Members are destroyed in the reverse order from the order they were originally initialized.

#### When a Destructor Is Called
The destructor is used automatically whenever an object of its type is destroyed:
* Variables are destroyed when they go out of scope.
* Members of an object are destroyed when the object of which they are a part is destroyed.
* Elements in a container -- whether a library container or an array -- are destroyed when the container is destroyed.
* Dynamically allocated objects are destroyed when the `delete` operator is applied to a pointer to the object.
* Temporary objects are destroyed at the end of the full expression in which the temporary was created.
> The destructor is *not* run when a reference or a pointer to an object goes out of scope.

#### The Synthesized Destructor
The compiler defines a synthesized destructor for any class that does not define its own destructor.

### Classes That Need Destrocutors Need Copy and Assignment
If the class needs a destructor, it almost surely needs a copy constructor and copy-assignment operator as well. Considering the deletion of a pointer to an object does not call its destructor.

### Classes That Need Copy Need Assignemnt, and Vice Versa
If a class needs a copy constructor, it almost surely needs a copy-assignment operator. (All elements are copied by the synthesized constructor or assignment, but not what user wanted.)
nevertheless, needing either the copy constructor or the copy-assignment operator does not (necessarily) indicate the need for a destructor.

### Using`= default`
We can explicitly ask the compiler to generate the synthesized versions of the copy-control members by defining them as `= default`.
```
class Sales_data {
public:
  // copy controls; use defaults
  Sales_data() = default;
  Sales_data(const Sales_data&) = default;
  Sales_data& operator=(const Sales_data&);
  ~Sales_data() = default;
}
```
When we specify `= default` on the delcaration of the member inside the class body, the **synthesized function is implicitly inline** (just as is any other member function defined in the body of the class). If we do not want the synthesized member to be an inline fucntion, we can specify `=default` on the member's definition.

### Preventing Copies
> Most classes should define -- either implicitly or explicitly -- the default and copy constructors and the copy-assignment operator.
It might seem that we could prevent copies byf not defining the copy-control members. However, this strategy doesn't work: If our class doesn't define these operations, the compiler will synthesize them.

#### Defining a Function as Deleted
A deleted function is one that is declared but may not be used in any other way. We indicate that we want to define a function as deleted by following its parameter list with `=delete`.
```cpp
struct NoCopy {
  NoCopy()=default;           // use the synthesized default constructor
  NoCopy(const NoCopy&) = delete; // no copy
  NoCopy &operator=(const NoCopy&) = delete;  // no assignment
  ~Nocopy() = default;    // synthesized
};
```
Unlike `=default`, `=delete` must appear on the first declaration of a deleted function.
Also unlike `=default`, we can specify `=delete` on any function (we can use `= default` only on the default constructor or a copy-control member that the compiler can synthesize).

#### The Copy-Control Members May Be Synthesized as Deleted
For some classes, the compiler defines these synthesized members as deleted functions:
* The synthesized destructor is defined as deleted if the class has a member whose own destructor is deleted or is inaccessible (e.g., private);
* The synthesized copy constructor is defined as deleted if the class has a member whose own copy constructor is deleted or inaccessible. It is also deleted if the class has a member with a deleted or inaccessible destructor.
* The synthesized copy-assignment operator is defined as deleted if a member has a deleted or inaccessible copy-assignment operator, or if the class has a `const` or reference member.
* The synthesized default constructor is defined as deleted if the class has a member with a deleted or inaccessible destructor; or has a member that does not have an in-class initializer; or has a `const` member whose type does not explicitly define a default constructor and that member does not have an in-class initializer.

In essence, these rules mean that if a class has a data member that cannot be default constructed, copied, or destoryed, then the  corresponding member will be a deleted function.
It should not be surprising that  the compiler will not synthesize a default constructor for a class with a reference member or a `const` member that cannot be default constructed. Nor should it be surprising that a class with a `const` member cannot use the synthesized copy-assignment operator: After all, that operator attempts to assign to every member. It is not possible to assign a new value to a `const` object.

> Classes that want to prevent copying should define their copy constructor and copy-assignment operators using `= delete` rather than making those members private.

