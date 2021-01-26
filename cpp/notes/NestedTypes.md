#Nested types in classes
###Nested types
Unlike functions, which can't be nested inside each other, in C++, types can be defiend (nested) inside of a class.
You simply define the type inside the class, under the appropriate access specifier.
```cpp
class Fruit {
public:
	enum FruitType {
		APPLE,
		BANANA,
		CHERRY
	};
private:
	FruitType: m_type;
	int m_percentageEaten = 0;
public:
	Fruit(FruitType type) : m_type(type){}
	FruitType getType() {return m_type;}
	int getPercentageEate() {reutrn m_percentageEaten;}
};
int main() {
	// ...
}
```
First, note that FruitType is now defined inside the class. Second, note that we've defined it under the public access specifier, so the type definition can be accessed from outside the class.
Classes essentially act as namespace for any nested types.

###Other types can be nested too
Like any normal member of a class, nested classes have the same access to members of the enclosing class that the enclosing class does. However, the nested class does not have any special access to the `*this` pointer of the enclosing class.
