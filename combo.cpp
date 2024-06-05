struct Combo {
    vector<ll> facs, invfacs;
    int N;
    long long MOD = 1e9+7;

    Combo(int N) {
        this->N=N;
        facs.assign(N+1,0);
        invfacs.assign(N+1,0);
        facs[0] = 1;
        for (int i = 1; i <= N; i++) {
            facs[i] = (facs[i-1]*i)%MOD;
        }
        invfacs[N] = binpow(facs[N],MOD-2);
        for (int i = N-1; i >= 0; i--) {
            invfacs[i] = (invfacs[i+1]*(i+1))%MOD;
        }
    }

    long long choose(int n, int k) {
        if (n<0||k<0||n<k) return 0LL;
        long long denInv = (invfacs[k]*invfacs[n-k])%MOD;
        long long ans = (facs[n]*denInv)%MOD;
        return ans;
    }

    long long binpow(long long x, long long y) {
        long long ans = 1;
        x %= MOD;
        while (y > 0) {
            if (y%2==1) ans = (ans*x)%MOD;
            y /= 2;
            x = (x*x)%MOD;
        }
        return ans;
    }
};