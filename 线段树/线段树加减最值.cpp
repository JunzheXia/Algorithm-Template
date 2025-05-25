
struct node {
    i64 l, r, sum, lazy;
} tr[N << 2];

void push_up(int ind) { tr[ind].sum = tr[ind << 1].sum + tr[ind << 1 | 1].sum; }//上传

void build(int ind, int l, int r) {//建树
    tr[ind].l = l, tr[ind].r = r;
    if (l == r) {
        tr[ind].sum = a[l];
        return;
    }
    int mid = (l + r) >> 1;
    build(ind << 1, l, mid);
    build(ind << 1 | 1, mid + 1, r);
    push_up(ind);
}

void push_down(int ind) {//下传
    if (tr[ind].lazy) {
        tr[ind << 1].sum +=
            tr[ind].lazy * (tr[ind << 1].r - tr[ind << 1].l + 1);
        tr[ind << 1].lazy += tr[ind].lazy;
        tr[ind << 1 | 1].sum +=
            tr[ind].lazy * (tr[ind << 1 | 1].r - tr[ind << 1 | 1].l + 1);
        tr[ind << 1 | 1].lazy += tr[ind].lazy;
        tr[ind].lazy = 0;
    }
}

void modify(int ind, int l, int r, i64 k) {//区间修改同时支持单点修改
    if (tr[ind].l >= l && tr[ind].r <= r) {
        tr[ind].sum += k * (tr[ind].r - tr[ind].l + 1);
        tr[ind].lazy += k;
        return;
    }
    push_down(ind);
    int mid = (tr[ind].l + tr[ind].r) >> 1;
    if (l <= mid) {
        modify(ind << 1, l, r, k);
    }
    if (r > mid) {
        modify(ind << 1 | 1, l, r, k);
    }
    push_up(ind);
}

i64 query(int ind, int l, int r) {//区间查询同时支持单点查询
    if (tr[ind].l >= l && tr[ind].r <= r) {
        return tr[ind].sum;
    }
    if (tr[ind].r < l || tr[ind].l > r) {
        return 0;
    }
    push_down(ind);
    i64 res = 0;
    int mid = (tr[ind].l + tr[ind].r) >> 1;
    if (l <= mid) {
        res += query(ind << 1, l, r);
    }
    if (r > mid) {
        res += query(ind << 1 | 1, l, r);
    }
    return res;
}

查询最值也是比较简单和常见的操作
struct node {
    int l, r, mn;
} tr[N << 2];
加上相应标记即可
int query(int ind, int l, int r) {//最小值查询
    if (tr[ind].l > r || tr[ind].r < l) {
        return INF;
    }
    if (tr[ind].l >= l && tr[ind].r <= r) {
        return tr[ind].mn;
    }
    return min(query(ind << 1, l, r), query(ind << 1 | 1, l, r));
}
