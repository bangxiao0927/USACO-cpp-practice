#include <fstream>
#include <vector>
using namespace std;

int main() {
    ifstream cin("sequence.in");
    ofstream cout("sequence.out");

    int T;
    cin >> T;
    while (T--) {
        long long M;
        int K;
        cin >> M >> K;

        vector<long long> a;

        // Step 1: build basis: for each bit i of K, add one number with popcount = 1<<i
        long long S = 0;
        for (int i = 0; i < 31; i++) {
            if (K & (1<<i)) {
                // create number with popcount = i+1
                // simplest: lowest (i+1) bits set: (1<<(i+1)) - 1
                long long x = (1LL << (i+1)) - 1;
                a.push_back(x);
                S += x;
            }
        }

        if (S > M) {
            cout << -1 << "\n";
            continue;
        }

        long long R = M - S;  // remaining sum

        if (R > 0) a.push_back(R);  // popcount(R) may break XOR

        // Fix popcount XOR:
        int xr = 0;
        for (long long v : a) xr ^= __builtin_popcountll(v);

        if (xr != K) {
            int diff = xr ^ K; // needed popcount adjustment

            // create one number with popcount=diff
            if (diff <= 60) {
                long long y = (1LL << diff) - 1;
                a.push_back(y);
            } else {
                cout << -1 << "\n";
                continue;
            }
        }

        if ((int)a.size() > 100) {
            cout << -1 << "\n";
            continue;
        }

        cout << a.size() << "\n";
        for (long long v : a) cout << v << " ";
        cout << "\n";
    }
    return 0;
}
