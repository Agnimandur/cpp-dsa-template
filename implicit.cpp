struct Implicit {
    long long L;
    long long R;
    long long val;
    const long long NONE = 0LL; //set this manually
    Implicit *left, *right;

    Implicit(long long L, long long R) {
        this->L=L;
        this->R=R;
        val = 0;
        left = nullptr;
        right = nullptr;
    }

    //set this manually
    long long merge(long long a, long long b) {
        return (a+b);
    }

    void build() {
        if (left==nullptr && L < R) {
            long long m = (L+R)/2;
            left = new Implicit(L,m);
            right = new Implicit(m+1,R);
        }
    }

    void add(long long i, long long x) {
        long long cur = query(i,i);
        update(i,x+cur);
    }

    void update(long long i, long long x) {
        if (L==R) {
            val = x;
            return;
        }
        build();
        //propagate
        if (i <= left->R)
            left->update(i,x);
        else
            right->update(i,x);
        val = merge(left->val,right->val);
    }

    long long query(long long lq, long long rq) {
        if (lq <= L && R <= rq) {
            return val;
        } else if (max(lq,L) > min(rq,R)) {
            return NONE;
        } else {
            build();
            return merge(left->query(lq,rq),right->query(lq,rq));
        }
    }
};