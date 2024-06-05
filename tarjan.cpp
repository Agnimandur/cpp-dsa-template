struct Tarjan {
    int N,foundat=1;
    vector<vector<int>> graph,scc;
    vector<int> disc,low;
    vector<bool> onstack;

    Tarjan(int N) {
        this->N=N;
        graph.assign(N,vector<int>{});
        disc.assign(N,-1);
        low.assign(N,1000000000);
        onstack.assign(N,false);
    }

    void addEdge(int u, int v) {
        graph[u].add(v);
    }

    void tarjan(int u){
        static stack<int> st;

        disc[u]=low[u]=foundat++;
        st.push(u);
        onstack[u]=true;
        for(int v: graph[u]){
            if(disc[v]==-1){
                tarjan(v);
                low[u]=min(low[u],low[v]);
            } else if(onstack[v]) {
                low[u]=min(low[u],disc[v]);
            }
        }
        if(disc[u]==low[u]){
            vector<int> scctem;
            while(true) {
                int v=st.top();
                st.pop();onstack[v]=false;
                scctem.add(v);
                if(u==v) break;
            }
            scc.add(scctem);
        }
    }

    vector<vector<int>> run() {
        for (int i = 0; i < N; i++) {
            if (disc[i]==-1)
                tarjan(i);
        }
        return scc;
    }
};