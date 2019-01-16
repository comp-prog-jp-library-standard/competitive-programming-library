// @depends_on library/cpp/src/graph/graph.cpp

namespace procon {

template <typename Graph>
bool bellman_ford(
    const Graph &g, typename Graph::node_type start,
    typename Graph::template map_value<typename Graph::cost_type> &d) {
  using node_type = typename Graph::node_type;
  using cost_type = typename Graph::cost_type;
  using compare_lt = typename Graph::cost_compare_lt;
  using compare_eq = typename Graph::cost_compare_eq;
  using add = typename Graph::cost_add;
  d.resize(g.size(), Graph::inf_cost);
  d[start] = Graph::zero_cost;
  unsigned int max_update_count = (unsigned int)g.size();
  for (unsigned int c = 1; c <= max_update_count; c++) {
    for (node_type from = 0; from < g.size(); from++) {
      if (compare_eq()(d[from], Graph::inf_cost))
        continue;
      for (const auto &e : g[from]) {
        node_type to = e.to;
        cost_type new_dist = add()(d[from], e.weight);
        if (not compare_lt()(new_dist, d[to]))
          continue;
        d[to] = new_dist;
        if (c == max_update_count)
          return false;
      }
    }
  }
  return true;
}

} // namespace procon
