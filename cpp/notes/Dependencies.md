# Dependencies
A **dependency** occurs when one object invokes another object's functionality in order to accomplish some specific task. This is a weaker relationship than an association, but still, any change to object being dependend upon may berak functionality in the (dependent) caller.

```cpp
#include <iostream>
class Point {
private:
	double m_x, m_y, m_z;
public:
	Point(double x=0.0, double y=0.0, double z=0.0): m_x(x), m_y(y), m_z(z){}
	friend std::ostream& operator<<(std::ostream &out, const Point &point);
};
```
In the above code, Point isn't directly related to std::cout, but it has a dependency on std::cout since operator << uses std::cout to print the Point to the console.
#### Dependencies vs Association in C++
In C++, associations are relationship between two classes at the class level. That is, one class keeps a direct or indirect "link" to the associated class as a member.
Dependencies typically are not represented at the class level -- that is, the object being depended on is not linked as a member. Rather, the object being depended on is typically instantiated as needed (like opening a file to write data to), or passed into a function as a parameter;
