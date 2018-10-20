namespace procon {
namespace internal {
template <class I, class BiOp> class SegmentTree {
  int n;
  std::vector<I> dat;
  BiOp op;
  I e;

public:
  typedef int size_type;
  typedef I value_type;
  SegmentTree(size_type n_, BiOp op, value_type e) : op(op), e(e) {
    n = 1;
    while (n < n_)
      n *= 2; // n is a power of 2
    dat.resize(2 * n);
    for (int i = 0; i < 2 * n - 1; i++) {
      dat[i] = e;
    }
  }
  /* ary[k] <- v */
  void update(size_type k, value_type v) {
    k += n - 1;
    dat[k] = v;
    while (k > 0) {
      k = (k - 1) / 2;
      dat[k] = op(dat[2 * k + 1], dat[2 * k + 2]);
    }
  }
  /* http://proc-cpuinfo.fixstars.com/2017/07/optimize-segment-tree/
   * [a, b)
   */
  value_type query(size_type a, size_type b) const {
    value_type left = e;
    value_type right = e;
    a += n - 1;
    b += n - 1;
    while (a < b) {
      if ((a & 1) == 0) {
        left = op(left, dat[a]);
      }
      if ((b & 1) == 0) {
        right = op(dat[b - 1], right);
      }
      a = a / 2;
      b = (b - 1) / 2;
    }
    return op(left, right);
  }
  value_type operator[](size_type idx) const { return dat[idx + n - 1]; }
  size_type size() const { return n; }
};

template <class T> class generic_min {
public:
  T operator()(T x, T y) const { return min(x, y); }
};

template <class T> class generic_max {
public:
  T operator()(T x, T y) const { return max(x, y); }
};
} // namespace internal

template <class I, class BiOp>
internal::SegmentTree<I, BiOp> make_segment_tree(int size, BiOp op, I e) {
  internal::SegmentTree<I, BiOp> tree(size, op, std::move(e));
  return tree;
}

template <class I>
internal::SegmentTree<I, internal::generic_min<I>>
make_range_min_query(int n, I infinity) {
  make_segment_tree(n, internal::generic_min<I>(), infinity);
}

template <class I>
internal::SegmentTree<I, internal::generic_max<I>>
make_range_max_query(int n, I negative_infinity) {
  make_segment_tree(n, internal::generic_max<I>(), negative_infinity);
}

template <class I>
internal::SegmentTree<I, std::plus<I>> make_range_sum_query(int n, I zero) {
  make_segment_tree(n, std::plus<I>(), zero);
}
} // namespace procon
