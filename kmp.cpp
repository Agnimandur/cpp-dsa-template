struct KMP {
    string S;
    string T;
    KMP(string s, string t) {
        S = s;
        T = t;
    }

    vector<int> run() {
        vector<int> pref = prefix_function(T+"#"+S);
        vector<int> occs;
        int szT = sz(T);
        for (int i = szT+1; i < sz(pref); i++) {
            if (pref[i]==szT) {
                occs.add(i-2*szT);
            }
        }
        return occs;
    }

    vector<int> prefix_function(string s) {
        int n = sz(s);
        vector<int> pi(n);
        for (int i = 1; i < n; i++) {
            int j = pi[i-1];
            while (j > 0 && s[i] != s[j])
                j = pi[j-1];
            if (s[i] == s[j])
                j++;
            pi[i] = j;
        }
        return pi;
    }
};