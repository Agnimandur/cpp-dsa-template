const int K = 26;
struct Vertex {
    array<int,K> next;
    int parent = -1;
    int leaf = 0;

    Vertex() {
        fill(all(next), -1);
    }
};

vector<Vertex> trie(1);

void insert_string(string const& s, int x) {
    int v = 0;
    for (char ch : s) {
        int c = ch - 'a';
        if (trie[v].next[c] == -1) {
            trie[v].next[c] = sz(trie);
            trie.emplace_back();
        }
        int p = trie[v].next[c];
        trie[p].parent = v;
        v = p;
    }
    trie[v].leaf += x;
}