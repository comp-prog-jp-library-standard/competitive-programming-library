// @depends_on library/cpp/src/graph/graph.cpp

namespace procon {

template <typename Graph>
typename Graph::template map_value<typename Graph::cost_type>
dijkstra(const Graph &g, typename Graph::node_type start) {
  using node_type = typename Graph::node_type;
  using cost_type = typename Graph::cost_type;
  using map_value = typename Graph::template map_value<cost_type>;
  map_value d(g.size(), Graph::inf_cost);
  d[start] = Graph::zero_cost;
  using P = std::pair<cost_type, node_type>;
  std::priority_queue<P, std::vector<P>, std::greater<P>> que;
  que.emplace(d[start], start);
  while (!que.empty()) {
    cost_type dist = que.top().first;
    int v = que.top().second;
    que.pop();
    if (dist > d[v]) {
      continue;
    }
    for (const auto &e : g[v]) {
      cost_type new_dist = d[v] + e.weight;
      if (d[e.to] <= new_dist)
        continue;
      d[e.to] = new_dist;
      que.emplace(new_dist, e.to);
    }
  }
  return d;
}

} // namespace procon
