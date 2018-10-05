/*
 * Sieve of Eratosthenes.
 * Returns a bool array of length (n + 1)
 * representing whether integers <= n are prime or not.
 * if i is a prime, p[i] == true holds.
 * if i is not a prime, p[i] == false holds.
 * header requirement: vector
 */
namespace procon {
std::vector<bool> sieve_primes(int n) {
  std::vector<bool> prime(n + 1);
  for (int i = 2; i <= n; ++i) {
    prime[i] = true;
  }
  for (int i = 2; i * i <= n; ++i) {
    if (not prime[i]) {
      continue;
    }
    for (int j = i * i; j <= n; j += i) {
      prime[j] = false;
    }
  }
  return prime;
}
} // namespace procon
