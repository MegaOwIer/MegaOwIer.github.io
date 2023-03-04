#include <bits/stdc++.h>
using namespace std;

const vector<int> B {2, 3, 4, 5, 0, 1}, invB {4, 5, 0, 1, 2, 3};
const vector<int> C {1, 5, 0, 4, 3, 2}, invC {2, 0, 5, 4, 3, 1};

string solve(const string &s, const string &t) {
    vector<int> perm(6);
    iota(perm.begin(), perm.end(), 0);

    function<void(const vector<int> &)> mult = [&] (const vector<int> &p) {
        vector<int> tmp;
        for(int cur : perm) {
            tmp.push_back(p[cur]);
        }
        perm = move(tmp);
    };

    for(char c : s) {
        if(c == 'a') {  // a = bc
            mult(B), mult(C);
        } else if(c == 'b') {
            mult(B);
        } else {
            mult(C);
        }
    }

    for(char c : t) {
        if(c == 'a') {  // a^{-1} = c^{-1}b^{-1}
            mult(invC), mult(invB);
        } else if(c == 'b') {
            mult(invB);
        } else {
            mult(invC);
        }
    }

    for(size_t i = 0; i < 6; i++) {
        if(perm[i] != i) {
            return "no";
        }
    }
    return "yes";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int _;
    cin >> _;
    while(_--) {
        string s, t;
        cin >> s >> t;
        reverse(t.begin(), t.end());
        cout << solve(s, t) << "\n";
    }

    return 0;
}
