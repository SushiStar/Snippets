
template <typename Contained>

struct S {
    S = default;
    S(contained &&c_) : contained(std::move(c_)){};
    S(const Contained &c_) : contained(c_) {};

    const Contained &get() const {
        return contained;
    }

    operator Contained() const {
        return contained;
    }

    private:
    Contained contained;
};

void func(const S<int>&);

void other_func(int);

int main() {
    func(1);
    other_func(S<int>{});
}
