// @depends_on library/cpp/src/array/segment_tree.cpp

int main(void) {
  int n, q;
  scanf("%d%d", &n, &q);
  auto seg = procon::RangeMinQuery<int>(n);
  while (q--) {
    int com, x, y;
    scanf("%d%d%d", &com, &x, &y);
    if (com)
      printf("%d\n", seg.query(x, y + 1));
    else
      seg.update(x, y);
  }
  return 0;
}
