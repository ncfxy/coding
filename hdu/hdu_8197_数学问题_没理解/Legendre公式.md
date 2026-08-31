# Legendre 公式

Legendre 公式（也称 de Polignac 公式）用来计算 \(n!\) 中某个质数 \(p\) 出现了几次。

记 \(v_p(m)\) 为 \(m\) 的 \(p\)-adic 赋值，即 \(m\) 的质因数分解里 \(p\) 的指数。则

\[
v_p(n!)=\sum_{k\ge 1}\left\lfloor\frac{n}{p^k}\right\rfloor.
\]

求和在 \(p^k>n\) 时自动停止。约定 \(v_p(0!)=v_p(1)=0\)。

本题里

\[
f(x)=v_2(x!),
\]

就是 \(p=2\) 的特例。

---

## 1. 为什么成立

\(n!=1\cdot 2\cdot\ldots\cdot n\)。\(1\sim n\) 里：

- 每 \(p\) 个数贡献一次因子 \(p\)，共 \(\lfloor n/p\rfloor\) 个；
- 每 \(p^2\) 个数再多贡献一次，共 \(\lfloor n/p^2\rfloor\) 个；
- 每 \(p^3\) 个数再多贡献一次，……

把这些贡献加起来，就是 \(v_p(n!)\)。

例如 \(v_5(100!)=\lfloor 100/5\rfloor+\lfloor 100/25\rfloor+\lfloor 100/125\rfloor=20+4+0=24\)，所以 \(100!\) 末尾有 24 个零。

---

## 2. \(p=2\) 时的闭形式

把 \(x\) 写成二进制：

\[
x=\sum_{i\ge 0}a_i\,2^i,\qquad a_i\in\{0,1\}.
\]

\(\operatorname{popcount}(x)=\sum_i a_i\) 是 \(x\) 二进制表示中 \(1\) 的个数。则

\[
v_2(x!)=\sum_{k\ge 1}\left\lfloor\frac{x}{2^k}\right\rfloor=x-\operatorname{popcount}(x).
\]

证明：对每个 \(k\)，

\[
\left\lfloor\frac{x}{2^k}\right\rfloor=\sum_{i\ge k}a_i\,2^{i-k}.
\]

对 \(k\) 求和后，每个 \(a_i\) 出现的次数是

\[
1+2+4+\cdots+2^{i-1}=2^i-1,
\]

因此

\[
\sum_{k\ge 1}\left\lfloor\frac{x}{2^k}\right\rfloor
=\sum_i a_i(2^i-1)
=\sum_i a_i\,2^i-\sum_i a_i
=x-\operatorname{popcount}(x).
\]

例：\(x=13=1101_2\)，\(\operatorname{popcount}(13)=3\)，

\[
f(13)=\left\lfloor\frac{13}{2}\right\rfloor+\left\lfloor\frac{13}{4}\right\rfloor+\left\lfloor\frac{13}{8}\right\rfloor=6+3+1=10=13-3.
\]

---

## 3. 二进制整块上的可加性

如果 \(B\) 是 \(2^k\) 的倍数，并且 \(0\le t<2^k\)，则 \(B\) 的低 \(k\) 位全为 \(0\)，与 \(t\) 相加不进位：

\[
\operatorname{popcount}(B+t)=\operatorname{popcount}(B)+\operatorname{popcount}(t).
\]

于是

\[
f(B+t)=f(B)+f(t).
\]

特别地，取 \(B=2^k\)：

\[
f(2^k+t)=2^k-1+f(t).
\]

HDU 8197 能处理 \(V\le 10^{18}\)，用的就是这个性质：把 \([0,V]\) 拆成若干个二进制整块，再对每块做矩阵变换。

---

## 4. 实现

```cpp
// v_p(n!)，p 为质数
long long legendre(long long n, long long p) {
    long long ans = 0;
    while (n) {
        n /= p;
        ans += n;
    }
    return ans;
}

// v_2(n!) = n - popcount(n)
long long v2_fact(long long n) {
    return n - __builtin_popcountll(n);
}
```
