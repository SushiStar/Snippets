#Function template instances
C++ does not compile the template function directly. Instead, at compile time, when the compiler encounters a call to template function ,it replicates the template function and replaces the template type parameters with actual types. The function with actual types is called a **function template instance**.

####operators, function calls, and function templates
When the compiler compiles the template instance, it compiles it just like a normal function. In a normal function, any operators or function calls that you use with your types must be defined, or you will get a compile error. Any operators or function calls in your template must be defined for any types the function template is instantiated for.
