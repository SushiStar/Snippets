# Bitwise Hacks for Competitive Programming

####How to set a bit at nth position in number 'num':
It can be done using 'OR' operator (|).
* First we left shift '1' to n position via (1 << n)
* Then, use 'OR' operator to set bit at that position.
```cpp
void set (int &num, int pos) {
  num |= (1<<pos);
}
```

####How to unset/clear a bit at n'th position in the number 'num':
* First we left shift '1' to n position via (1 << n) then we use bitwise NOT operator '~' to unset this shifted '1'.
* Now after clearing this left shifted '1', we will 'AND' with the number num.
```cpp
void unset (int &num, int pos) {
  num &= (~(1 << pos));
}
```

####Toggling a bit at nth position:
* Properties of 'XOR' operator:
  * 1^1 = 0
  * 0^0 = 0
  * 1^0 = 1
  * 0^1 = 1
* If two bits are different then 'XOR' operator returns a set bit(1) else it returns an unset bit(0).
```cpp
void toggle(int &num, int pos) {
  num ^= (1 << pos);
}
```

####Checking if a bit at nth position is set or unset:
```cpp
bool at_position(int num, int pos){
  bool bit = num & (1 << pos);
  return bit;
}
```
####Two's complement
`int twos_complement = -num`

####Stripping off the lowest set bit:
`X = X & (X-1)`
Let X = 1100, (X-1) inverts all the bits till it encounter lowest set '1' and it also invert that lowest set'1'.
X-1 becomes 1011. After 'AND' X with X-1 we get lowest set bit stripped.
```cpp
void strip_last_set_bit(int &num) {
  num = num & (num-1);
}
```

####Getting lowest set bit of number:
Let X = 00101100, so ~X will be '11010011' and 2's complement will be (~X +1 or -X). So if will 'AND' original number 'X' with its two's complement which is '-X', we get lowest set bit.
```cpp
int lowest_set_bit(int num) {
  int ret = num & (-num);
  return ret;
}
```
