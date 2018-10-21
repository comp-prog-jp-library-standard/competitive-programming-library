namespace procon {
namespace internal {
template <class Op> class SegmentTree {
  using I = typename Op::value_type;
  int n;
  std::vector<I> dat;

public:
  typedef int size_type;
  SegmentTree(size_type n_) {
    n = 1;
    while (n < n_)
      n *= 2; // n is a power of 2
    dat.resize(2 * n);
    for (int i = 0; i < 2 * n - 1; i++) {
      dat[i] = Op::id;
    }
  }
  /* ary[k] <- v */
  void update(size_type k, typename Op::value_type v) {
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
  typename Op::value_type query(size_type a, size_type b) const {
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
  typename Op::value_type operator[](size_type idx) const {
    return dat[idx + n - 1];
  }
  size_type size() const { return n; }
};

template <class T> class generic_min {
public:
  using value_type = T;
  static const T id = std::numeric_limits<T>::max();
  static T op(T x, T y) { return std::min(x, y); }
};

template <class T> class generic_max {
public:
  using value_type = T;
  static const T id = std::numeric_limits<T>::min();
  static T op(T x, T y) { return std::max(x, y); }
};

template <class T> class generic_sum {
public:
  using value_type = T;
  static const T id = 0;
  static T op(T x, T y) { return x + y; }
};
} // namespace internal

template <class I>
internal::SegmentTree<internal::generic_min<I>> make_range_min_query(int n) {
  return internal::SegmentTree<internal::generic_min<I>>(n);
}

template <class I>
internal::SegmentTree<internal::generic_max<I>> make_range_max_query(int n) {
  return internal::SegmentTree<internal::generic_max<I>>(n);
}

template <class I>
internal::SegmentTree<internal::generic_sum<I>> make_range_sum_query(int n) {
  return internal::SegmentTree<internal::generic_sum<I>>(n);
}
} // namespace procon
