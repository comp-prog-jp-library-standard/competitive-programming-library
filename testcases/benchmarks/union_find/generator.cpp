#include <cassert>
#include <cstdio>
#include <fstream>
#include <random>
#include <vector>

struct Query {
  const uint64_t com;
  Query(uint8_t op, uint32_t x1, uint32_t x2)
      : com((uint64_t{op} & 0x0000000000000000f) << 60 |
            (uint64_t{x1} & 0x000000003ffffffff) << 30 |
            (uint64_t{x2} & 0x000000003ffffffff)) {}
};

void output(const char *name, int array_size, const std::vector<Query> &query) {
  char filename[128];
  static int id = 0;
  sprintf(filename, "%.3d_%s.in", id++, name);
  std::ofstream os(filename, std::ofstream::binary);

  const int N = array_size;
  const int Q = query.size();
  os.write((char *)&N, sizeof(int));
  os.write((char *)&Q, sizeof(int));
  os.write((char *)query.data(), sizeof(Query) * query.size());
}

void random_case(int seed, int array_size, int query_size) {
  std::mt19937 mt(seed);
  std::vector<Query> query;
  query.reserve(query_size);
  for (int i = 0; i < query_size; ++i) {
    const int com = mt() & 1;
    const int x = mt() % array_size;
    const int y = mt() % array_size;
    query.emplace_back(com, x, y);
  }
  output("random", array_size, query);
}

int main() {
  int array_size = 1000000;
  int query_size = 10000000;
  for (int i = 0; i < 20; ++i) {
    random_case(i, array_size, query_size);
    array_size *= 1.08;
    query_size *= 1.08;
  }
}
