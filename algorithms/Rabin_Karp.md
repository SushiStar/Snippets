# String Hash
Hash a string:
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

# Robin-Karp
https://cp-algorithms.com/string/rabin-karp.html

Problem: Given two strings - a pattern *s* and a text *t*, determine if the pattern
appears in the text and if it does, enumerate all its occurrences in $O(|s| + |t|)$ time.

Algorithm: Calculate the hash for the pattern *s*. Calculate hash values for all the
prefixes of the text *t*. Now we can compare a substring of length $|s|$ with *s* in
constant time using the claculated hashes. So, compare each substring of length $|s|$ with
the pattern. This will take a total of $O(|t|)$ time. Hence the final complexity is
$O(|t|+|s|)$: $O(|s|)$ is required for calculating the hash of the pattern and $O(|t|)$
for comparing eacch substring of length $|s|$ with the pattern.

```cpp
std::vector<int> rabin_karp(const std::string& s, const std::string& t) {
    const int p = 31;
    const int mod = 1e9+9;
    int len_s = s.size();
    int len_t = t.size();

    std::vector<long long> p_pow(std::max(len_s, len_t));
    p_pow[0] = 1;
    for(int i = 1; i < (int)p_pow.size(); ++i) {
        p_pow[i] = (p_pow[i-1]*p)%m;
    }

    std::vector<long long> hash_t(len_t + 1, 0);
    for(int i = 0;i < len_t; ++i) {
        hash_t[i+1] = (hash_t[i] + (t[i] - 'a'+1) * p_pow[i])%mod;
    }

    long long hash_s = 0;
    for(int i = 0;i < len_s; ++i) {
        hash_s = (hash_s + (s[i] - 'a' + 1) * p_pow[i])%mod
    }

    std::vector<int> occurrences;
    for(int i =0 ; i < i+len_s-1 < len_t; ++i){
        long long cur_hash = (hash_t[i+len_s] + mod - hash_t[i]) %mod;
        cur_hash = (cur_hash*p_pow[len_s - i -1])%mod;
        if(cur_hash == hash_s*p_pow[i]%mod) {
            occurrences.push_back(i);
        }
    }
    return occurrences;
}
```