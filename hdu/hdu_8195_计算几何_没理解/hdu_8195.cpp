
#include <iostream>
#include <cstdint>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

using ll = long long;
using i128 = __int128_t;

static const int INF = 1e9;
static const uint16_t DINF = 65535;

struct Dir {
    ll x, y;
};

static inline i128 cross(const Dir& a, const Dir& b) {
    return (i128)a.x * b.y - (i128)a.y * b.x;
}

static inline Dir negDir(const Dir& a) {
    return {-a.x, -a.y};
}

static inline int halfPlane(const Dir& a) {
    return (a.y > 0 || (a.y == 0 && a.x >= 0)) ? 0 : 1;
}

static bool polarLess(const Dir& a, const Dir& b) {
    int ha = halfPlane(a), hb = halfPlane(b);
    if (ha != hb) return ha < hb;
    i128 c = cross(a, b);
    if (c != 0) return c > 0;
    return false;
}

static inline pair<ll,ll> keyOf(const Dir& a) {
    return {a.x, a.y};
}

static ll gcdll(ll a, ll b) {
    while (b) {
        ll t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<ll> x(n), y(n);
    vector<Dir> dir(n);
    vector<char> nonzero(n, false);
    vector<int> nz;

    for (int i = 0; i < n; ++i) {
        cin >> x[i] >> y[i];

        if (x[i] == 0 && y[i] == 0) {
            dir[i] = {0, 0};
            continue;
        }

        ll g = gcdll(llabs(x[i]), llabs(y[i]));
        dir[i] = {x[i] / g, y[i] / g};
        nonzero[i] = true;
        nz.push_back(i);
    }

    vector<vector<int>> adj(n);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].push_back(v);
    }

    // ------------------------------------------------------------
    // 1. APSP: every source runs BFS.
    // Shortest simple path has length <= n - 1 <= 3999,
    // so uint16_t is sufficient.
    // ------------------------------------------------------------
    vector<uint16_t> dist((size_t)n * n, DINF);

    vector<int> q(n);

    for (int s = 0; s < n; ++s) {
        uint16_t* row = dist.data() + (size_t)s * n;
        fill(row, row + n, DINF);

        int ql = 0, qr = 0;
        q[qr++] = s;
        row[s] = 0;

        while (ql < qr) {
            int u = q[ql++];

            for (int v : adj[u]) {
                if (row[v] == DINF) {
                    row[v] = row[u] + 1;
                    q[qr++] = v;
                }
            }
        }
    }

    // If there aren't even 3 non-zero points, impossible.
    if ((int)nz.size() < 3) {
        for (int i = 0; i < n; ++i)
            cout << -1 << '\n';
        return 0;
    }

    // ------------------------------------------------------------
    // 2. Directed ray groups.
    // ------------------------------------------------------------
    map<pair<ll,ll>, int> rayMap;
    vector<Dir> rayDir;
    vector<vector<int>> rayVerts;
    vector<int> rayId(n, -1);

    for (int v : nz) {
        auto k = keyOf(dir[v]);
        auto it = rayMap.find(k);

        int id;
        if (it == rayMap.end()) {
            id = (int)rayDir.size();
            rayMap[k] = id;
            rayDir.push_back(dir[v]);
            rayVerts.push_back({});
        } else {
            id = it->second;
        }

        rayId[v] = id;
        rayVerts[id].push_back(v);
    }

    int R = rayDir.size();

    vector<int> oppRay(R, -1);
    for (int g = 0; g < R; ++g) {
        Dir nd = negDir(rayDir[g]);
        auto it = rayMap.find(keyOf(nd));
        if (it != rayMap.end())
            oppRay[g] = it->second;
    }

    // ------------------------------------------------------------
    // 3. Direction universe:
    // every existing direction + every opposite direction.
    // Used for the strict-triangle angular scans.
    // ------------------------------------------------------------
    vector<Dir> uni;
    uni.reserve(2 * nz.size());

    for (int v : nz) {
        uni.push_back(dir[v]);
        uni.push_back(negDir(dir[v]));
    }

    sort(uni.begin(), uni.end(), polarLess);

    uni.erase(
        unique(uni.begin(), uni.end(),
               [](const Dir& a, const Dir& b) {
                   return a.x == b.x && a.y == b.y;
               }),
        uni.end()
    );

    int U = uni.size();

    map<pair<ll,ll>, int> uniMap;
    for (int i = 0; i < U; ++i)
        uniMap[keyOf(uni[i])] = i;

    vector<int> dirPos(n, -1), oppPos(n, -1);

    for (int v : nz) {
        dirPos[v] = uniMap[keyOf(dir[v])];
        oppPos[v] = uniMap[keyOf(negDir(dir[v]))];
    }

    // ------------------------------------------------------------
    // 4. Undirected line classes (angle modulo pi).
    //
    // canonical direction is chosen inside [0, pi).
    // lineSign[v] tells which of the two rays v belongs to.
    // ------------------------------------------------------------
    vector<Dir> canonical(n);
    vector<int> lineSign(n, 0);

    vector<Dir> lineList;
    lineList.reserve(nz.size());

    for (int v : nz) {
        Dir d = dir[v];

        if (d.y < 0 || (d.y == 0 && d.x < 0)) {
            canonical[v] = negDir(d);
            lineSign[v] = -1;
        } else {
            canonical[v] = d;
            lineSign[v] = +1;
        }

        lineList.push_back(canonical[v]);
    }

    sort(lineList.begin(), lineList.end(), polarLess);

    lineList.erase(
        unique(lineList.begin(), lineList.end(),
               [](const Dir& a, const Dir& b) {
                   return a.x == b.x && a.y == b.y;
               }),
        lineList.end()
    );

    int L = lineList.size();

    map<pair<ll,ll>, int> lineMap;
    for (int i = 0; i < L; ++i)
        lineMap[keyOf(lineList[i])] = i;

    vector<int> lineId(n, -1);
    for (int v : nz)
        lineId[v] = lineMap[keyOf(canonical[v])];

    // finish[v] = minimum length at the moment the geometric
    // condition has already become true and current vertex is v.
    vector<int> finish(n, INF);

    // ============================================================
    // PART I: strict triangle
    // ============================================================
    vector<int> val(U), prefCCW(U), prefCW(U);

    for (int b : nz) {
        fill(val.begin(), val.end(), INF);

        // W_b(a) = D(1,a) + D(a,b)
        for (int a : nz) {
            uint16_t d1a = dist[a]; // dist[0][a]
            uint16_t dab = dist[(size_t)a * n + b];

            if (d1a == DINF || dab == DINF)
                continue;

            int w = (int)d1a + (int)dab;
            int p = dirPos[a];

            val[p] = min(val[p], w);
        }

        int p = oppPos[b];

        prefCCW[0] = INF;
        prefCW[0] = INF;

        for (int t = 1; t < U; ++t) {
            prefCCW[t] =
                min(prefCCW[t - 1], val[(p + t) % U]);

            prefCW[t] =
                min(prefCW[t - 1], val[(p - t + U) % U]);
        }

        for (int c : nz) {
            uint16_t dbc = dist[(size_t)b * n + c];
            if (dbc == DINF)
                continue;

            i128 cr = cross(dir[b], dir[c]);

            if (cr > 0) {
                int qpos = oppPos[c];
                int delta = (qpos - p + U) % U;

                // open interval: exclude -c itself.
                if (delta >= 1) {
                    int best = prefCCW[delta - 1];
                    if (best < INF)
                        finish[c] =
                            min(finish[c], best + (int)dbc);
                }
            } else if (cr < 0) {
                int qpos = oppPos[c];
                int delta = (p - qpos + U) % U;

                if (delta >= 1) {
                    int best = prefCW[delta - 1];
                    if (best < INF)
                        finish[c] =
                            min(finish[c], best + (int)dbc);
                }
            }
        }
    }

    // ============================================================
    // PART II-A:
    // positions (a,b) form the antipodal pair.
    //
    // a -> b -> c -> d
    // ============================================================
    vector<int> pairStart(n, INF);

    for (int b : nz) {
        int og = oppRay[rayId[b]];
        if (og < 0) continue;

        for (int a : rayVerts[og]) {
            uint16_t d1a = dist[a];
            uint16_t dab = dist[(size_t)a * n + b];

            if (d1a == DINF || dab == DINF)
                continue;

            pairStart[b] =
                min(pairStart[b], (int)d1a + (int)dab);
        }
    }

    vector<int> lineVal(L);
    vector<int> globalPref(L + 1), globalSuff(L + 1);
    vector<int> between(L);

    for (int c : nz) {
        fill(lineVal.begin(), lineVal.end(), INF);

        for (int b : nz) {
            if (pairStart[b] >= INF)
                continue;

            uint16_t dbc = dist[(size_t)b * n + c];
            if (dbc == DINF)
                continue;

            int id = lineId[b];

            lineVal[id] =
                min(lineVal[id], pairStart[b] + (int)dbc);
        }

        globalPref[0] = INF;
        for (int i = 0; i < L; ++i)
            globalPref[i + 1] =
                min(globalPref[i], lineVal[i]);

        globalSuff[L] = INF;
        for (int i = L - 1; i >= 0; --i)
            globalSuff[i] =
                min(globalSuff[i + 1], lineVal[i]);

        fill(between.begin(), between.end(), INF);

        int lc = lineId[c];

        int run = INF;
        for (int j = lc + 1; j < L; ++j) {
            between[j] = run;
            run = min(run, lineVal[j]);
        }

        run = INF;
        for (int j = lc - 1; j >= 0; --j) {
            between[j] = run;
            run = min(run, lineVal[j]);
        }

        for (int d : nz) {
            uint16_t dcd = dist[(size_t)c * n + d];
            if (dcd == DINF)
                continue;

            int ld = lineId[d];
            int best = INF;

            if (lineSign[c] == lineSign[d]) {
                // The separating line lies strictly between them.
                best = between[ld];
            } else {
                // Their ray orientations differ by pi:
                // the separating line is outside the interval.
                int lo = min(lc, ld);
                int hi = max(lc, ld);

                best = min(
                    globalPref[lo],
                    globalSuff[hi + 1]
                );
            }

            if (best < INF)
                finish[d] =
                    min(finish[d], best + (int)dcd);
        }
    }

    // ============================================================
    // PART II-B:
    // positions (a,c) form the antipodal pair.
    //
    // a -> b -> c -> d
    // ============================================================
    vector<int> fromOpp(n);

    for (int h = 0; h < R; ++h) {
        int og = oppRay[h];
        if (og < 0)
            continue;

        fill(fromOpp.begin(), fromOpp.end(), INF);

        // fromOpp[b] =
        // min_{a in opposite(h)} D(1,a) + D(a,b)
        for (int a : rayVerts[og]) {
            uint16_t d1a = dist[a];
            if (d1a == DINF)
                continue;

            const uint16_t* row =
                dist.data() + (size_t)a * n;

            for (int b : nz) {
                if (row[b] == DINF)
                    continue;

                fromOpp[b] =
                    min(fromOpp[b],
                        (int)d1a + (int)row[b]);
            }
        }

        for (int c : rayVerts[h]) {
            int bestLeft = INF;
            int bestRight = INF;

            for (int b : nz) {
                if (fromOpp[b] >= INF)
                    continue;

                uint16_t dbc = dist[(size_t)b * n + c];
                if (dbc == DINF)
                    continue;

                int cur = fromOpp[b] + (int)dbc;
                i128 cr = cross(dir[c], dir[b]);

                if (cr > 0)
                    bestLeft = min(bestLeft, cur);
                else if (cr < 0)
                    bestRight = min(bestRight, cur);
            }

            for (int d : nz) {
                uint16_t dcd = dist[(size_t)c * n + d];
                if (dcd == DINF)
                    continue;

                i128 cr = cross(dir[c], dir[d]);

                // d left -> b must be right
                if (cr > 0 && bestRight < INF) {
                    finish[d] =
                        min(finish[d],
                            bestRight + (int)dcd);
                }

                // d right -> b must be left
                if (cr < 0 && bestLeft < INF) {
                    finish[d] =
                        min(finish[d],
                            bestLeft + (int)dcd);
                }
            }
        }
    }

    // ============================================================
    // PART II-C:
    // positions (b,c) form the antipodal pair.
    //
    // a -> b -> c -> d
    // ============================================================
    vector<int> leftBest(n, INF), rightBest(n, INF);

    for (int b : nz) {
        for (int a : nz) {
            uint16_t d1a = dist[a];
            uint16_t dab = dist[(size_t)a * n + b];

            if (d1a == DINF || dab == DINF)
                continue;

            int cur = (int)d1a + (int)dab;
            i128 cr = cross(dir[b], dir[a]);

            if (cr > 0)
                leftBest[b] =
                    min(leftBest[b], cur);
            else if (cr < 0)
                rightBest[b] =
                    min(rightBest[b], cur);
        }
    }

    vector<int> preLeft(n, INF), preRight(n, INF);

    for (int c : nz) {
        int og = oppRay[rayId[c]];
        if (og < 0)
            continue;

        for (int b : rayVerts[og]) {
            uint16_t dbc = dist[(size_t)b * n + c];
            if (dbc == DINF)
                continue;

            if (leftBest[b] < INF)
                preLeft[c] =
                    min(preLeft[c],
                        leftBest[b] + (int)dbc);

            if (rightBest[b] < INF)
                preRight[c] =
                    min(preRight[c],
                        rightBest[b] + (int)dbc);
        }
    }

    for (int c : nz) {
        for (int d : nz) {
            uint16_t dcd = dist[(size_t)c * n + d];
            if (dcd == DINF)
                continue;

            i128 cr = cross(dir[c], dir[d]);

            // b is opposite to c.
            // If d is left of c, it is right of b,
            // therefore a must have been left of b.
            if (cr > 0 && preLeft[c] < INF) {
                finish[d] =
                    min(finish[d],
                        preLeft[c] + (int)dcd);
            }

            if (cr < 0 && preRight[c] < INF) {
                finish[d] =
                    min(finish[d],
                        preRight[c] + (int)dcd);
            }
        }
    }

    // ------------------------------------------------------------
    // 5. Once successful, just travel from the successful endpoint
    //    to the final requested vertex k.
    // ------------------------------------------------------------
    vector<int> ans(n, INF);

    for (int c : nz) {
        if (finish[c] >= INF)
            continue;

        const uint16_t* row =
            dist.data() + (size_t)c * n;

        for (int k = 0; k < n; ++k) {
            if (row[k] == DINF)
                continue;

            ans[k] =
                min(ans[k],
                    finish[c] + (int)row[k]);
        }
    }

    for (int k = 0; k < n; ++k) {
        if (ans[k] >= INF)
            cout << -1 << '\n';
        else
            cout << ans[k] << '\n';
    }

    return 0;
}