/*
 * Container class
 * The word virtual means "may be refined later in a class derived from this one.
 * A class called pure virtual function is called abstract class.
 */
#include <memory> // unique_ptr
#include <vector>
#include <iostream>

class Shape;
class Kind;
using namespace std;

namespace WD{
    
    class Container{
    public:
        virtual double& operator[](int) = 0;
        virtual int size()const = 0;
        virtual ~Container(){}
    };


    /*
     * unique pointer
     */
    unique_ptr<Shape> read_shape(istream& is)      // read shape descriprions from input stream
    {   
        switch(k){
            case Kind::circle:
                return unique_ptr<Shape> new(Circle(p,r));
        }
    }

    void usr(){
        std::vector<unique_ptr<Shape>> v;
        while(cin){
            v.push_back(read_shape (cin));
        }
        draw_all(v);
        rotate_all(v,45);
    } // all shapes implicitly destroyed

    // when a class is a resource handle, default copy would leave a copy of a reference 
    // to the same elements as the original.
    // Copying of an object of a class is defined by two members: a copy constructor and a copy assignment
    class Vector {
    private:
        double *elem; // elem points to an array of sz doubles
        int sz;
    public:
        Vector(int s);  // constructor: establish invariant, acquire resources
        ~Vector(){delete[] elem;}   // destructor: release resources

        Vector(const Vector& a);    // copy constructor
        Vector& operator=(const Vector& a);     // copy assignment

        Vector(Vector&& a);     // move constructor
        Vector& operator=(Vector&& a);      // move assignment

        double& operator[](int i);
        const double& operator[](int i) const;

        int size() const;
    }; 

    // a copy constructor and a copy assignment for a class X are typically 
    // declared to take an argument of type const X& 
    Vector::Vector(const Vector& a)     // copy constructor
        :elem(new double[a.sz]),sz(a.sz){
        for(int i = 0; i!=z; ++i){
            elem[i] = a.elem[i];
        }    
    }

    Vector& Vector::operator=(const Vector& a){     // copy assignment
        double *p = new double[a.sz];
        for(int i=0; i!=a.sz; ++i){
            p[i] = a.elem[i];
        }
        delete[] elem;      // delete old elements
        elem = p;
        sz = a.sz;
        return *this;
    }

    /*
     * && means 'rvalue reference' and is a reference to which we can bind an rvalue,
     * rvalue is -to a first approximation - a value that you can't assign to, such as
     * an integer returned by a function call, and an rvalue reference is a reference
     * to something that nobody else can assign to.
     */
    Vector::Vector(Vector&& a): elem(a.elem), sz(a.sz){     // grab the elements from a
        a.elem = nullptr;       // now a has no elements
        a.sz = 0;
    }

    /*
     * delete the default copy and move operations.
     * The =delete mechanism is general, that is, it can be used to suppress any opreation.
     */
    class Shape{
    public:
        Shape(const Shape&) = delete;           // no copy operations
        Shape& operator=(const Shape&)=delete;

        Shape(Shape&&) = delete;                // no move operations
        Shape& operator=(Shape&&)=delete;

        ~Shape();
        // ...
    };
    

}
