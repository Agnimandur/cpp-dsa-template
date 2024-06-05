struct MinMaxLazyST {
    vector<long long> tree;
    vector<long long> lazy;
    int N;
    long long NONE;
 
    MinMaxLazyST(int n) {
        N = n;
        NONE = -1e18; //set this manually
        tree.assign(2*N,NONE);
        lazy.assign(2*N,0);
    }
 
    void add(int L, int R, long long val) {
        add(0,0,N-1,L,R,val);
    }
 
    void add(int n, int L, int R, int uL, int uR, long long val) {
        push(n,L,R);
        if (uL <= L && R <= uR) {
            //fully contained
            lazy[n] += val;
            push(n,L,R);
            return;
        } else if (L>uR || R<uL || L==R) {
            //not contained at all or leaf
            return;
        }
        int mid = (L+R)/2;
        add(n+1,L,mid,uL,uR,val); 
        add(n+2*(mid-L+1),mid+1,R,uL,uR,val);
        tree[n] = merge(tree[n+1],tree[n+2*(mid-L+1)]);
    }
 
    long long query(int L, int R) {
        return query(0,0,N-1,L,R);
    }
 
    long long query(int n, int L, int R, int Lq, int Rq) {
        push(n,L,R);
        if (Lq <= L && R <= Rq) {
            return tree[n];
        } else if (R < Lq || Rq < L) {
            return NONE;
        } else {
            int mid = (L+R)/2;
            return merge(query(n+1,L,mid,Lq,Rq),query(n+2*(mid-L+1),mid+1,R,Lq,Rq));
        }
    }
 
    void push(int n, int L, int R) {
        tree[n] += lazy[n];
 
        if (L < R) {
            int mid = (L+R)/2;
            lazy[n+1] += lazy[n];
            lazy[n+2*(mid-L+1)] += lazy[n];
        }
        lazy[n] = 0;
    }

    //set this manually
    long long merge(long long a, long long b) {
        //return min(a,b); //min,NONE=INF
        return max(a,b); //max,NONE=NEG INF
    }
};