

template <typename A, typename B>
struct Pair {
    A first;
    B second;

    Pair() {}

    Pair(A a, B b) : first(a), second(b) {}
};

template <typename A, typename B>
Pair<A, B> make_pair(A a, B b) {
    return Pair<A, B>(a, b);
}
