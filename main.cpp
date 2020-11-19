
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <array>
#include <algorithm>
#include <numeric>
#include <cstdint>

using namespace std::literals::string_literals;

template<typename T>
T addup(T sum) {
  if (sum == 1) return 1;
  else return sum + addup(sum - 1);
}

int main(int argc, char const * argv[]) {
  {
    std::cout << "iterate with std::accumulate"s << '\n';
    std::list<int> ton(100);
    std::iota(ton.begin(), ton.end(), 1);
    auto sum = std::accumulate(ton.begin(), ton.end(), 0);
    std::cout << sum << std::endl;
  }

  {
    std::cout << "iterate with a range-based for"s << '\n';
    std::list<int> ton(100);
    std::iota(ton.begin(), ton.end(), 1);
    int sum = 0;
    for (auto n_ : ton) { sum += n_; }
    std::cout << sum << std::endl;
  }

  {
    std::cout << "iterate with a C style for"s << '\n';
    int sum = 0;
    for (int i = 0; i < 100; ++i, sum += i);
    std::cout << sum << std::endl;
  }

  {
    std::cout << "aritmetic formula"s << '\n';
    int ev = 100;
    int sum;
    sum = ev * (ev + 1) / 2;
    std::cout << sum << std::endl;
  }

  {
    std::cout << "iterate with std::for_each"s << '\n';
    std::list<int> ton(100);
    std::iota(ton.begin(), ton.end(), 1);
    int sum = 0;
    std::for_each(ton.begin(), ton.end(), [&sum](auto n_) { sum += n_; });    
    std::cout << sum << std::endl;
  }

  {
    std::cout << "recursive function"s << '\n';
    int sum = addup(100);
    std::cout << sum << std::endl;
  }

  {
    std::cout << '\n';
    std::cout << "Factorials (using std::partial_sum):\n"s;
    //  20! is the largest factorial that will fit in a 64-bit integer.
    size_t constexpr max_factor(20);
    std::vector<uint64_t> vidx(max_factor, 1);
    std::vector<uint64_t> vfact(max_factor);
    std::for_each(vidx.begin(), vidx.end(), [](auto n_) {
      std::cout << std::setw(2) << n_ << ' ';
    });
    std::cout << '\n';
    std::partial_sum(vidx.begin(), vidx.end(), vfact.begin());
    std::for_each(vfact.begin(), vfact.end(), [](auto n_) {
      std::cout << std::setw(2) << n_ << ' ';
    });
    std::cout << '\n';
    std::partial_sum(vfact.begin(), vfact.end(), vfact.begin(),
                     std::multiplies<uint64_t>());
    std::for_each(vfact.begin(), vfact.end(), [](auto n_) {
      std::cout << std::setw(20) << n_ << '\n';
    });

    std::cout << '\n' << "Factorials (using a constant table)"s
              << '\n';

    //  From GMP.Factorial.Select
    uint64_t constexpr factorials[] = {
      /* 0!*/                         0ULL, /* TODO: Added to make picking factorials intuitive */
      /* 1!*/                         1ULL,
      /* 2!*/                         2ULL,
      /* 3!*/                         6ULL,
      /* 4!*/                        24ULL,
      /* 5!*/                       120ULL,
      /* 6!*/                       720ULL,
      /* 7!*/                     5'040ULL,
      /* 8!*/                    40'320ULL,
      /* 9!*/                   362'880ULL,
      /*10!*/                 3'628'800ULL,
      /*11!*/                39'916'800ULL,
      /*12!*/               479'001'600ULL, /* TODO: max factorial for 32-bit integers */
      /*13!*/             6'227'020'800ULL,
      /*14!*/            87'178'291'200ULL,
      /*15!*/         1'307'674'368'000ULL,
      /*16!*/        20'922'789'888'000ULL,
      /*17!*/       355'687'428'096'000ULL,
      /*18!*/     6'402'373'705'728'000ULL,
      /*19!*/   121'645'100'408'832'000ULL,
      /*20!*/ 2'432'902'008'176'640'000ULL, /* TODO: max factorial for 64-bit integers */
      };
    size_t factorials_c = sizeof(factorials) / sizeof(*factorials);
    std::for_each(std::begin(factorials), std::end(factorials),
    [](auto n_) {
      if (n_ != 0) {
        std::cout << std::setw(20) << n_ << '\n';
      }
    });
  }

  {
    std::cout << "Fibonacci using std::adjacent_difference"s << '\n';
    std::array<uint64_t, 93> ary { 1 };

    std::adjacent_difference(ary.begin(), std::prev(ary.end()),
                             std::next(ary.begin()), std::plus<> {});
    size_t col(0);
    size_t const col_max(3);
    std::for_each(ary.begin(), ary.end(), [& col](auto const n_)
    {
      std::cout << std::setw(20) << n_
                << (++col % col_max == 0 ? '\n' : ' ');
    });
  }

  return 0;
}
