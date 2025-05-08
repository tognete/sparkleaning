#include <bits/stdc++.h>
using namespace std;
constexpr int fib(int n){return n<2?n:fib(n-1)+fib(n-2);}              // CT‑recursion
template<class T> concept Num = integral<T> || floating_point<T>;      // concepts
int main(){
    static_assert(fib(10)==55);                                         // metaprogram check
    auto tic = chrono::high_resolution_clock::now();                    // timing
    vector<int> v(10); iota(begin(v), end(v), 1);                       // fill 1‑10
    ranges::shuffle(v, mt19937{random_device{}()});                     // random permute
    unique_ptr<long long> sum = make_unique<long long>(accumulate(v.begin(), v.end(), 0LL)); // RAII ptr
    jthread worker([&]{ *sum = reduce(execution::par, v.begin(), v.end()); }); // parallel sum
    worker.join();                                                      // sync
    cout << "nums: "; for (int x : v) cout << x << ' '; cout << '\n';   // range‑based for
    cout << "parallel sum = " << *sum << '\n';                          // lambda result
    cout << "fib(10) = " << fib(10) << '\n';                            // constexpr value
    auto toc = chrono::high_resolution_clock::now();                    // stop timer
    cout << "elapsed(ms) = "                                           //
         << chrono::duration<double,milli>(toc - tic).count() << '\n';
    if (is_sorted(v.begin(), v.end())) cout << "sorted!\n"; else cout << "not sorted\n";
    ranges::sort(v); cout << "now sorted? " << boolalpha << ranges::is_sorted(v) << '\n';
    cout << "mean = " << accumulate(v.begin(), v.end(), 0)/static_cast<double>(v.size()) << '\n';
}
