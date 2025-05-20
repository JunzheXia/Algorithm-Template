//往小找
while (l < r) {
    int mid = (l + r) >> 1;
    if (check(mid)) {
        r = mid;
    } else
        l = mid + 1;
}
//往大找
while (l < r) {
    int mid = (l + r + 1) >> 1;
    if (check(mid)) {
        l = mid;
    } else
        r = mid - 1;
}
//l 就是结果
