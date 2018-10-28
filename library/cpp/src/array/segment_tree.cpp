namespace procon {
namespace internal {
template <class T> class generic_min {
public:
  using value_type = T;
  static const T id;
  static T op(T x, T y) { return std::min(x, y); }
};
template <class T> const T generic_min<T>::id = std::numeric_limits<T>::max();

template <class T> class generic_max {
public:
  using value_type = T;
  static const T id;
  static T op(T x, T y) { return std::max(x, y); }
};
template <class T> const T generic_max<T>::id = std::numeric_limits<T>::min();

template <class T> class generic_sum {
public:
  using value_type = T;
  static const T id = 0;
  static T op(T x, T y) { return x + y; }
};
} // namespace internal

template <class Op> class SegmentTree {
  const int n;
  std::vector<typename Op::value_type> dat;
  static int calculate_size(int n_) {
    int n = 1;
    while (n < n_)
      n *= 2; // n is a power of 2
    return n;
  }

public:
  typedef int size_type;
  using value_type = typename Op::value_type;
  SegmentTree(size_type size)
      : n(calculate_size(size)), dat(2 * n - 1, Op::id) {}
  /* ary[k] <- v */
  void update(size_type k, value_type v) {
    k += n - 1;
    dat[k] = v;
    while (k > 0) {
      k = (k - 1) / 2;
      dat[k] = Op::op(dat[2 * k + 1], dat[2 * k + 2]);
    }
  }
  /* http://proc-cpuinfo.fixstars.com/2017/07/optimize-segment-tree/
   * [a, b)
   */
  value_type query(size_type a, size_type b) const {
    typename Op::value_type left = Op::id;
    typename Op::value_type right = Op::id;
    a += n - 1;
    b += n - 1;
    while (a < b) {
      if ((a & 1) == 0) {
        left = Op::op(left, dat[a]);
      }
      if ((b & 1) == 0) {
        right = Op::op(dat[b - 1], right);
      }
      a = a / 2;
      b = (b - 1) / 2;
    }
    return Op::op(left, right);
  }
  value_type operator[](size_type idx) const { return dat[idx + n - 1]; }
  size_type size() const { return n; }
};

template <class I> using RangeMinQuery = SegmentTree<internal::generic_min<I>>;
template <class I> using RangeMaxQuery = SegmentTree<internal::generic_max<I>>;
template <class I> using RangeSumQuery = SegmentTree<internal::generic_sum<I>>;
} // namespace procon
