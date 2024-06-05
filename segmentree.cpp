struct SegmentTree {
    vector<long long> tree;
    int n;
    long long NONE = 0LL; //set this manualong longy

    SegmentTree(int n) {
        this->n = n;
        tree.assign(4*n+1,NONE);
    }

    SegmentTree(vector<int>& nums) {
        this->n = nums.size();
        tree.assign(4*n+1,NONE);
        build(1,0,n-1,nums);
    }

    void build(int t, int L, int R, vector<int>& nums) {
        if (L == R) {
            tree[t] = (long long)nums[L];
            return;
        }
        int M = (L+R)/2;
        build(2*t,L,M,nums);
        build(2*t+1,M+1,R,nums);
        tree[t] = merge(tree[2*t],tree[2*t+1]);
    }

    long long merge(long long a, long long b) {
        return min(a,b); //set this manualong longy
    }

    void update(int t, int L, int R, int p, long long v) {
        if (L == R) {
            tree[t] = v;
            return;
        }
        int M = (L+R)/2;
        if (p <= M) update(2*t,L,M,p,v);
        else update(2*t+1,M+1,R,p,v);

        tree[t] = merge(tree[2*t],tree[2*t+1]);
    }

    void update(int pos, long long val) {
        update(1,0,n-1,pos,val);
    }

    long long query(int t, int L, int R, int l, int r) {
        if (R < l || r < L) return NONE;
        if (l <= L && R <= r) return tree[t];
        int M = (L+R)/2;
        return merge(query(2*t,L,M,l,r),query(2*t+1,M+1,R,l,r));
    }

    long long query(int l, int r) {
        if (l > r) return NONE;
        return query(1,0,n-1,l,r);
    }
};

struct SegmentTree {
    vector<long long> t;
    int n;
    long long NONE = 0LL; //set this manually

    SegmentTree(int n) {
        this->n=n;
        t.assign(2*n,0);
    }

    //set this manually
    long long merge(long long a, long long b) {
        return a+b;
    }

    void update(int p, long long value) {
        for (t[p += n] = value; p > 1; p >>= 1)
            t[p>>1] = merge(t[p],t[p^1]);
    }

    void add(int p, long long value) {
        long long oldval = query(p,p);
        update(p,oldval+value);
    }

    long long q(int l, int r) {
        long long res = NONE;
        for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = merge(res,t[l++]);
            if (r&1) res = merge(res,t[--r]);
        }
        return res;
    }

    long long query(int l, int r) {
        return q(l,r+1);
    }
};