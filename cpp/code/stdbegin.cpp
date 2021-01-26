#include <iostream>
#include <vector>

#include <algorithm>

using namespace std;
int main() {
   vector<int> v{1,2,3};

   reverse(v.begin(), v.end());
   for (auto a:v) {
       cout << a << endl;
   }

   return 0;
}
