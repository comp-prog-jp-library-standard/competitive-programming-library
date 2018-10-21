// @depends_on library/cpp/src/array/segment_tree.cpp

using ll = long long;

int main(void) {
  int n;
  scanf("%d", &n);
  std::vector<int> x(n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &x[i]);
  auto seg = procon::make_range_max_query<ll>(n + 1);
  ll ma = 0;
  for (int i = 0; i < n; ++i) {
    ll res = std::max(seg.query(1, x[i]), 0LL);
    ll cur = res + x[i];
    ma = std::max(ma, cur);
    seg.update(x[i], cur);
  }
  ll whole = (ll)n * (ll)(n + 1) / 2;
  printf("%lld\n", whole - ma);
}
