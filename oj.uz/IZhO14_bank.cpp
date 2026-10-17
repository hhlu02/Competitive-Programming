#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

int main() {
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<int> a(n); for (auto &x : a) cin >> x;
    vector<int> b(m); for (auto &x : b) cin >> x;
    vector<int> pref(n);
    for (int i = 0; i < n; i++) {
        pref[i] = pref[(i ? i - 1 : 0)] + a[i];
    }
    vector<bool> dp(1 << m);
    dp[0] = 1;
    for (int i = 0; i < (1 << m); i++) {
        if (!dp[i]) continue;
        int sum = 0;
        for (int j = 0; j < m; j++) {
            if ((1 << j) & i) {
                sum += b[j];
            }
        }
        if (sum == pref.back()) {
            cout << "YES\n";
            return 0;
        }
        if (sum > pref.back()) continue;
        int cur_pos = upper_bound(pref.begin(), pref.end(), sum) - pref.begin();
        int cur_need = pref[cur_pos] - sum;
        for (int j = 0; j < m; j++) {
            if ((1 << j) & i) continue;
            if (b[j] <= cur_need) {
                dp[i | (1 << j)] = 1;
            }
        }
    }
    cout << "NO\n";
}

/*
dp[mask] = is the current mask reachable
transition is if its reachable then try to check next masks
*/
