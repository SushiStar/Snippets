# Pointers and refernces to the base class of derived objects
### Use for pointers and references to base classes

1. Lets' say you wanted to write a function that printed an animal's name and sound. Without using a pointer to the base class, you'd have to write it using overloaded functions, like this:
```cpp
void report(const Cat &cat) {
	printf("%s says %s\n", cat.getName(), cat.speak());
}
void report(const Dog &dog) {
	printf("%s says %s\n", dog.getName(), dog.speak());
}
```
However, because Cat and Dog are derived from Animal, Cat and Dog have an Animal part. There fore it makes sense that we should be able to do something like this:
```cpp
void report(const Animal &rAnimal) {
	printf("%s says %s\n", rAnimal.getName(), rAnimal.speak());
}
```
The problem is, of course, that because rAnimal is an Animal reference, `rAnimal.speak()` will call `Animal::speak()` instead of the derived version of `speak()`.

2. Let's say you had 3 cats and 3 dogs that you wanted to keep in an array for easy access. Because arrays can only hold objects of one type, without a pointer or reference to a base class, you'd have to create a different array for each derived type.

Although both of these techniques could save us a lot of time and energy, they have the same problem. The pointer or reference to the base class calls the base version of the function rather than the derived version.

