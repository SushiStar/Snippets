# Julia

## Array

- Index starts from 0
- The  value of an array is its pointer to the memory location.
- Use copy() or deepcopy() function to create a new array.
- Arrays can be of any type, can also be an element of an array(which doesn't require arrays to have the same length).
- Mutating functions: with a <span style="color:red">**!** </span>and the end. And tend to mutate their first argument.
```
    a = [1,6,8]
    b = similar(a) # make an array just a but with undefined values
    copyto!(b,a)   # b changes
```

## Function
- Functions allow overloading (multiple dispatch)
```
    f(x,y) = 2x+y
    f(1,2) # call the function

    function f(x)   # longer definition
        x+2
    end 

    f(x::Int, y::Int) = 3x+2y   # type specified
```
- <: means a subtype of 
- @time f() estimate the run time of this function
- Functions can also feature the optional arguments and multiple return values;
```
function test_function(x,y;z=0) #z is an optional argument
  if z==0
    return x+y,x*y              #Return a tuple
  else
  return x*y*z,x+y+z            #Return a different tuple
                                #whitespace is optional
  end                           #End if statement
end                             #End function definition
```
- Function scoping rules: an inner function can know the variables defined in the same scope as the function. This rule is recursive, leading us to conclusion that the top level scope is global.
- An anonymous function cannot have more than one dispatch.
```
    g = (x,y)->2x+y     # an anonymous definition

    g = (x)-> 3x+3      # this will cover the former definition, g(x) is valid but g(x,y) is not legal any more  
```
## Type Declaration Syntax
- struct definition, <span style="color:red;">**the convention for types is capital letters (WorkshopParticipant)**</span>
```
    mutable sturct Car
        make
        modle
    end 
```
- Initialization
```
    mycar = Car("Toyota", "RAV4")   # string is double quoted
    mycar.modle                     # to access the field of car object
```
- To specify the type of one  field
```
    mutalbe struct StaffMember{T<:Number}
        name::String
        field::Symbol
        age::T
    end
    ter = StaffMember("Terry", :football, 17)
```
- There exist abstract types, these types cannot be instantiated but are used to build the type hierachy.
```
abstrat type Person
end
mutable struct Student <: Person
    name::String
    grade::float64
end
```
- Another version of type is **immutable**. When one uses immutable, the fields of the type cannot be changed. Immutable types are stored closer to the CPU, and have less cost for memory access. Eg:
```
struct Field  # without "mutable" notation
    name
    school
end
```
- Lazy Iterator types 
We can get array from some types via the <span style="color:red;">***collect***</span> function.
```
c = collect(a)
```
- Difference between arrays and tuples: **tuples are immutalbe, tuples are included by '()', whereas array is included by '[]'

