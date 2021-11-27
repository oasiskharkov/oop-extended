#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <iterator>
#include <numeric>
#include <list>
#include <deque>

constexpr size_t size = 100;

template <typename Container, typename ValueType>
void insert_sorted(Container& cont, const ValueType& value)
{
    auto it = std::find_if(cont.begin(), cont.end(), [value](const auto& elem) { return value <= elem; });
    std::cout << "Insert " << value << " into " << std::distance(cont.begin(), it) << " position" << std::endl;
    cont.insert(it, value);
}

int main()
{
    // ====== TASK #1 =======
    srand(static_cast<unsigned>(time(nullptr)));
    std::vector<int> vec(20);
    std::generate(vec.begin(), vec.end(), []() { return rand() % 20; });
    std::sort(std::begin(vec), std::end(vec));
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    insert_sorted(vec, rand() % 30);
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::list<int> lst(20);
    std::generate(lst.begin(), lst.end(), []() { return rand() % 20; });
    lst.sort();
    std::copy(lst.begin(), lst.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    insert_sorted(lst, rand() % 30);
    std::copy(lst.begin(), lst.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    std::deque<int> deq(20);
    std::generate(deq.begin(), deq.end(), []() { return rand() % 20; });
    std::sort(std::begin(deq), std::end(deq));
    std::copy(deq.begin(), deq.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    insert_sorted(deq, rand() % 30);
    std::copy(deq.begin(), deq.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    // ====== TASK #2 =======  
    std::random_device rd;
    std::mt19937 mt(rd());
    std::uniform_real_distribution<float> dist(0, size);

    std::vector<float> vec_float(size);
    std::vector<int> vec_int(size);

    std::generate(vec_float.begin(), vec_float.end(), [&dist, &mt]() { return dist(mt); });
    std::transform(vec_float.begin(), vec_float.end(), vec_int.begin(), [](float value) {return static_cast<int>(value); });

    std::copy(vec_float.begin(), vec_float.end(), std::ostream_iterator<float>(std::cout, " "));
    std::cout << std::endl;

    std::copy(vec_int.begin(), vec_int.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    int index = 0;
    float error1 = std::accumulate(vec_float.begin(), vec_float.end(), 0.f, [index, &vec_int](float x, float value) mutable
        {
            float add = (value - vec_int[index]) * (value - vec_int[index]);
            ++index;
            return x + add;
        }
    );
    std::cout << "Error = " << error1 << std::endl;

    float error2 = 0.f;
    std::for_each(vec_float.begin(), vec_float.end(), [index, &vec_int, &error2] (float value) mutable
        {
            error2 += (value - vec_int[index]) * (value - vec_int[index]);
            ++index;
        }
    );
    std::cout << "Error = " << error2 << std::endl;

    std::vector<float> result(size);
    std::transform(vec_float.begin(), vec_float.end(), vec_int.begin(), result.begin(), [](float a, int b)
        {
            return (a - b) * (a - b);
        }
    );
    float error3 = std::accumulate(result.begin(), result.end(), 0.f);
    std::cout << "Error = " << error3 << std::endl;

    return 0;
}
