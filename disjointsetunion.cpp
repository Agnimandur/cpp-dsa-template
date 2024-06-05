struct DisjointSetUnion {
    vector<int> parent;
    vector<int> weight;
    int count; //number of components

    DisjointSetUnion(int N) {
        count = N;
        parent.assign(N,0);
        for (int i = 0; i < N; i++) parent[i] = i;
        weight.assign(N,1);
    }

    //"find"
    int root(int p) {
        if (p==parent[p])
            return p;
        int r = root(parent[p]);
        parent[p] = r;
        return r;
    }

    //"union"
    void connect(int p, int q) {
        p = root(p);
        q = root(q);
        if (p==q) return;

        if (weight[p] >= weight[q]) swap(p,q);
        parent[p] = q;
        weight[q] += weight[p];
        count--;
    }

    bool connected(int p, int q) {
        return root(p)==root(q);
    }
};