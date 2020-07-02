#Bit Tricks for Competitive Programming
####Clear all bits from LSB (Least Significant Bit) to ith bit
```cpp
mask = ~((1 << i+1)-1);
x &= mask;
```
To clear all bits from LSB to i-th bit, we have to AND x with mask having LSB to i-th bit 0. To obtain such mask, first left shift 1 $i+1$ times. Now if we minus 1 from that, all the bits form 0 to i-1 become 1 and remaining bits become 0. Now we can simply take complement of mask to get all first i bits to 0 and remaning to 1.

####Clear all bits from MSB to i-th bit
```cpp
mask = (1<<i)-1;
x&=mask;
```
To clear all bits from MSB to i-th bit, we have to AND x with mask having MSB to i-th bit 0. To obtain such mask, first left shift 1 i times. Now if we minus 1 from that, all the bits from 0 to i-1 become 1 and remaining bits become 0.

####Divide by 2
`x >>=1`

####Multiple by 2
`x <<= 1`

####Upper case English alphabet to lower case
`ch |= ' ';`

####Lower case English alphabet to upper case
`ch &= '_';`

####Count set bits in integer
```cpp
int countSetBits(int x) {
  int count = 0;
  while (x) {
    x &= (x-1);
    ++count;
  }
  return count;
}
```

####Find log base2 of 32 bit integer
```cpp
int log2 (int x) {
  int res = 0;
  while (x >>= 1) {
    res++;
  }
  return res;
}
```
####Checking if given 32 bit integer is power of 2
```cpp
int isPowerof2(int x) {
  return (x && !(x & x-1));
}
```
All the power of 2 have only single bit set e.g. 16 (00010000). If we minus 1 from this, all the bits from LSB to set bit get toggled, i.e., 16-1 = 15 (00001111). Now if we AND x with (x-1) and the result is 0 then we can say that x is power of 2 otherwise not. We have to take extra care when x = 0.
