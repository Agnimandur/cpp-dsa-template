struct TopologicalSort {
    int n;
    vector<vector<int>> graph;
    vector<bool> visited;
    vector<int> order;
    vector<int> post;

    TopologicalSort(vector<vector<int>> &g) {
        graph = g;
        n = (int)graph.size();
    }

    TopologicalSort(int numNodes) {
        n = numNodes;
        graph.assign(n,vector<int>{});
    }

    void addEdge(int u, int v) {
        graph[u].push_back(v);
    }

    void dfs(int v) {
        visited[v] = true;
        for (int u : graph[v]) {
            if (!visited[u])
                dfs(u);
        }
        order.push_back(v);
    }

    vector<int> run() {
        visited.assign(n, false);
        for (int i = 0; i < n; i++) {
            if (!visited[i])
                dfs(i);
        }
        reverse(order.begin(), order.end());
        post.assign(n,-1);
        for (int i = 0; i < n; i++) {
            post[order[i]] = i;
        }
        
        for (int i = 0; i < n; i++) {
            for (int j: graph[i]) {
                if (post[i] > post[j]) {
                    order.clear();
                    return order;
                }
            }
        }
        return order;
    }
};