#include <vector>
#include <string>
#include <fstream>

// solution.cpp
using namespace std;

using ll  = long long;      // C++11 type alias
using ull = unsigned long long;

vector<ull> solve(ll M, int K) {
    // Even M cannot produce odd XOR of popcounts
    if (M % 2 == 0 && K % 2 == 1) return {};

    vector<ull> powers;
    ll cur = M;
    for (int b = 30; b >= 0; --b) {
        ull p = 1ULL << b;
        if (cur >= (ll)p) {
            powers.push_back(p);
            cur -= p;
        }
    }

    if (cur == 0) {                     // M is sum of distinct powers of two
        if (K == 0) return powers;
        if (K == 1 && !powers.empty()) {
            ull p = powers.back(); powers.pop_back();
            powers.push_back(p - 1);
            powers.push_back(1);
            return powers;
        }
        return {};
    }

    // Split the remainder cur into x, y, z such that
    // popcount(y) ^ popcount(z) == K
    ull x = cur, y = 0, z = 0;
    int need = K;
    for (int b = 30; b >= 0; --b) {
        if (need & (1 << b)) {
            ull mask = 1ULL << b;
            if (x >= mask) { x -= mask; y += mask; }
            else           { z += mask; }
        }
    }

    vector<ull> res = powers;
    if (x) res.push_back(x);
    if (y) res.push_back(y);
    if (z) res.push_back(z);
    if (res.size() > 100) return {};
    return res;
}

int main() {
    ifstream cin("sequence.in");
    ofstream cout("sequence.out");

    int T;
    cin >> T;
    for (int t = 0; t < T; ++t) {
        ll M; int K;
        cin >> M >> K;

        auto ans = solve(M, K);
        if (ans.empty()) {
            cout << "-1\n";
            continue;
        }
        cout << ans.size() << '\n';
        for (size_t i = 0; i < ans.size(); ++i) {
            if (i) cout << ' ';
            cout << ans[i];
        }
        cout << '\n';
    }
    return 0;
}