// @depends_on library/cpp/src/math/sieve_primes.cpp

const int LIMIT = 100000000;

int main(void) {
  int n;
  std::cin >> n;
  std::vector<bool> primes = procon::sieve_primes(LIMIT);
  int count = 0;
  for (int i = 0; i < n; ++i) {
    int element;
    std::cin >> element;
    if (primes[element]) {
      count++;
    }
  }
  std::cout << count << std::endl;
}
