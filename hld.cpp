struct HeavyLightDecomposition {
    int N;
    static const int D = 20;
    vector<vector<int>> table,tree;
    vector<int> depth,subsum,relabeled, firstinchain;
    int timer = 0;

    vector<long long> seg,nums;
    long long NONE = 0; //set this manualong longy

    HeavyLightDecomposition(vector<vector<int>>& tree) {
        N = (int)tree.size();
        this->tree=tree;
        depth.assign(N,0); subsum.assign(N,0);
        table.assign(D,vector<int>(N,-1));
        dfs(0,-1);
        for (int i = 1; i < D; i++) {
            for (int u = 0; u < N; u++) {
                if (table[i-1][u] >= 0)
                    table[i][u] = table[i-1][table[i-1][u]];
                else
                    table[i][u] = -1;
            }
        }

        relabeled.assign(N,0); firstinchain.assign(N,0);
        dfs2(0,-1,0);

        seg.assign(2*N,0); nums.assign(N,0);
    }

    void dfs(int u, int p) {
        table[0][u] = p;
        subsum[u] = 1;
        for (int v: tree[u]) {
            if (v==p) continue;
            depth[v] = depth[u]+1;
            dfs(v,u);
            subsum[u] += subsum[v];
        }
    }

    bool heavy(int u, int v) {
        if (depth[u] > depth[v]) return heavy(v,u);
        return subsum[v] >= (1+subsum[u])/2;
    }

    void dfs2(int u, int p, int b) {
        relabeled[u] = timer; timer++;
        firstinchain[u] = b;

        for (int v: tree[u]) {
            //heavy edge
            if (v != p && heavy(u,v)) dfs2(v,u,b);
        }
        for (int v: tree[u]) {
            //light edge
            if (v != p && !heavy(u,v)) dfs2(v,u,v);
        }
    }

    int up(int u, int dist) {
        for (int i = D-1; i >= 0; i--) {
            if ((dist&(1<<i)) > 0) {
                u = table[i][u];
                if (u==-1) return -1;
            }
        }
        return u;
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) return lca(v,u);

        int diff = depth[u]-depth[v];
        u = up(u,diff);
        if (u==v) return u;

        for (int i = D-1; i >= 0; i--) {
            if (table[i][u]!=table[i][v]) {
                u = table[i][u];
                v = table[i][v];
            }
        }
        return table[0][u];
    }


    //set this manually
    long long merge(long long a, long long b) {
        return a+b;
    }

    void segupdate(int p, long long value) {
        for (seg[p += N] = value; p > 1; p >>= 1)
            seg[p>>1] = merge(seg[p],seg[p^1]);
    }

    long long q(int l, int r) {
        long long res = NONE;
        for (l += N, r += N; l < r; l >>= 1, r >>= 1) {
            if (l&1) res = merge(res,seg[l++]);
            if (r&1) res = merge(res,seg[--r]);
        }
        return res;
    }

    long long segquery(int l, int r) {
        return q(l,r+1);
    }

    
    long long HLDhelper(int u, int dist) {
        if (dist < 0 || u < 0) return NONE;
        if (dist == 0) return nums[u];

        int ru = relabeled[u];
        int rf = relabeled[firstinchain[u]];
        int hop = max(rf,ru-dist);

        int par = table[0][firstinchain[u]];
        return merge(segquery(hop,ru),HLDhelper(par,dist-(ru-hop)-1));
    }

    /*
        HLD OPERATIONS!
        HLDupdate: Point update O(log N)
        HLDquery: Range path query O(log^2 N)
    */
    
    //Update the value at a node
    void update(int i, long long val) {
        segupdate(relabeled[i],val);
        nums[i] = val;
    }

    //Query along the path from node u to v
    long long query(int u, int v) {
        int x = lca(u,v);
        long long val1 = HLDhelper(u,depth[u]-depth[x]-1);
        long long val2 = HLDhelper(v,depth[v]-depth[x]-1);
        return merge(nums[x],merge(val1,val2));
    }
};