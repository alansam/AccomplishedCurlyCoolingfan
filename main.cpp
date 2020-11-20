
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <array>
#include <algorithm>
#include <numeric>
#include <cstdint>
#include <climits>

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
    std::cout << "aritmetic formula n * (n + 1) / 2"s << '\n';
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
  // TODO: Fibonacci Rule is xᵤ = xᵤ₋₁ + xᵤ₋₂
  std::cout << "\nFibonacci series, xᵤ = xᵤ₋₁ + xᵤ₋₂ [first 93 terms]\n"s;
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

    std::cout << "\nFibonacci using constant table"s << '\n';
    uint64_t constexpr fibonacci[] {
    /*  0 */                          1ULL,                          1ULL,                          2ULL,
    /*  3 */                          3ULL,                          5ULL,                          8ULL,
    /*  6 */                         13ULL,                         21ULL,                         34ULL,
    /*  9 */                         55ULL,                         89ULL,                        144ULL,
    /* 12 */                        233ULL,                        377ULL,                        610ULL,
    /* 15 */                        987ULL,                      1'597ULL,                      2'584ULL,
    /* 18 */                      4'181ULL,                      6'765ULL,                     10'946ULL,
    /* 21 */                     17'711ULL,                     28'657ULL,                     46'368ULL,
    /* 24 */                     75'025ULL,                    121'393ULL,                    196'418ULL,
    /* 27 */                    317'811ULL,                    514'229ULL,                    832'040ULL,
    /* 30 */                  1'346'269ULL,                  2'178'309ULL,                  3'524'578ULL,
    /* 33 */                  5'702'887ULL,                  9'227'465ULL,                 14'930'352ULL,
    /* 36 */                 24'157'817ULL,                 39'088'169ULL,                 63'245'986ULL,
    /* 39 */                102'334'155ULL,                165'580'141ULL,                267'914'296ULL,
    /* 42 */                433'494'437ULL,                701'408'733ULL,              1'134'903'170ULL,
    /* 45 */              1'836'311'903ULL,              2'971'215'073ULL,              4'807'526'976ULL,
    /* 48 */              7'778'742'049ULL,             12'586'269'025ULL,             20'365'011'074ULL,
    /* 51 */             32'951'280'099ULL,             53'316'291'173ULL,             86'267'571'272ULL,
    /* 54 */            139'583'862'445ULL,            225'851'433'717ULL,            365'435'296'162ULL,
    /* 57 */            591'286'729'879ULL,            956'722'026'041ULL,          1'548'008'755'920ULL,
    /* 60 */          2'504'730'781'961ULL,          4'052'739'537'881ULL,          6'557'470'319'842ULL,
    /* 63 */         10'610'209'857'723ULL,         17'167'680'177'565ULL,         27'777'890'035'288ULL,
    /* 66 */         44'945'570'212'853ULL,         72'723'460'248'141ULL,        117'669'030'460'994ULL,
    /* 69 */        190'392'490'709'135ULL,        308'061'521'170'129ULL,        498'454'011'879'264ULL,
    /* 72 */        806'515'533'049'393ULL,      1'304'969'544'928'657ULL,      2'111'485'077'978'050ULL,
    /* 75 */      3'416'454'622'906'707ULL,      5'527'939'700'884'757ULL,      8'944'394'323'791'464ULL,
    /* 78 */     14'472'334'024'676'221ULL,     23'416'728'348'467'685ULL,     37'889'062'373'143'906ULL,
    /* 81 */     61'305'790'721'611'591ULL,     99'194'853'094'755'497ULL,    160'500'643'816'367'088ULL,
    /* 84 */    259'695'496'911'122'585ULL,    420'196'140'727'489'673ULL,    679'891'637'638'612'258ULL,
    /* 87 */  1'100'087'778'366'101'931ULL,  1'779'979'416'004'714'189ULL,  2'880'067'194'370'816'120ULL,
    /* 90 */  4'660'046'610'375'530'309ULL,  7'540'113'804'746'346'429ULL, 12'200'160'415'121'876'738ULL,
    };
    size_t constexpr __attribute__((__unused__)) fibonacci_l = sizeof(fibonacci) / sizeof(*fibonacci);
    col = 0;
    std::for_each(std::begin(fibonacci), std::end(fibonacci), [&col](auto f_) {
      std::cout << std::setw(20) << f_ << (++col % col_max == 0 ? '\n' : ' ');
    });
    std::cout << '\n'
              << std::setw(40 + 2) << "Max 64-bit unsigned integer ULLONG_MAX: "s
              << std::setw(20) << ULLONG_MAX << '\n';

    std::cout << std::endl;
  }

  {
    // 1/2 * (n)^2 + 1/2 n
    // n * (n + 1) / 2"s << '\n'
    std::cout << "aritmetic formula: 1/2 * (n)^2 + 1/2 n"s << '\n';
    double ev = 100;
    double sum;
    sum = 0.5 * (ev * ev) + 0.5 * ev;
    std::cout << sum << std::endl;
  }

  return 0;
}
