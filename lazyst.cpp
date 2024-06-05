//segment tree supporting range sum, range set, and range update operations
struct LazyST {
    int N;
    vector<long long> sum;
    vector<long long> lazy;
    vector<bool> add;
 
    LazyST(vector<long long> arr) {
        N = arr.size();
        sum.assign(2*N,0LL);
        lazy.assign(2*N,0LL);
        add.assign(2*N,true);
 
        build(0,0,N-1,arr);
    }
 
    void update(int l, int r, long long value, bool isAdd) {
        upd(0,0,N-1,l,r,value,isAdd);
    }
 
    long long query(int l, int r) {
        return que(0,0,N-1,l,r);
    }
 
    void build(int t, int L, int R, vector<long long>& arr) {
        if (L == R) {
            sum[t] = arr[L];
        } else {
            int mid = (L+R)/2;
 
            build(t+1,L,mid,arr);
            build(t+2*(mid-L+1),mid+1,R,arr);
            sum[t] = sum[t+1]+sum[t+2*(mid-L+1)];
        }
    }
 
    void apply(int t, int L, int R, long long value, bool isAdd) {
        if(isAdd) sum[t] += value * (R-L+1);
        else sum[t] = value * (R-L+1);
 
        if(isAdd) lazy[t] += value;
        else lazy[t] = value;
        add[t] = (add[t]&isAdd);
    }
 
    void push(int t, int L, int R) {
        if(L != R){
            int mid = (L+R)/2;
            apply(t+1,L,mid,lazy[t],add[t]);
            apply(t+2*(mid-L+1),mid+1,R,lazy[t],add[t]);
        }
        lazy[t] = 0; add[t] = true;
    }
 
    void upd(int t, int L, int R, int l, int r, long long value, bool isAdd) {
        if(R < l || r < L) return;
        if(l <= L && R <= r) {
            apply(t,L,R,value,isAdd);
            return;
        }
        push(t,L,R);
 
        int mid = (L+R)/2;
        upd(t+1,L,mid,l,r,value,isAdd);
        upd(t+2*(mid-L+1),mid+1,R,l,r,value,isAdd);
        sum[t] = sum[t+1]+sum[t+2*(mid-L+1)];
    }
 
    long long que(int t, int L, int R, int l, int r){
        if(r < L || R < l) return 0;
        if(l <= L && R <= r) return sum[t];
        push(t,L,R);
 
        int mid = (L+R)/2;
        long long p = que(t+1,L,mid,l,r);
        long long q = que(t+2*(mid-L+1),mid+1,R,l,r);
        return p+q;
    }
};