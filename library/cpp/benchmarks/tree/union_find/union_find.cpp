// @depends_on library/cpp/src/tree/union_find.cpp

int main(void) {
  int size, n_query;
  std::cin.read((char*)&size, sizeof(int));
  std::cin.read((char*)&n_query, sizeof(int));

  std::vector<uint64_t> query(n_query);
  std::cin.read((char*)query.data(), sizeof(uint64_t) * n_query);

  const int mask = (1 << 30) - 1;

  uint64_t res = 123456789;
  procon::UnionFind uf(size);
  for (uint64_t q: query) {
    const int com = q >> 60;
    const int x = (q >> 30) & mask;
    const int y = (q >> 0) & mask;
    assert (0 <= x && x < size);
    assert (0 <= y && y < size);
    if (com) {
      res = res * 17 + (uf.is_same_set(x, y) ? 1 : 0);
    } else {
      uf.unite(x, y);
    }
  }
  std::cout << res << std::endl;
  return 0;
}
