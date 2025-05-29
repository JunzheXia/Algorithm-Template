支持大小写字母、数字的字典树

const int N = 3e6 + 10;
int trie[N][62];
int cnt[N];
int id;

struct Trie {
    Trie() { clear(); }

    void clear() {
        for (int i = 0; i <= id; i++) {
            fill(trie[i], trie[i] + 62, 0);
            cnt[i] = 0;
        }
        id = 0;
    }

    int get(char c) {
        if (c >= 'a' && c <= 'z')
            return c - 'a';
        if (c >= 'A' && c <= 'Z')
            return c - 'A' + 26;
        if (c >= '0' && c <= '9')
            return c - '0' + 52;
    }

    void insert(const string &s) {
        int p = 0;
        for (char c : s) {
            int x = get(c);
            if (!trie[p][x])
                trie[p][x] = ++id;
            p = trie[p][x];
            cnt[p]++;
        }
    }

    int find(const string &s) {
        int p = 0;
        for (char c : s) {
            int x = get(c);
            if (!trie[p][x])
                return 0;
            p = trie[p][x];
        }
        return cnt[p];
    }
};

void solve() {
    Trie trie;
    int n, q;
    string s;
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> s;
        trie.insert(s);
    }
    for (int i = 0; i < q; i++) {
        cin >> s;
        cout << trie.find(s) << '\n';
    }
}
