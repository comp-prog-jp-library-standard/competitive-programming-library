// @depends_on library/cpp/src/graph/dijkstra.cpp

int main() {
  int V, E, r;
  scanf("%d%d%d", &V, &E, &r);
  // using Graph = procon::WeightedGraph<int>;
  using Graph = procon::WeightedGraph<int>;
  Graph g(V);
  while (E--) {
    int s, t, d;
    scanf("%d%d%d", &s, &t, &d);
    g.add_edge(s, t, d);
  }
  // auto dist = procon::dijkstra(g, r);
  std::vector<int> dist = procon::dijkstra(g, r);
  for (int d : dist) {
    if (d == Graph::inf_cost) {
      printf("INF\n");
    } else {
      printf("%d\n", d);
    }
  }
  return 0;
}
