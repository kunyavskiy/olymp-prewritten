const int MOD1 = 1000000007;
const int MOD2 = 1000000009;

struct HV {
  int f, s;

  bool operator<(const HV &rhs) const {
    if (f != rhs.f)
      return f < rhs.f;
    return s < rhs.s;
  }

  bool operator==(const HV &x) const {
    return f == x.f && s == x.s;
  }
};

HV operator+(const HV &a, const HV &b) {
  return {(a.f + b.f) % MOD1, (a.s + b.s) % MOD2};
}

HV operator-(const HV &a, const HV &b) {
  return {(a.f - b.f + MOD1) % MOD1, (a.s - b.s + MOD2) % MOD2};
}

HV operator*(const HV &a, const HV &b) {
  return {(int) ((a.f * 1LL * b.f) % MOD1), (int) ((a.s * 1LL * b.s) % MOD2)};
}
