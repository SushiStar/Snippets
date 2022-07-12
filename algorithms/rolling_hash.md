# Rolling Hash
Rolling hash a string: 
https://cp-algorithms.com/string/string-hashing.html

```cpp
long long computeHash(const std::string& s) {
    const int p = 31;
    const int mod=1e9+7;
    long long pow_p = 31;
    long long hash_value = 0;

    for(char c : s) {
        hash_value = (hash_value + (c - 'a'+1)*pow_p)%mod;
        pow_p = (pow_p * p)%mod;
    }

    return  hash_value;
}
```
