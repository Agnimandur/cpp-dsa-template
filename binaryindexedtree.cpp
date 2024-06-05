struct BinaryIndexedTree {
    vector<int> arr;
    int N;

    BinaryIndexedTree (int N) {
        this->N=N;
        arr.assign(N+1,0);
    }

    void add(int i, int val) {
        for (int node = i+1; node <= N; node += (node & (-node)))
            arr[node] += val;
    }

    int sum(int s_i, int e_i) {
        return sum(e_i+1) - sum(s_i);
    }

    int sum(int i) {
        int total = 0;
        for (int node = i; node > 0; node -= (node & (-node)))
            total += arr[node];
        return total;
    }

    int search(int v) {
        int sum = 0;
        int pos = 0;
        for(int i=19; i>=0; i--) {
            if (pos + (1 << i) <= N && sum + arr[pos + (1 << i)] < v) {
                sum += arr[pos + (1 << i)];
                pos += (1 << i);
            }
        }
        return pos;
    }
};