#Multiple inheritance
Multiple inheritance enables a derived class to inherit members from more than one parent.
```cpp
class Person {
private:
    std::string m_name;
    int m_age;
public:
    Person(std::string name, int age) : m_name(name), m_age(age) {}
    std::string getName() { return m_name; }
    int getAge() { return m_age; }
};

class Employee {
private:
    std::string m_employer;
    double m_wage;
public:
    Employee(std::string employer, double wage) : m_employer(employer), m_wage(wage) {}
    std::string getEmployer() { return m_employer; }
    double getWage() { return m_wage; }
};

// Teacher publicly inherits Person and Employee
class Teacher: public Person, public Employee {
private:
     int m_teachesGrade;
public: Teacher(std::string name, int age, std::string employer, double wage, int teachesGrade)
        : Person(name, age), Employee(employer, wage), m_teachesGrade(teachesGrade) {}
};
```
###Problems with multiple inheritance
First, ambiguity can result when multiple base classes contain a function with the same name.
```cpp
class USBDevice {
private:
    long m_id;
public:
    USBDevice(long id) : m_id(id) {}
    long getID() { return m_id; }
};

class NetworkDevice {
private:
    long m_id;
public:
    NetworkDevice(long id) : m_id(id) {}
    long getID() { return m_id; }
};

class WirelessAdapter: public USBDevice, public NetworkDevice {
public:
    WirelessAdapter(long usbId, long networkId)
        : USBDevice(usbId), NetworkDevice(networkId) {}
};
```
There are actually two `getID()` functions. There's a way to work around this problem: you can explicitly specify which version you meant to call:
```cpp
std::cout << c54G.USBDevice::getID();
```
The potential for naming conflicts increases exponentially as you inherit more classes, and each of these naming conflicts needs to be resolved explicitly

Second, and more serious is the diamond problem. This occurs when a class multiply inherits from two classes which each inherit from a single base class.
```cpp
class PoweredDevice
{
};

class Scanner: public PoweredDevice
{
};

class Printer: public PoweredDevice
{
};

class Copier: public Scanner, public Printer
{
};
```
