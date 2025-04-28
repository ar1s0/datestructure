#include <bits/stdc++.h>
using namespace std;
using LL = long long;

// 全局变量
int N = 1000;  // 默认大小
int MOD = 1000000007;  // 默认模数
vector<LL> fac;    // factorial array
vector<LL> inv;    // inverse array
vector<LL> facInv; // factorial inverse array

// 初始化函数
void init() {
    fac.resize(N);
    inv.resize(N);
    facInv.resize(N);
    
    fac[0] = facInv[0] = 1;
    inv[1] = 1;
    for (int i = 1; i < N; i++) {
        fac[i] = fac[i - 1] * i % MOD;
        if (i > 1)
            inv[i] = (MOD - MOD / i) * inv[MOD % i] % MOD;
        facInv[i] = facInv[i - 1] * inv[i] % MOD;
    }
}

// 快速幂计算
LL qpow(LL a, LL n, LL mod) {
    LL ans = 1;
    while (n) {
        if (n & 1) ans = ans * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return ans;
}

// 使用费马小定理计算逆元
LL fermatInv(LL a, LL mod) {
    return qpow(a, mod - 2, mod);  // a^(p-2) mod p
}

// 基础组合数计算
LL C(LL n, LL k) {
    if (k < 0 || k > n) return 0;
    if (n >= N) return 0;
    return fac[n] * facInv[k] % MOD * facInv[n - k] % MOD;
}

// 基础组合数计算（使用费马小定理）
LL CFermat(LL n, LL k) {
    if (k < 0 || k > n) return 0;
    if (n >= MOD) return 0;
    
    LL up = fac[n];
    LL down = (fac[k] * fac[n - k]) % MOD;
    return up * fermatInv(down, MOD) % MOD;
}

// Lucas定理计算
LL Lucas(LL n, LL m) {
    if (m == 0) return 1;
    return C(n % MOD, m % MOD) * Lucas(n / MOD, m / MOD) % MOD;
}

// 扩展Lucas辅助函数
LL exgcd(LL a, LL b, LL &x, LL &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    LL d = exgcd(b, a % b, y, x);
    y -= (a / b) * x;
    return d;
}

LL calc(LL n, LL p) {
    LL res = 0;
    while (n) {
        res += n / p;
        n /= p;
    }
    return res;
}

// 扩展Lucas组合数计算
LL CombinationModP(LL n, LL m, LL p) {
    if (m > n) return 0;
    
    LL s = calc(n, p) - calc(m, p) - calc(n - m, p);
    if (s > 0) return 0;

    int oldMOD = MOD;
    int oldN = N;
    
    MOD = p;
    N = p + 1;
    init();
    
    LL res = 1;
    while (n) {
        res = res * C(n % p, m % p) % p;
        n /= p;
        m /= p;
    }
    
    // 恢复原始值
    MOD = oldMOD;
    N = oldN;
    init();
    
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    // 初始化
    init();

    // 测试样例
    cout << "C(5,2) = " << C(5, 2) << '\n';
    cout << "C_Fermat(5,2) = " << CFermat(5, 2) << '\n';  // 使用费马小定理的方法
    cout << "Lucas(10,3) = " << Lucas(10, 3) << '\n';
    cout << "CombinationModP(10,3,7) = " << CombinationModP(10, 3, 7) << '\n';

    return 0;
}