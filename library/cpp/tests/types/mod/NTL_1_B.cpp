// @depends_on library/cpp/src/types/mod.cpp

int main(void) {
  using Mod = Modulo<1000000007>;
  int m, n;
  std::cin >> m >> n;
  std::cout << static_cast<int>(Mod(m) ^ n) << std::endl;
}
