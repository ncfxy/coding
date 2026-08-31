# FFT 与 Dominance Convolution

对照本题实现见 [`hdu_8190.md`](./hdu_8190.md)、[`hdu_8190.cpp`](./hdu_8190.cpp)。

先记住两句：

- **FFT**：快速算多项式乘法，也就是快速卷积。
- **Dominance convolution**：只统计满足偏序约束的数对，再按某个函数（本题是差值 \(k=x-y\)）做卷积。

FFT 不管「谁支配谁」；支配关系要靠分块、只取非负下标这些题意约束自己保证。

---

# 第一部分：FFT

## 1. 名字

**FFT** = Fast Fourier Transform，快速傅里叶变换。

它算的是离散傅里叶变换 **DFT**。DFT 本身是 \(O(n^2)\) 的定义式，FFT 是 \(O(n\log n)\) 的算法。

信号处理里，FFT 把时间信号拆成各个频率。竞赛里几乎只关心一件事：

> 两个长度为 \(n\) 的数组做卷积，从 \(O(n^2)\) 降到 \(O(n\log n)\)。

---

## 2. 卷积就是多项式乘法

给定

\[
F(z)=\sum_{i=0}^{n-1}f_i z^i,\qquad
G(z)=\sum_{j=0}^{n-1}g_j z^j.
\]

乘积

\[
C(z)=F(z)G(z)=\sum_k c_k z^k
\]

的系数是

\[
\boxed{
c_k=\sum_{i+j=k}f_i g_j
}
\]

这个式子叫 **（线性）卷积**。

小例子：\(f=[1,2,3]\)，\(g=[4,5]\)。

\[
\begin{align*}
c_0&=1\cdot 4=4,\\
c_1&=1\cdot 5+2\cdot 4=13,\\
c_2&=2\cdot 5+3\cdot 4=22,\\
c_3&=3\cdot 5=15.
\end{align*}
\]

暴力枚举每一对 \((i,j)\) 就是 \(O(n^2)\)。\(n=2\times 10^5\) 时过不去，所以要 FFT。

---

## 3. 为什么能变快：系数表示 \(\leftrightarrow\) 点值表示

多项式有两种看法。

**系数表示**：记下 \((f_0,f_1,\ldots,f_{n-1})\)。相乘要对每一对系数做贡献，慢。

**点值表示**：选 \(n\) 个不同的数 \(x_0,\ldots,x_{n-1}\)，记下

\[
\bigl(F(x_0),F(x_1),\ldots,F(x_{n-1})\bigr).
\]

点值下乘法极快：

\[
C(x_k)=F(x_k)\,G(x_k).
\]

只要 \(O(n)\) 次复数乘法。

于是完整流程是：

1. 系数 \(\xrightarrow{\text{FFT}}\) 点值，\(O(n\log n)\)
2. 对应位置相乘，\(O(n)\)
3. 点值 \(\xrightarrow{\text{IFFT}}\) 系数，\(O(n\log n)\)

关键是第 1、3 步不能用随便选的 \(x_k\)，否则求值/插值仍是 \(O(n^2)\)。FFT 选的是 **单位根**，才能分治做到 \(O(n\log n)\)。

---

## 4. DFT 公式

取 \(n\) 次单位根（竞赛实现里通常 \(n\) 是 2 的幂）

\[
\omega=e^{-2\pi i/n}=\cos\theta+i\sin\theta,\qquad
\theta=-\frac{2\pi}{n}.
\]

它满足 \(\omega^n=1\)，且 \(1,\omega,\omega^2,\ldots,\omega^{n-1}\) 两两不同。

**正变换（DFT / FFT）**：

\[
\hat f_k
=
\sum_{j=0}^{n-1}f_j\,\omega^{jk}
=
F(\omega^k).
\]

**逆变换（IDFT / IFFT）**：

\[
f_j
=
\frac1n\sum_{k=0}^{n-1}\hat f_k\,\omega^{-jk}.
\]

卷积定理：

\[
\boxed{
\widehat{(f*g)}_k
=
\hat f_k\cdot\hat g_k
}
\]

也就是：时域卷积 = 频域点乘。这就是「先 FFT、再点乘、再 IFFT」的全部根据。

代码里：

- `transform(a, false)`：正 FFT，得到 \(\hat f\)
- `transform(a, true)`：逆 FFT，并且除以 \(n\)，回到系数

---

## 5. 分治直觉（蝴蝶）

为什么单位根能分治？把下标拆成偶数、奇数：

\[
F(z)=F_{\mathrm{even}}(z^2)+z\,F_{\mathrm{odd}}(z^2).
\]

在 \(z=\omega^k\) 和 \(z=\omega^{k+n/2}\) 上，有

\[
(\omega^{k+n/2})^2=(\omega^k)^2,
\]

后一半可以复用前一半已经算过的子问题，只差一个符号（因为 \(\omega^{n/2}=-1\)）。

于是规模 \(n\) 的 DFT 变成两次规模 \(n/2\) 的 DFT，外加 \(O(n)\) 次合并：

\[
T(n)=2T(n/2)+O(n)=O(n\log n).
\]

实现上就是不断对半、乘旋转因子 `w`，即所谓蝴蝶操作。`rev[]` 是位逆序，用来把递归的叶子排成迭代下标。

这些实现细节记住「能 \(O(n\log n)\) 求值/插值」即可，本题真正用到的代数性质在后面两节。

---

## 6. 线性卷积 vs 循环卷积

FFT 默认算的是 **循环卷积**（多项式乘法再模 \(z^L-1\)）：

\[
c_k
=
\sum_{i+j\equiv k\pmod L}f_i g_j.
\]

下标加起来超过 \(L\) 的项会 **绕回来** 加到低位上。

线性卷积没有绕回。要让循环卷积等于线性卷积，必须把长度取够：

\[
L\ge \deg F+\deg G+1.
\]

通常把 \(L\) 补成 2 的幂。本题值在 \([1,n]\)，差在 \([-(n-1),n-1]\)，所以取

\[
L>2n
\]

的 2 的幂。正差放在下标 \(k\)，负差绕到 \(L-k\)，两者不会撞。

---

## 7. 相关：差卷积 \(F(z)G(z^{-1})\)

普通卷积统计的是 **和** \(i+j=k\)。

本题统计的是 **差** \(x-y=k\)：

\[
\boxed{
c_k=\sum_{x-y=k}f_x g_y
}
\]

对应生成函数

\[
C(z)=F(z)\,G(z^{-1}).
\]

在循环意义下，\(G(z^{-1})\) 就是把 \(g\) 的系数按下标 \(0,-1,-2,\ldots\) 排，也就是

\[
g_0,\; g_{L-1},\; g_{L-2},\; \ldots
\]

对 **实系数** 多项式，有一个极好用的性质：

\[
\boxed{
\operatorname{FFT}\bigl(F(z^{-1})\bigr)
=
\overline{\widehat F}
}
\]

也就是频域里对 \(\widehat F\) 逐点取共轭，不必真的把数组 reverse 再 FFT 一次。

本题代码里的

```text
prod = prefix[k] * conj(F)
```

就是在算

\[
\Bigl(\sum_{p<q}F_p(z)\Bigr)F_q(z^{-1})
\]

的频域形式。

---

## 8. 两实数组打包进一次 FFT

实数组的 FFT 有共轭对称：

\[
\hat f_{L-k}=\overline{\hat f_k}.
\]

因此可以把两个实数组 \(f,g\) 塞进一个复数组

\[
h_x=f_x+i g_x,
\]

做一次 FFT 得到 \(H\)，再拆：

\[
\hat f_k=\frac{H_k+\overline{H_{-k}}}{2},\qquad
\hat g_k=\frac{H_k-\overline{H_{-k}}}{2i}.
\]

正 FFT 次数减半。本题 \(n=2\times 10^5\)，这个常数优化很有用。

---

# 第二部分：Dominance Convolution

## 9. 它不是一种新的 FFT

**Dominance convolution（支配卷积）** 描述的是 **带偏序约束的配对计数**，不是 DFT 的变体。

普通卷积：所有 \((x,y)\) 只要下标加起来（或减出来）等于 \(k\) 都算。

支配卷积：还要满足「谁在前、谁更大」这类不等式，只统计被支配关系允许的对。

本题要的是

\[
\boxed{
ans_k
=
\#\{(i,j):i<j,\ a_i\ge a_j,\ a_i-a_j=k\}
}
\]

两层支配：

| 维度 | 约束 | 含义 |
|------|------|------|
| 位置 | \(i<j\) | 左边下标更靠前 |
| 值 | \(a_i\ge a_j\) | 左边值更大（或相等） |

按差值 \(k=a_i-a_j\) 汇总，就是 dominance convolution。

和普通卷积的对比：

\[
\begin{align*}
\text{普通卷积}\quad
c_k&=\sum_{x+y=k}f_x g_y,\\
\text{相关 / 差卷积}\quad
c_k&=\sum_{x-y=k}f_x g_y,\\
\text{本题的支配卷积}\quad
ans_k&=\sum_{\substack{i<j\\x=a_i,\,y=a_j\\x-y=k\\x\ge y}}1.
\end{align*}
\]

第三式比第二式多了位置顺序 \(i<j\)。值上的 \(x\ge y\) 等价于只要 \(k\ge 0\)，IFFT 之后丢掉负下标即可。

---

## 10. 为什么不能对整个数组直接 FFT

如果不管位置，只做值的频次相关：

\[
f_x=\#\{i:a_i=x\},
\qquad
c_k=\sum_{x-y=k}f_x f_y,
\]

会把 \((i,j)\) 和 \((j,i)\) 一起算进去，也没有 \(i<j\)。顺序信息在做成频次数组的那一刻就丢了。

所以：

- 值域上的差 \(x-y\)：FFT 能一次算完；
- 位置上的序 \(i<j\)：必须另想办法保留。

---

## 11. 分块：把位置偏序变成块的先后

设块长为 \(B\)，位置分成 \(m=n/B\) 块。

数对 \((i,j)\)、\(i<j\) 分两种：

1. **同块**：块长 \(\le B\)，枚举 \(i<j\)，若 \(a_i\ge a_j\) 则 \(ans_{a_i-a_j}++\)。复杂度 \(O(nB)\)。
2. **异块**：\(i\) 在块 \(p\)，\(j\) 在块 \(q\)，且 \(p<q\)。块号已经保证 \(i<j\)，位置约束可以丢掉。

异块时每个块只剩一张频次表：

\[
c_b[x]=\#\{i\text{ 在块 }b:a_i=x\},\qquad
F_b(z)=\sum_x c_b[x]z^x.
\]

块 \(p<q\) 的贡献是

\[
F_p(z)F_q(z^{-1})
\]

中 \(z^k\)（\(k\ge 0\)）的系数。

不能枚举所有块对，否则有 \(O(m^2)\) 次卷积。改成扫右块 \(q\)，左边用前缀和：

\[
\Bigl(\sum_{p<q}F_p(z)\Bigr)F_q(z^{-1}).
\]

---

## 12. 频域里的核心公式

设 \(\widehat F_b=\operatorname{FFT}(F_b)\)。实系数加上 \(z^{-1}\) 变共轭，于是

\[
\boxed{
\widehat D
=
\sum_q
\Bigl(\sum_{p<q}\widehat F_p\Bigr)
\overline{\widehat F_q}
}
\]

实现时维护两个频域数组：

- `prefix`：已经处理过的块的 \(\widehat F\) 之和；
- `total`：累加 \(\widehat D\)。

对每个块：

```text
total += prefix * conj(F)
prefix += F
```

全部块处理完，对 `total` **只做一次 IFFT**。`total[k]`（\(0\le k\le n\)）就是所有异块、满足 \(i<j\) 且 \(a_i-a_j=k\) 的对数。

\(k<0\) 的项落在 `total[L-k]`，不要。那正好是 \(a_i<a_j\) 的对，不满足值支配。

---

## 13. 样例

数组

\[
[1,1,4,5,1,4],
\]

块长 \(B=3\)：

- 块 0：`1,1,4` \(\rightarrow\) \(F_0=2z+z^4\)
- 块 1：`5,1,4` \(\rightarrow\) \(F_1=z+z^4+z^5\)

跨块时左边每个数配右边每个数（位置已经 \(i<j\)）：

| 左 \ 右 | 5 | 1 | 4 |
|---------|---|---|---|
| 1 | \(1-5<0\) 丢 | \(0\) | \(1-4<0\) 丢 |
| 1 | 丢 | \(0\) | 丢 |
| 4 | \(4-5<0\) 丢 | \(3\) | \(0\) |

合法跨块差：三个 \(k=0\)、一个 \(k=3\)。

同块暴力再补块内的 \((i,j)\)，得到

```text
4 1 0 1 1 0 0
```

即 \(ans_0=4,\;ans_1=1,\;ans_3=1,\;ans_4=1\)。

---

## 14. 复杂度

同块暴力 \(O(nB)\)。

异块：每块一次正 FFT，最后一次 IFFT，\(L=O(n)\)，故

\[
O\Bigl(\frac nB\cdot L\log L\Bigr)
=
O\Bigl(\frac{n^2\log n}{B}\Bigr).
\]

合计

\[
O\Bigl(nB+\frac{n^2\log n}{B}\Bigr).
\]

取 \(B=\Theta(\sqrt{n\log n})\)，得到

\[
O\bigl(n\sqrt{n\log n}\bigr).
\]

两实块打包进一次 FFT，只减常数，不改阶。

---

## 15. 和 NTT 的关系

模素数下的版本叫 **NTT**（数论变换）。单位根改成模 \(p\) 的原根，公式同一套，没有浮点误差。

本题计数可以进 `long long`，用普通复数 FFT + `llround` 即可。若要求模 \(998244353\) 一类的答案，应改 NTT。

---

## 16. 收束

| 词 | 实际含义 | 本题里谁负责 |
|----|----------|----------------|
| 卷积 | \(\sum_{i+j=k}f_i g_j\) | 多项式乘法的一般形式 |
| 相关 / 差卷积 | \(\sum_{x-y=k}f_x g_y\) | FFT 点乘共轭 |
| 循环卷积 | 下标模 \(L\) 的卷积 | 取 \(L>2n\)，正负差不冲突 |
| FFT / IFFT | 系数 \(\leftrightarrow\) 点值 | 快速算出所有 \(k\) 的 \(c_k\) |
| Dominance | \(i<j\) 且 \(a_i\ge a_j\) | 分块保证位置；\(k\ge 0\) 保证值 |

一句话：

> **FFT 负责「所有 \(x-y=k\) 的乘积和」；dominance 负责「只保留 \(i<j\) 且 \(x\ge y\)」。分块把位置偏序变成块的先后，FFT 再在值域上做相关。**
