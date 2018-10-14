/*
 * Union-Find tree
 * header requirement: vector
 */
namespace procon {
class UnionFind {
private:
  struct nodeinfo {
    int par;
    int rank;
    nodeinfo(int par) : par(par), rank(0) {}
  };
  std::vector<nodeinfo> node;

public:
  UnionFind(int n) : node() {
    node.reserve(n);
    for (int i = 0; i < n; ++i) {
      node.emplace_back(i);
    }
  }
  int root(int x) {
    if (node[x].par == x) {
      return x;
    }
    return node[x].par = root(node[x].par);
  }
  void unite(int x, int y) {
    x = root(x);
    y = root(y);
    if (x == y) {
      return;
    }
    if (node[x].rank < node[y].rank) {
      node[x].par = y;
    } else {
      node[y].par = x;
      if (node[x].rank == node[y].rank) {
        ++node[x].rank;
      }
    }
  }
  bool is_same_set(int x, int y) { return root(x) == root(y); }
};
} // namespace procon
