// @depends_on library/cpp/src/tree/union_find.cpp

int main(void) {
  int log_size;
  int n_query;
  int seed;
  std::cin >> log_size >> n_query >> seed;

  assert (0 <= log_size && log_size <= 30);
  assert (0 <= n_query);

  const int size = 1 << log_size;
  const int mask = size - 1;
  uint64_t res = 123456789;

  std::mt19937 mt(seed);
  procon::UnionFind uf(size);
  while (n_query--) {
    const int com = mt() & 1;
    const int x = mt() & mask;
    const int y = mt() & mask;
    if (com) {
      res = res * 17 + (uf.is_same_set(x, y) ? 1 : 0);
    }
    else {
      uf.unite(x, y);
    }
  }
  std::cout << res << std::endl;
  return 0;
}
