constexpr bool is_prime(int x) {
  // TODO: Support C++11
  for (int d = 2; d * d <= x; ++d) {
    if (x % d == 0) {
      return false;
    }
  }
  return true;
}

template <int M> class Modulo {
  static constexpr bool has_inverse = is_prime(M);
  int n;
  static typename std::enable_if<has_inverse, long long>::type
  inv(long long a, long long p) {
    return (a == 1 ? 1 : (1 - p * inv(p % a, a)) / a + p);
  }

public:
  Modulo() : n(0) { ; }
  Modulo(int m) : n(m) {
    if (n >= M)
      n %= M;
    else if (n < 0)
      n = (n % M + M) % M;
  }
  Modulo(long long m) {
    if (m >= M)
      m %= M;
    else if (m < 0)
      m = (m % M + M) % M;
    n = m;
  }
  explicit operator int() const { return n; }
  explicit operator long long() const { return n; }
  bool operator==(const Modulo &a) const { return n == a.n; }
  Modulo &operator+=(const Modulo &a) {
    n += a.n;
    if (n >= M)
      n -= M;
    return *this;
  }
  Modulo &operator-=(const Modulo &a) {
    n -= a.n;
    if (n < 0)
      n += M;
    return *this;
  }
  Modulo &operator*=(const Modulo &a) {
    n = (static_cast<long long>(n) * a.n) % M;
    return *this;
  }
  Modulo operator+(const Modulo &a) const {
    Modulo res = *this;
    return res += a;
  }
  Modulo operator-(const Modulo &a) const {
    Modulo res = *this;
    return res -= a;
  }
  Modulo operator-() const { return Modulo(0) - *this; }
  Modulo operator*(const Modulo &a) const {
    Modulo res = *this;
    return res *= a;
  }
  friend Modulo pow(const Modulo &x, long long m) {
    if (m == 0)
      return Modulo(1);
    const Modulo a = x;
    Modulo res = pow(a * a, m / 2);
    return m % 2 ? res * a : res;
  }
  typename std::enable_if<has_inverse, Modulo>::type
  operator/(const Modulo &a) const {
    return *this * inv(static_cast<long long>(a), M);
  }
  typename std::enable_if<has_inverse, Modulo>::type
  operator/=(const Modulo &a) {
    return *this *= inv(static_cast<long long>(a), M);
  }
};
