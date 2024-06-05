struct HashTemplate {
    long long MOD1;
    long long MOD2;
    long long BASE;
    vector<int> arr;
    vector<long long> hash1;
    vector<long long> hash2;
    int N;

    long long inv1;
    long long inv2;

    HashTemplate(vector<int> input) {
        MOD1 = 1999999927LL;
        MOD2 = 1999999973LL;
        BASE = generateRNG(1e9+1,MOD1-20);
        N = sz(input);
        arr = input;
        hash1.assign(N+1,0);
        hash2.assign(N+1,0);
        for (int i = 0; i < N; i++) {
            hash1[i+1] = (hash1[i]+power(BASE,i,MOD1)*arr[i])%MOD1;
            hash2[i+1] = (hash2[i]+power(BASE,i,MOD2)*arr[i])%MOD2;
        }

        inv1 = power(BASE,MOD1-2,MOD1);
        inv2 = power(BASE,MOD2-2,MOD2);
    }

    //compute the sub-array hash of [L..R] inclusive
    long long computeHash(int L, int R) {
        long long h1 = ((hash1[R+1]-hash1[L]+MOD1)*power(inv1,L,MOD1))%MOD1;
        long long h2 = ((hash2[R+1]-hash2[L]+MOD2)*power(inv2,L,MOD2))%MOD2;
        return h1*MOD2+h2;
    }

    long long generateRNG(long long L, long long R) {
        mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
        return uniform_int_distribution<long long>(L,R)(rng);
    }

    long long power(long long x, long long y, long long m) {
        long long ans = 1LL;
        x %= m;
        while (y > 0) {
            if (y%2==1)
                ans = (ans*x)%m;
            y /= 2;
            x = (x*x)%m;
        }
        return ans;
    }
};