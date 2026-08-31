#include <iostream>
#include <vector>
using namespace std;

using ll = long long;

/*
 * 归并排序统计逆序对
 *
 * 同时将 a[l...r] 排序。
 */
ll mergeSort(vector<int>& a, vector<int>& tmp, int l, int r) {
    if (l >= r) {
        return 0;
    }

    int mid = (l + r) >> 1;

    ll cnt = 0;

    // 统计左右两部分内部的逆序对
    cnt += mergeSort(a, tmp, l, mid);
    cnt += mergeSort(a, tmp, mid + 1, r);

    // 统计跨左右区间的逆序对
    int i = l;
    int j = mid + 1;
    int k = l;

    while (i <= mid && j <= r) {
        if (a[i] <= a[j]) {
            tmp[k++] = a[i++];
        } else {
            /*
             * 因为左半部分已经有序，
             *
             * a[i] > a[j]
             *
             * 则：
             *
             * a[i], a[i+1], ..., a[mid]
             *
             * 都大于 a[j]。
             *
             * 因此产生 mid - i + 1 个逆序对。
             */
            cnt += mid - i + 1;
            tmp[k++] = a[j++];
        }
    }

    while (i <= mid) {
        tmp[k++] = a[i++];
    }

    while (j <= r) {
        tmp[k++] = a[j++];
    }

    // 写回原数组
    for (int p = l; p <= r; ++p) {
        a[p] = tmp[p];
    }

    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;

    // 多组测试数据，读到 EOF
    while (cin >> n) {
        vector<int> a(n);

        for (int i = 0; i < n; ++i) {
            cin >> a[i];
        }

        /*
         * mergeSort 会修改数组，
         * 后面还需要原排列的顺序，
         * 因此复制一份。
         */
        vector<int> b = a;
        vector<int> tmp(n);

        // 初始排列的逆序对
        ll inv = mergeSort(b, tmp, 0, n - 1);

        ll ans = inv;

        /*
         * 依次将：
         *
         * a[0], a[1], ..., a[n-2]
         *
         * 从序列开头移动到序列末尾。
         *
         * 不需要真的旋转数组。
         */
        for (int i = 0; i < n - 1; ++i) {
            ll x = a[i];

            /*
             * 移动前：
             * x 与所有比它小的数构成逆序对，
             * 一共 x 个。
             *
             * 移动后：
             * 所有比 x 大的数与 x 构成逆序对，
             * 一共 n - 1 - x 个。
             */
            inv -= x;
            inv += n - 1 - x;

            // 等价于：
            // inv += n - 1 - 2 * x;

            ans = min(ans, inv);
        }

        cout << ans << '\n';
    }

    return 0;
}