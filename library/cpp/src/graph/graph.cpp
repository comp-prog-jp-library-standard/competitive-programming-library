namespace procon {

template <typename Cost, typename Compare = std::less<Cost>,
          typename Add = std::plus<Cost>>
class WeightedGraph {
public:
  class edge_type {
  public:
    using node_type = int;
    using weight_type = Cost;
    const node_type to;
    const weight_type weight;
    edge_type(node_type t, weight_type w) : to(t), weight(w) { ; }
  };
  using base_graph_type = WeightedGraph;
  using node_type = typename edge_type::node_type;
  using weight_type = typename edge_type::weight_type;
  using cost_type = Cost;
  using compare = Compare;
  using add = Add;
  using edges_type = std::vector<edge_type>;
  using iterator = typename edges_type::iterator;
  using const_iterator = typename edges_type::const_iterator;
  template <typename T> using map_value = std::vector<T>;
  static const cost_type inf_cost = std::numeric_limits<cost_type>::max();
  static const cost_type zero_cost = static_cast<cost_type>(0);
  WeightedGraph() : g() { ; }
  WeightedGraph(int size) : g(size) { ; }
  void add_edge(node_type s, node_type t, weight_type w) {
    g[s].emplace_back(t, w);
  }
  const edges_type &operator[](node_type node) const { return g[node]; }
  edges_type &operator[](node_type node) { return g[node]; }
  iterator begin() { return g.begin(); }
  const_iterator begin() const { return g.begin(); }
  iterator end() { return g.end(); }
  const_iterator end() const { return g.end(); }
  int size() const { return g.size(); }

private:
  std::vector<edges_type> g;
};

} // namespace procon
