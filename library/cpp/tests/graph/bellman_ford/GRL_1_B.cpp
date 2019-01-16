// @depends_on library/cpp/src/graph/bellman_ford.cpp

int main() {
  int V, E, r;
  scanf("%d%d%d", &V, &E, &r);
  using Graph = procon::WeightedGraph<int>;
  Graph g(V);
  while (E--) {
    int s, t, d;
    scanf("%d%d%d", &s, &t, &d);
    g.add_edge(s, t, d);
  }
  std::vector<int> dist;
  bool no_negative_cycle = procon::bellman_ford(g, r, dist);
  if (!no_negative_cycle) {
    printf("NEGATIVE CYCLE\n");
  } else {
    for (auto d : dist) {
      if (d == Graph::inf_cost) {
        printf("INF\n");
      } else {
        printf("%d\n", d);
      }
    }
  }
  return 0;
}
