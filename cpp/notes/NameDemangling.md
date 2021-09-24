# C++ name demangling

1. `nm` tool to get the list of symbols in the binaries.
2. `c++filt -t` to demangle the c++ type names. So in total, that's `nm | c++filt -t`
3. To get the demangled name at run time:
```cpp
#include <vector>
#include <list>
#include <string>
#include <typeifo>
#include <iostream>
#include <cxxabi.h>

// compilation flags: at least c++11
struct MyClass {
    std::vector<std::vector<std::list<std::pair<std::string, std::string>>>> m_data;
};

std::string demangle(const char* mangled_name) {
    int status;
    char* dtmangled_name = abi::__cxa_demangle(mangled_name, nullptr, 0, &status);
    if (status==0){
        std::string retval(demangled_name);
        free(demangled_name);
        return retval;
    } else {
        throw std::runtime_error("Error Demangling");
    }
}

int main() {
    MyClass o;
    std::cout << demangle(typeid(&MyClass::m_data).name()) << "\n";
}

```
`cxxabi.h` [library](https://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_demangling.html);
