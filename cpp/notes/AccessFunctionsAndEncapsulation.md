# Access functions and encapsulation
### Encapsulation
In object-oriented programming, **Encapsulation** (also called **information hiding**) is the process of keeping the details about how an object is implemented hidden away from users of the object without having to understand how it is implemented.
In C++, we implement encapsulation via access specifiers.

#### Benefit: encapsulated classes are easier to use and reduce the complexity of your programs.
#### Benefit: encapsulated classes are easier to change
#### Benefit: encapsulated classes are easier to debug

### Access functions
An access functions is a short public function whose job is to retrieve or change the value of a private member variable. Access functions are typically come in two flavors: getters and setters. Getters (also sometimes called accessors) are functions that return the value of a private member variable. Setters (also called mutators) are functions that set the value of a private member variable.

### Access functions concerns
As you create your classes, consider the following:

- If nobody outside your class needs to access a member, don't provide access functions for that member.
- If someone outside your class needs to access a member, think about whether you can expose a behavior or action instead.
- If you can't, consider whether you can provide only a getter.
