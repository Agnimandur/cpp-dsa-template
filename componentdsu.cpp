struct ComponentDSU {
    vector<int> parent;
    vector<int> weight;
    int count; //number of components
    vector<set<int>> sets;
    set<int> roots;
 
    ComponentDSU(int N) {
        count = N;
        parent.assign(N,0);
        for (int i = 0; i < N; i++) parent[i] = i;
        weight.assign(N,1);
        sets.assign(N,set<int>{});
        for (int i = 0; i < N; i++) sets[i].insert(i);
        for (int i = 0; i < N; i++) roots.insert(i);
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
        sets[q].insert(all(sets[p]));
        sets[p].clear();
        roots.erase(p);
        count--;
    }
 
    bool connected(int p, int q) {
        return root(p)==root(q);
    }
};
