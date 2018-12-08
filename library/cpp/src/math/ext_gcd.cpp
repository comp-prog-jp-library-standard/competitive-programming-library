namespace procon {
/*
 * Performs extended Euclidean algorithm.
 * Return g = gcd(a, b), and overwrites x and y with values that satisfy
 * a * x + b * y = g.
 */
template <class T> T ext_gcd(T a, T b, T &x, T &y) {
  static_assert(std::is_integral<T>::value, "T should be an integral value");
  if (b == 0) {
    x = 1;
    y = 0;
    return a;
  }
  T q = a / b;
  T g = ext_gcd(b, a - q * b, x, y);
  T z = x - q * y;
  x = y;
  y = z;
  return g;
}
} // namespace procon
