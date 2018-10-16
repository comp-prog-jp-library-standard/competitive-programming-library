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
  SegmentTree(int n_, BiOp op, I e) : op(op), e(e) {
    n = 1;
    while (n < n_)
      n *= 2; // n is a power of 2
    dat.resize(2 * n);
    for (int i = 0; i < 2 * n - 1; i++) {
      dat[i] = e;
    }
  }
  /* ary[k] <- v */
  void update(int k, I v) {
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
  I query(int a, int b) const {
    I left = e;
    I right = e;
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
  I operator[](int idx) const { return dat[idx + n - 1]; }
};
} // namespace internal

template <class I, class BiOp>
internal::SegmentTree<I, BiOp> make_segment_tree(int size, BiOp op, I e) {
  internal::SegmentTree<I, BiOp> tree(size, op, std::move(e));
  return tree;
}
} // namespace procon
