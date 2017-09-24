
//#define TESTL

struct Linear {
  static const int INF = 0x3fffffff;
  vector<ll> a;
  vector<ll> b;
  vector<ll> t;

#ifdef TESTL
  vector<ll> aa, ab;
#endif

  ll get(ll x) {
    int id = upper_bound(t.begin(), t.end(), x) - t.begin();
    assert(id != 0);
    id--;
    ll res = a[id] * x + b[id];
#ifdef TESTL
    ll res2 = -(1LL << 60);
    int rid = -1;
    for (int i = 0; i < (int) aa.size(); i++) {
      if (res2 < aa[i] * x + ab[i]) {
        rid = i;
        res2 = aa[i] * x + ab[i];
      }
    }
    fprintf(stderr, "get %p %lld => %lld == %lld?\n", this, x, res, res2);
    if (res != res2) {
      fprintf(stderr, "%lld,%lld %lld,%lld\n", a[id], b[id], aa[rid], ab[rid]);
      for (int i = 0; i < (int)a.size(); i++) {
        printf("%lld %lld %lld\n", a[i], b[i], t[i]);
      }
    }
    assert(res == res2);
#endif
    return res;
  }

  void add(ll na, ll nb) {
#ifdef TESTL
    fprintf(stderr, "add %p %lld %lld\n", this, na, nb);
    aa.push_back(na);
    ab.push_back(nb);
#endif
    while (!t.empty() && na * t.back() + nb > a.back() * t.back() + b.back()) {
      a.pop_back();
      b.pop_back();
      t.pop_back();
    }

    if (t.empty()) {
      a.push_back(na);
      b.push_back(nb);
      t.push_back(0);
      return;
    }
    assert(na >= a.back());
    // a1 * x + b1 > a2 * x + b2
    // (a1 - a2) * x > b2 - b1

    ll nt = (b.back() - nb + na - a.back() - 1) / (na - a.back());
    //printf("%lld,%lld ; %lld,%lld -> %lld\n", na, nb, a.back(), b.back(), nt);
    assert(na * nt + nb >= a.back() * nt + b.back());
    assert(na * (nt - 1) + nb < a.back() * (nt - 1) + b.back());
    a.push_back(na);
    b.push_back(nb);
    t.push_back(nt);
  }
};
