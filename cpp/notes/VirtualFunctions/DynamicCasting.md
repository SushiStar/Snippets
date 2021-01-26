#Dynamic casting
####The need for `dynamic_cast`
When dealing with polymorphism, you'll often enconter cases where you have a pointer to a base class, but you want to access some information that exists only in the derived class.
We know that C++ will implicitly let you convert a Derived pointer into a Base pointer. This process is sometimes called **upcasting**.

####`dynamic_cast`
Although dynamic casts have a few different capabilities, by far the most common use for dynamic casting is for converting base-class pointers into derived-class pointers. This process is called **downcasting**.
```cpp
int main() {
	Base *b = getObject(true);
        Derived *d = dynamic_cast<Derived*>(b); // use dynamic cast to convert Base pointer into Derived pointer
        std::cout << "The name of the Derived is: " << d->getName() << '\n';
	delete b;
	return 0;
}
```
####`dynamic_cast` failure
What if b wasn’t pointing to a Derived object?
If a `dynamic_cast` fails, the result of the conversion will be a null pointer.
```cpp
int main() {
	Base *b = getObject(true);
	Derived *d = dynamic_cast<Derived*>(b); // use dynamic cast to convert Base pointer into Derived pointer
	if (d) // make sure d is non-null
		std::cout << "The name of the Derived is: " << d->getName() << '\n';
	delete b;
	return 0;
}
```
>Rule
>Always ensure your dynamic casts actually succeeded by checking for a null pointer result.

Note that because `dynamic_cast` does some consistency checking at runtime (to ensure the conversion can be made), use of `dynamic_cast` does incur a performance penalty.
Also note that there are several cases where downcasting using `dynamic_cast` will not work:
1) With protected or private inheritance.
2) For classes that do not declare or inherit any virtual functions (and thus don’t have a virtual table).
3) In certain cases involving virtual base classes.

####Downcasting with `static_cast`
The main difference is that `static_cast` does no runtime type checking to ensure that what you’re doing makes sense. This makes useing `static_cast` faster, but more dangerous. If you cast a Base\* to a Derived\*, it will "succeed" even if the Base pointer isn't pointing to a Derived object. This will result in undefined behavior when you try to access the resulting Derived pointer (that is actually pointing to a Base object).

####`dynamic_cast` and references
Although all of the above examples show dynamic casting of pointers (which is more common), `dynamic_cast` can also be used with references. This works analogously to how `dynamic_cast` works with pointers.

####`dynamic_cast` vs `static_cast`
New programmers are sometimes confused about when to use `static_cast` vs `dynamic_cast`. The answer is quite simple: use `static_cast` unless you’re downcasting, in which case `dynamic_cast` is usually a better choice. However, you should also consider avoiding casting altogether and just using virtual functions.

####Downcasting vs virtual functions
In general, using a virtual function should be preferred over downcasting. However, there are times when downcasting is the better choice:
- When you can not modify the base class to add a virtual function (e.g. because the base class is part of the standard library)
- When you need access to something that is derived-class specific (e.g. an access function that only exists in the derived class).
- When adding a virtual function to your base class doesn't make sense. Using a pure virtual function may be an option here if you don't need to instantiate the base class.

####A warning about `dyanmic_cast` and RTTI
Run-time type information (RTTI) is a feature of C++ that exposes information about an object’s data type at runtime. This capability is leveraged by dynamic_cast. Because RTTI has a pretty significant space performance cost, some compilers allow you to turn RTTI off as an optimization. Needless to say, if you do this, dynamic_cast won’t function correctly.
