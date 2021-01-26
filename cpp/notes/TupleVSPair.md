std::tuple can never be by standard-layout (at least, it's not required to be by the standard). Every `std::pair<T, Y>` is standard-layout if both T and Y are standard-layout.
It's a bit easier to get the contents of a pair than a tuple. You have to use a function call in the tuple case, while the pair case is just a member field.

Because `std::pair` is defined with member variables, its size cannot be optimized using empty base class optimization (first and second must occupy distinct addresses, even if one or both is an empty class).
This exacerbated by whatever alignment requirements second\_type has, so in the worst case the resulting `std::pair` will be basically twice the size it needs to be.

`std::tuple` only allows access through helper functions, so it's possible for it to derive from either type if one or the other is empty, saving on the overhead.
