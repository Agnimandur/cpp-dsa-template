struct Dijkstra {
    vector<vector<pair<int,int>>> graph;
    int N;

    Dijkstra(int N) {
        graph.assign(N,vector<pair<int,int>>{});
        this->N=N;
    }

    void addEdge(int u, int v, int w) {
        graph[u].add({v,w});
    }

    vector<long long> dijkstra(int root) {
        long long INF = 1000000000000000000LL;
        vector<long long> dists(N,INF);

        dists[root] = 0LL;
        priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> pq;
        pq.push({0LL, root});

        while (!pq.empty()) {
            int v = pq.top().second;
            long long d_v = pq.top().first; pq.pop();

            for (auto edge : graph[v]) {
                int to = edge.first;
                long long w = edge.second;

                if (d_v + w < dists[to]) {
                    dists[to] = d_v + w;
                    pq.push({dists[to], to});
                }
            }
        }

        return dists;
    }
};