// @depends_on library/cpp/src/math/ext_gcd.cpp

int main(void) {
  int a, b;
  std::cin >> a >> b;
  int x, y;
  int g = procon::ext_gcd(a, b, x, y);
  std::cout << g << std::endl;
}
