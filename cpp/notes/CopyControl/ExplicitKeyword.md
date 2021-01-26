# What is the purpose of `explicit` keyword?
To tell the compiler that a certain constructor may not be used to implicitly cast an expression to its class type.

The explicit keyword is an optional decoration for constructors that take exactly one argument. It only applies to single-argument constructors since those are the only constructors that can be used in type casting.

For example, without the explicit keyword the following code is valid:
```cpp
class Foo {
public:
  Foo(int x);
};

class Bar {
public:
  Bar(double x);
};

void yourCode()
{
  Foo a = 42;         //OK: calls Foo::Foo(int) passing 42 as an argument
  Foo b(42);          //OK: calls Foo::Foo(int) passing 42 as an argument
  Foo c = Foo(42);    //OK: calls Foo::Foo(int) passing 42 as an argument
  Foo d = (Foo)42;    //OK: calls Foo::Foo(int) passing 42 as an argument

  Bar x = 3.14;       //OK: calls Bar::Bar(double) passing 3.14 as an argument
  Bar y(3.14);        //OK: calls Bar::Bar(double) passing 3.14 as an argument
  Bar z = Bar(3.14);  //OK: calls Bar::Bar(double) passing 3.14 as an argument
  Bar w = (Bar)3.14;  //OK: calls Bar::Bar(double) passing 3.14 as an argument
}
```

But sometimes you want to prevent this sort of implicit promotion or implicit type conversion. For example, if Foo is really an array-like container and 42 is the initial size, you might want to let your users say, Foo x(42); or perhaps Foo x = Foo(42);, but not just Foo x = 42;. If that's the case, you should use the explicit keyword:
```cpp
class Foo {
public:
  explicit Foo(int x);
};

class Bar {
public:
  explicit Bar(double x);
};

void yourCode()
{
  Foo a = 42;         //Compile-time error: can't convert 42 to an object of type Foo
  Foo b(42);          //OK: calls Foo::Foo(int) passing 42 as an argument
  Foo c = Foo(42);    //OK: calls Foo::Foo(int) passing 42 as an argument
  Foo d = (Foo)42;    //OK: calls Foo::Foo(int) passing 42 as an argument

  Bar x = 3.14;       //Compile-time error: can't convert 3.14 to an object of type Bar
  Bar y(3.14);        //OK: calls Bar::Bar(double) passing 3.14 as an argument
  Bar z = Bar(3.14);  //OK: calls Bar::Bar(double) passing 3.14 as an argument
  Bar w = (Bar)3.14;  //OK: calls Bar::Bar(double) passing 3.14 as an argument
}
```
