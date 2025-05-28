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
while(l < r){
    int mid = (l + r) >> 1;
    if(check(mid) <= check(mid + 1)){
        r = mid;
    else{
        l = mid + 1;
    }
}
cout << check(l) << endl;
默认找最大值，找最小值将判断反过来
