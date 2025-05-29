01字典树，支持插入和删除操作  查询最大和最小异或值

const int BIT = 30;
const int N = 1e5 * BIT;
int trie[N][2];
int cnt[N];
int id;

struct Trie {
    Trie() { clear(); }

    void clear() {
        for (int i = 0; i <= id; i++) {
            trie[i][0] = trie[i][1] = 0;
            cnt[i] = 0;
        }
        id = 0;
    }

    void insert(int x) {
        int p = 0;
        for (int i = BIT; i >= 0; i--) { // 从高位到低位
            int b = (x >> i) & 1;
            if (!trie[p][b])
                trie[p][b] = ++id;
            p = trie[p][b];
            cnt[p]++;
        }
    }

    void erase(int x) {
        int p = 0;
        for (int i = BIT; i >= 0; i--) {
            int b = (x >> i) & 1;
            p = trie[p][b];
            cnt[p]--;
        }
    }

    // 查询与x异或最大的数
    int max_xor(int x) {
        int p = 0, res = 0;
        for (int i = BIT; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (trie[p][!b] && cnt[trie[p][!b]]) {
                res |= (1 << i);
                p = trie[p][!b];
            } else {
                p = trie[p][b];
            }
        }
        return res;
    }

    // 查询与x异或最小的数
    int min_xor(int x) {
        int p = 0, res = 0;
        for (int i = BIT; i >= 0; i--) {
            int b = (x >> i) & 1;
            if (trie[p][b] && cnt[trie[p][b]]) {
                p = trie[p][b];
            } else {
                res |= (1 << i);
                p = trie[p][!b];
            }
        }
        return res;
    }
}

void solve() {
    BinaryTrie trie;
    trie.insert(0); // 通常先插入0作为初始值

    int q;
    cin >> q;
    while (q--) {
        char op;
        int x;
        cin >> op >> x;
        if (op == '+')
            trie.insert(x);
        else if (op == '-')
            trie.erase(x);
        else
            cout << trie.max_xor(x) << '\n';
    }
}
