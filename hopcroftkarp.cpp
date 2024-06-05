//Max matching in bipartite graphs
struct HopcroftKarp {
    vector<int> match;
    vector<int> dist;
    vector<vector<int>> graph;
    int N;
    int M;
    int T;
    const int INF = 1000000000;

    HopcroftKarp(int N, int M) {
        this->N=N;
        this->M=M;
        T = N+M+1;
        match.assign(T,0);
        dist.assign(T,0);
        graph.assign(T,vector<int>{});
    }

    //1 indexed
    void addEdge(int u, int v) {
        graph[u].add(v);
        graph[v].add(u);
    }

    bool BFS() {
        queue<int> q;
        for (int u = 1; u <= N; u++) {
            if (match[u]==0) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INF;
            }
        }
        dist[0] = INF;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            if (dist[u]<dist[0]) {
                for (int v: graph[u]) {
                    if (dist[match[v]] == INF) {
                        dist[match[v]] = dist[u]+1;
                        q.push(match[v]);
                    }
                }
            }
        }
        return dist[0]<INF;
    }

    bool DFS(int u) {
        if (u > 0) {
            for (int v: graph[u]) {
                if (dist[match[v]]==dist[u]+1 && DFS(match[v])) {
                    match[v] = u;
                    match[u] = v;
                    return true;
                }
            }
            dist[u] = INF;
            return false;
        }
        return true;
    }

    vector<pii> run() {
        int m = 0;
        while (BFS()) {
            for (int u = 1; u <= N; u++) {
                if (match[u]==0 && DFS(u)) {
                    m++;
                }
            }
        }
        vector<pii> ans;
        for (int v = N+1; v <= N+M; v++) {
            if (match[v]>0) {
                ans.add(make_pair(match[v],v));
            }
        }
        return ans;
    }
};
