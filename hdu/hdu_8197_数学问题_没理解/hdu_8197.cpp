#include <cstdio>
#include <iostream>
#include <vector>
#include <cstdint>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;
using u128 = __uint128_t;

static const int MAXK = 60;

int n, Q;
u64 MOD;

int B;                  // block count = n + 1
int S;                  // total state dimension <= 202
vector<int> d;          // dimension of every block
vector<int> offv;       // starting position of every block

/*
    Diagonal blocks are implicitly identity matrices.

    a only stores the strictly block-lower-triangular part.
    For convenience we allocate a full S * S array.
*/
struct Mat {
    vector<u32> a;

    Mat() = default;

    explicit Mat(int s)
        : a((size_t)s * s, 0) {}
};

/*
    Given M = T_{k-1}, construct

        Shift_shift(M) * M

    where

        Shift_c(M) = P_c M P_c^{-1}.

    All matrices are unit block-lower-triangular.
*/
Mat buildNext(const Mat& M, u64 shift) {
    vector<int> sh(B);

    for (int i = 0; i < B; ++i) {
        sh[i] = (int)(shift % d[i]);
    }

    /*
        acc temporarily uses 128 bit.

        For i > j:

        C_ij = A_ij + B_ij
             + sum_{j < t < i} A_it * B_tj

        A = Shift(M)
        B = M
    */
    vector<u128> acc((size_t)S * S, 0);

    // First add A_ij + B_ij.
    for (int i = 1; i < B; ++i) {
        int di = d[i];
        int oi = offv[i];

        for (int j = 0; j < i; ++j) {
            int dj = d[j];
            int oj = offv[j];

            for (int r = 0; r < di; ++r) {
                int rr = r - sh[i];
                if (rr < 0) rr += di;

                size_t rowC = (size_t)(oi + r) * S;
                size_t rowA = (size_t)(oi + rr) * S;

                for (int c = 0; c < dj; ++c) {
                    int cc = c - sh[j];
                    if (cc < 0) cc += dj;

                    // A_ij[r][c]
                    u32 va = M.a[rowA + oj + cc];

                    // B_ij[r][c]
                    u32 vb = M.a[rowC + oj + c];

                    acc[rowC + oj + c] = (u128)va + vb;
                }
            }
        }
    }

    // Add A_it * B_tj.
    for (int t = 1; t + 1 < B; ++t) {
        int dt = d[t];
        int ot = offv[t];

        for (int i = t + 1; i < B; ++i) {
            int di = d[i];
            int oi = offv[i];

            for (int j = 0; j < t; ++j) {
                int dj = d[j];
                int oj = offv[j];

                for (int r = 0; r < di; ++r) {
                    int rr = r - sh[i];
                    if (rr < 0) rr += di;

                    size_t rowA = (size_t)(oi + rr) * S;
                    size_t rowC = (size_t)(oi + r) * S;

                    for (int q = 0; q < dt; ++q) {
                        /*
                            A_it[r][q]
                            =
                            M_it[
                                r - shift mod d_i
                            ][
                                q - shift mod d_t
                            ]
                        */
                        int qq = q - sh[t];
                        if (qq < 0) qq += dt;

                        u32 av = M.a[rowA + ot + qq];
                        if (av == 0) continue;

                        size_t rowB = (size_t)(ot + q) * S;

                        for (int c = 0; c < dj; ++c) {
                            u32 bv = M.a[rowB + oj + c];

                            acc[rowC + oj + c]
                                += (u128)av * bv;
                        }
                    }
                }
            }
        }
    }

    Mat C(S);

    // Take modulo only once for every output entry.
    for (int i = 1; i < B; ++i) {
        int di = d[i];
        int oi = offv[i];

        for (int j = 0; j < i; ++j) {
            int dj = d[j];
            int oj = offv[j];

            for (int r = 0; r < di; ++r) {
                size_t row = (size_t)(oi + r) * S;

                for (int c = 0; c < dj; ++c) {
                    C.a[row + oj + c]
                        = (u32)(acc[row + oj + c] % MOD);
                }
            }
        }
    }

    return C;
}

/*
    Apply

        P_shift * M * P_shift^{-1}

    to state.

    Each block is cyclically shifted independently.
*/
void applyShifted(
    vector<u32>& state,
    const Mat& M,
    u64 shift
) {
    vector<int> sh(B);
    vector<u32> tmp(S);

    /*
        tmp = P^{-1} state

        If P moves residue r to r + shift,
        then

            (P^{-1} state)[r]
            =
            state[r + shift].
    */
    for (int b = 0; b < B; ++b) {
        sh[b] = (int)(shift % d[b]);

        for (int r = 0; r < d[b]; ++r) {
            int src = r + sh[b];
            if (src >= d[b]) src -= d[b];

            tmp[offv[b] + r]
                = state[offv[b] + src];
        }
    }

    /*
        tmp = M * tmp

        M is block-lower-triangular.

        Process blocks from large to small, so every lower block
        used on the RHS is still the old value.
    */
    for (int i = B - 1; i >= 1; --i) {
        int oi = offv[i];
        int di = d[i];

        /*
            All earlier blocks occupy [0, offv[i]).
        */
        int prefix = offv[i];

        for (int r = 0; r < di; ++r) {
            size_t row = (size_t)(oi + r) * S;

            u128 sum = tmp[oi + r];  // implicit identity block

            for (int c = 0; c < prefix; ++c) {
                sum += (u128)M.a[row + c] * tmp[c];
            }

            tmp[oi + r] = (u32)(sum % MOD);
        }
    }

    // state = P * tmp
    for (int b = 0; b < B; ++b) {
        for (int r = 0; r < d[b]; ++r) {
            int dst = r + sh[b];
            if (dst >= d[b]) dst -= d[b];

            state[offv[b] + dst]
                = tmp[offv[b] + r];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> MOD >> Q;

    /*
        Blocks:

        block 0 : dimension 1
        block j : dimension m_{j+1}, 1 <= j < n
        block n : dimension 1
    */
    d.assign(n + 1, 1);

    for (int i = 2; i <= n; ++i) {
        int m;
        cin >> m;
        d[i - 1] = m;
    }

    B = n + 1;

    offv.assign(B + 1, 0);

    for (int i = 0; i < B; ++i) {
        offv[i + 1] = offv[i] + d[i];
    }

    S = offv[B];

    /*
        T_0 corresponds to processing x = 0.

        f(0) = 0.

        One point update, because stages are updated in increasing
        order, allows a contribution from block j to propagate to
        every later block i.

        Therefore every block (i,j), i > j, has

            [0][0] = 1.
    */
    Mat T0(S);

    for (int i = 1; i < B; ++i) {
        for (int j = 0; j < i; ++j) {
            size_t pos =
                (size_t)offv[i] * S + offv[j];

            T0.a[pos] = (u32)(1 % MOD);
        }
    }

    vector<Mat> pw;
    pw.reserve(MAXK + 1);

    pw.push_back(std::move(T0));

    /*
        T_k =
            Shift_{2^{k-1}-1}(T_{k-1})
            * T_{k-1}.
    */
    for (int k = 1; k <= MAXK; ++k) {
        u64 shift = (1ULL << (k - 1)) - 1;
        pw.push_back(buildNext(pw.back(), shift));
    }

    while (Q--) {
        u64 V;
        cin >> V;

        /*
            Need to process x = 0 ... V,
            total length = V + 1.
        */
        u64 len = V + 1;
        u64 base = 0;

        vector<u32> state(S, 0);
        state[offv[0]] = (u32)(1 % MOD);

        /*
            Decompose [0, V] into aligned power-of-two blocks.
        */
        for (int k = MAXK; k >= 0; --k) {
            if (((len >> k) & 1ULL) == 0) {
                continue;
            }

            /*
                Current block:

                    [base, base + 2^k)

                base is divisible by 2^k.

                f(base + t) = f(base) + f(t).
            */
            u64 shift =
                base - (u64)__builtin_popcountll(base);

            applyShifted(state, pw[k], shift);

            base += (1ULL << k);
        }

        /*
            Final block n has dimension 1.
        */
        cout << state[offv[n]] << '\n';
    }

    return 0;
}