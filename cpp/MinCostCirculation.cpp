class MinCostCirculation {
    struct Edge {
        int to, ne, w, c;
    };
    vector<Edge> es;
    vi firs;
    int curRes;

public:
    MinCostCirculation(int n) : es(), firs(n, -1), curRes(0) {}
    // from, to, capacity (max.flow), cost
    int adde(int a, int b, int w, int c) {
        Edge e;
        e.to = b; e.ne = firs[a];
        e.w = w; e.c = c;
        es.pb(e);
        firs[a] = sz(es) - 1;

        e.to = a; e.ne = firs[b];
        e.w = 0; e.c = -c;
        es.pb(e);
        firs[b] = sz(es) - 1;
        return sz(es) - 2;
    }
    // increase capacity of edge 'id' by 'w'
    void ince(int id, int w) {
        es[id].w += w;
    }
    int solve() {
        const int n = sz(firs);

        for (;;) {
            vi d(n, 0), fre(n, -1);
            vi chd(n, -1);

            int base = -1;
            for (int step = 0; step < n; step++) { 
                for (int i = 0; i < sz(es); i++) if (es[i].w > 0) {
                        int b = es[i].to;
                        int a = es[i ^ 1].to; 
                        if (d[b] <= d[a] + es[i].c) continue;
                        d[b] = d[a] + es[i].c;
                        fre[b] = i;
                        if (step == n - 1)
                            base = b;
                    }
            }
            if (base < 0) break;

            vi seq;
            vb was(n, false);/*BOXNEXT*/
            for (int x = base;; x = es[fre[x] ^ 1].to) {
                if (!was[x]) {
                    seq.pb(x);
                    was[x] = true;
                } else {
                    seq.erase(
                            seq.begin(),
                            find(seq.begin(), seq.end(),
                                 x
                            ));
                    break;
                }
            }
            int minv = inf;
            for (int i = 0; i < sz(seq); i++) {
                int v = seq[i];
                int eid = fre[v];
                minv = min(minv, es[eid].w);
            }
            for (int i = 0; i < sz(seq); i++) {
                int v = seq[i];
                int eid = fre[v];
                assert(es[eid].w > 0);
                es[eid].w -= minv;
                es[eid ^ 1].w += minv;
                curRes += es[eid].c * minv;
            }
        }
        return curRes;
    }
};

