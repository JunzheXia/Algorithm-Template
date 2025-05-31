    cin >> n;
    for (int i = 1; i <= n; i++)cin >> a[i];
    for (int i = 1; i <= n; i++) {
        f[i] = 1;
        for (int j = 1; j < i; j++) {
            if (a[i] > a[j]) {
                f[i] = max(f[i], f[j] + 1);
            }
        }
        maxx = max(maxx, f[i]);
    }
    cout << maxx;

二分优化

第一问  最长单调不升子序列
	f[1] = a[1];
	for (int i = 2; i <= n; i++) {
		if (f[t] >= a[i])f[++t] = a[i];
		else {
			*upper_bound(f + 1, f + t + 1, a[i], greater<int>()) = a[i];
		}
	}
	cout << t << endl;
	t = 1;
第二问  最长上升子序列
	memset(f, 0, sizeof(f));
	f[1] = a[1];
	for (int i = 2; i <= n; i++) {
		if (f[t] < a[i])f[++t] = a[i];
		else {
			*lower_bound(f + 1, f + 1 + t, a[i]) = a[i];
		}
	}
	cout << t;
