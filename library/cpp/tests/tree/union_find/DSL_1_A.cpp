// @depends_on library/cpp/src/tree/union_find.cpp

int main(void) {
  int n, q;
  scanf("%d%d", &n, &q);
  procon::UnionFind uf(n);
  while (q--) {
    int com, x, y;
    scanf("%d%d%d", &com, &x, &y);
    if (com)
      printf("%d\n", uf.is_same_set(x, y));
    else
      uf.unite(x, y);
  }
  return 0;
}
