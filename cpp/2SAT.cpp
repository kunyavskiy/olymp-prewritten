#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <map>
#include <cstring>
#include <string>
#include <cmath>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <sstream>
#include <list>
#include <queue>
#include <deque>
#include <stack>
#include <cstdlib>
#include <cstdio>
#include <iterator>
#include <functional>
#include <bitset>

#ifdef LOCAL
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
#else
#define eprintf(...)
#endif

#define TIMESTAMP(x) eprintf("["#x"] Time : %.3lf s.\n", clock()*1.0/CLOCKS_PER_SEC)
#define TIMESTAMPf(x,...) eprintf("[" x "] Time : %.3lf s.\n", __VA_ARGS__, clock()*1.0/CLOCKS_PER_SEC)

using namespace std;

#ifdef LOCAL
static struct __timestamper {
  string what;
  __timestamper(const char* what) : what(what){};
  __timestamper(const string& what) : what(what){};
  ~__timestamper(){
    TIMESTAMPf("%s", what.data());
	}
} __TIMESTAMPER("end");
#else 
struct __timestamper {};
#endif

typedef long long ll;
typedef long double ld;


class TwoSatSolver {
  vector<vector<int>> g;
  vector<vector<int>> gt;
  vector<int> ts;
  vector<int> comp;
  vector<bool> used;

  void addEdge(int a, int av, int b, int bv) {
    g[2 * a + av].push_back(2 * b + bv);
    gt[2 * b + bv].push_back(2 * a + av);
  }

  void dfs_ts(int v) {
    if (used[v]) return;
    used[v] = true;
    for (int u : g[v]) {
      dfs_ts(u);
    }
    ts.push_back(v);
  }

  void dfs_comp(int v, int c) {
    if (comp[v] != -1) {
      return;
    }
    comp[v] = c;
    for (int u : gt[v]) {
      dfs_comp(u, c);
    }
  }

public:

  TwoSatSolver(int n) {
    g.resize(2 * n);
    gt.resize(2 * n);
  }

  int getN() {
    return (int)g.size() / 2;
  }

  int addVertex() {
    int n = (int) g.size() / 2;
    g.push_back(vector<int>());
    g.push_back(vector<int>());
    gt.push_back(vector<int>());
    gt.push_back(vector<int>());
    return n;
  }

  void addOr(int a, int av, int b, int bv) {
    eprintf("%cx%d || %cx%d = true\n", av ? ' ' : '!', a, bv ? ' ' : '!', b);
    addEdge(a, !av, b, bv);
    addEdge(b, !bv, a, av);
  }

  void addTrue(int a, int av) {
    eprintf("%cx%d = true\n", av ? ' ' : '!', a);
    addEdge(a, !av, a, av);
  }


  vector<bool> solve() {
    int n = g.size() / 2;
    used = vector<bool>(2 * n);
    comp = vector<int>(2 * n, -1);

    vector<bool> res(n);

    for (int i = 0; i < 2 * n; i++) {
      dfs_ts(i);
    }
    reverse(ts.begin(), ts.end());
    for (int i = 0; i < 2 * n; i++) {
      dfs_comp(ts[i], i);
    }

    for (int i = 0; i < n; i++) {
      if (comp[2 * i] == comp[2 * i + 1]) {
        return vector<bool>();
      }
      res[i] = comp[2 * i + 1] > comp[2 * i];
    }
    return res;
  }
};


int main() {
#ifdef LOCAL
  freopen("2sat.in", "r", stdin);
  freopen("2sat.out", "w", stdout);
#endif

  return 0;
}
