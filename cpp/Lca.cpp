int lca(int u, int v) {
  if (h[u] < h[v]) swap(u, v);
  for (int i = MAXLOG - 1; i >= 0; i--) {
    if (h[up[i][u]] >= h[v]) {
      u = up[i][u];
    }
  }
  if (u == v) return u;

  for (int i = MAXLOG - 1; i >= 0; i--) {
    if (up[i][u] != up[i][v]) {
      u = up[i][u];
      v = up[i][v];
    }
  }
  return up[0][v];
}

void init_lca(int n) {
  for (int i = 1; i < MAXLOG; i++) {
    for (int j = 0; j < n; j++) {
      up[i][j] = up[i - 1][up[i - 1][j]];
    }
  }
}

