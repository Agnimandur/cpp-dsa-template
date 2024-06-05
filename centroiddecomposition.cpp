struct CentroidDecomposition {
    vector<vector<int>> tree;
    int N;
    vector<int> parent;
    vector<int> count;
    vector<bool> vis;
    int root; //centroid of the tree

    CentroidDecomposition(vector<vector<int>>& tree) {
        this->tree = tree;
        N = (int)tree.size();
        parent.assign(N,-1);
        count.assign(N,0);
        vis.assign(N,false);
        init_centroid();
    }

    //Construct the centroid tree (max depth, logN)
    vector<vector<int>> run() {
        vector<vector<int>>centroidTree(N,vi{});
        for (int i = 0; i < N; i++) {
            if (parent[i] >= 0) centroidTree[parent[i]].push_back(i);
        }
        return centroidTree;
    }

    void init_centroid(int v = 0, int p = -1) {
        find_size(v);

        int c = find_centroid(v, -1, count[v]);
        vis[c] = true;
        parent[c] = p;
        if (p==-1) root = c;

        for (int x: tree[c]) {
            if (!vis[x]) {
              init_centroid(x, c);
            }
        }
    }

    int find_size(int v, int p = -1) {
        if (vis[v]) return 0;
        count[v] = 1;

        for (int x: tree[v]) {
            if (x != p) {
                count[v] += find_size(x, v);
            }
        }

        return count[v];
    }

    int find_centroid(int v, int p, int n) {
        for (int x: tree[v]) {
            if (x != p && !vis[x] && count[x] > n / 2) {
                return find_centroid(x, v, n);
            }
        }
        return v;
    }
};