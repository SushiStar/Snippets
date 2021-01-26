#Destructors
A destructor is another special kind of class member function that is executed when an object of that class is destroyed. Whereas constructors are designed to initialize a class, destructors are designed to help clean up.

###Destructor naming
1. The destructor must have the same name as the class, preceded by a tilde (~).
2. The destructor can not take arguments.
3. The destructor has no return type.

Note that rule 2 implies that only one destructor may exist per class, as there is no way to overload destructors since they can not be differentiated from each other based on arguments.

###Constructor and destructor timing 
Global variabls are constructed before `main()` and destroyed after `main()`.
###RAII
RAII(Resource Acquisition Is Initialization) is a programming technique whereby resource use is tied to the lifetime of objects with an automatic duration. In C++, RAII is implemented via classes with constructors and destructors. A resource (such as memory, a file or datebase handle, etc...) is typically acquired in the object's constructor (though it can be acquired after the object is created if that makes sense). That resource can then be used while the object is alive. The resource is released in the destructor, when the object is destroyed. The primary advantage of RAII is that it helps prevent resource leaks (e.g. memory not be deallocated) as all resource-holding objects are cleaned up automatically.

Under the RAII paradigm, objects holding resources should not be dynamically allocated. This is because destructors are only called when an object is destoryed. For objects allocated on stack, this happens automatically when the object goes out of scope, so there's no need to worry about a resource eventually getting cleaned up. However, for dynamically allocated objects, teh user is responsible for deletion -- if the user forgets to do that, then the destructor will not be called, and the memory for both the class object and the resource being managed will be leaked.
>Dynamic memory is acquired on initialization, and cleaned up automatically on destruction.

###A warning about the `exit()` function
Note that if you use the `exit()` function, your program will terminate and no destructors will be called. Be wary if you're relying on your destructors to do necessary cleanup work (e.g. write something to a log file or database before exiting).
