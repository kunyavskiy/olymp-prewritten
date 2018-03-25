// number of (x, y) : (0 <= x < n && 0 < y < k/d x + b/d)
ll points_under_line(ll n, ll k, ll b, ll d) {
  if (k == 0) {
    return (b / d) * n;
  }
  if (k >= d || b >= d) {
    return ((k / d) * (n - 1) + 2 * (b / d)) * n / 2 + points_under_line(n, k % d, b % d, d);
  }
  return points_under_line((k * n + b) / d, d, (k * n + b) % d, k);
}

