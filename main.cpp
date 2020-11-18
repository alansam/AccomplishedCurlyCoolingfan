
#include <iostream>
#include <algorithm>
#include <numeric>
#include <list>

template<typename T>
T addup(T sum) {
  if (sum == 1) return 1;
  else return sum + addup(sum - 1);
}

int main(int argc, char const * argv[]) {
  {
    std::cout << "iterate with std::accumulate" << '\n';
    std::list<int> ton(100);
    std::iota(ton.begin(), ton.end(), 1);
    auto sum = std::accumulate(ton.begin(), ton.end(), 0);
    std::cout << sum << std::endl;
  }

  {
    std::cout << "iterate with a range-based for" << '\n';
    std::list<int> ton(100);
    std::iota(ton.begin(), ton.end(), 1);
    int sum = 0;
    for (auto n_ : ton) { sum += n_; }
    std::cout << sum << std::endl;
  }

  {
    std::cout << "iterate with a C style for" << '\n';
    int sum = 0;
    for (int i = 0; i < 100; ++i, sum += i);
    std::cout << sum << std::endl;
  }

  {
    std::cout << "aritmetic formula" << '\n';
    int ev = 100;
    int sum;
    sum = ev * (ev + 1) / 2;
    std::cout << sum << std::endl;
  }

  {
    std::cout << "iterate with std::for_each" << '\n';
    std::list<int> ton(100);
    std::iota(ton.begin(), ton.end(), 1);
    int sum = 0;
    std::for_each(ton.begin(), ton.end(), [&sum](auto n_) { sum += n_; });    
    std::cout << sum << std::endl;
  }

  {
    std::cout << "recursive function" << '\n';
    int sum = addup(100);
    std::cout << sum << std::endl;
  }

  return 0;
}
