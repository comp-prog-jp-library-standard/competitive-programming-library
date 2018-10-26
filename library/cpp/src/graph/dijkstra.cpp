// @depends_on library/cpp/src/graph/graph.cpp

namespace procon {

namespace internal {

template <typename Cost, typename Node, typename Compare> struct PQueOrder {
  Cost cost;
  Node node;
  PQueOrder(Cost c, Node n) : cost(std::move(c)), node(std::move(n)) { ; }
};

template <typename Cost, typename Node, typename Compare>
bool operator<(const PQueOrder<Cost, Node, Compare> &lhs,
               const PQueOrder<Cost, Node, Compare> &rhs) {
  return Compare()(rhs.cost, lhs.cost);
}

} // namespace internal

template <typename Graph>
typename Graph::template map_value<typename Graph::cost_type>
dijkstra(const Graph &g, typename Graph::node_type start) {
  using node_type = typename Graph::node_type;
  using cost_type = typename Graph::cost_type;
  using compare = typename Graph::compare;
  using add = typename Graph::add;
  using map_value = typename Graph::template map_value<cost_type>;
  map_value d(g.size(), Graph::inf_cost);
  d[start] = Graph::zero_cost;
  std::priority_queue<internal::PQueOrder<cost_type, node_type, compare>> que;
  que.emplace(d[start], start);
  while (!que.empty()) {
    cost_type dist = que.top().cost;
    node_type v = que.top().node;
    que.pop();
    if (compare()(d[v], dist)) {
      continue;
    }
    for (const auto &e : g[v]) {
      cost_type new_dist = add()(d[v], e.weight);
      if (!compare()(new_dist, d[e.to]))
        continue;
      d[e.to] = new_dist;
      que.emplace(new_dist, e.to);
    }
  }
  return d;
}

} // namespace procon
