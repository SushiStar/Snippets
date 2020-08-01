# Copy Control and Resource Management
Ordinarilly, classes that manage resources that do not reside in the class must define the copy-control members. Such classes will need destructors to free the resources allocated by the object.
In order to define these members, we first have to decide what copying an object of our type will mean. In general, we have two choices: We can define the copy operations to make  the class be have like a value or like a pointer.
* Classes that behave like values have their own state. When we copy a valuelike object, the copy and the original are independent of each other.
* Classes taht behave like pointers share state. When we copy objects of such classes, the copy and the original use the same underlying data.

### Classes That Act Like Values
