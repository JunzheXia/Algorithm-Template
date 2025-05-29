    string s;
    cin >> s;
    int n = s.length();
    string t = "-#";
    for (int i = 0; i < n; i++) {
        t += s[i];
        t += '#';
    }
    int m = t.length();
    int mid = 0, r = 0;
    vector<int> p(m);
    for (int i = 1; i < m - 1; i++) {
        p[i] = i < r ? min(p[2 * mid - i], r - i) : 0;
        while (t[i - p[i] - 1] == t[i + p[i] + 1])
            p[i]++;
        if (i + p[i] > r) {
            r = i + p[i];
            mid = i;
        }
    }
    int mx = *max_element(p.begin(), p.end());
    int c = distance(p.begin(), find(p.begin(), p.end(), mx));
    cout << s.substr((c - mx) / 2, mx) << '\n' << mx;
