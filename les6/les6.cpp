#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>
#include <future>
#include <algorithm>
#include "pcout.h"

using namespace std::chrono_literals;
Pcout pcout;
std::mutex mtx;

void print_int()
{
    for (auto i{ 0 }; i < 50; ++i)
    {
        pcout << i << "\n";
        std::this_thread::sleep_for(200ms);
    }
}

void print_char()
{
    for (auto i{ 65 }; i <= 90; ++i)
    {
        pcout << static_cast<char>(i) << "\n";
        std::this_thread::sleep_for(200ms);
    }
}

__int64 find_prime(int count)
{
    __int64 val{ 0 };
    int prev{ 0 };
    int index{ 1 };
    while(true)
    {
        bool is_prime{ true };
        if (val <= 1 || (val != 2 && !(val % 2)))
        {
            is_prime = false;
        }
        else
        {
            int max_dev = static_cast<int>(sqrt(val));
            for (__int64 dev{ 3 }; dev <= max_dev; dev += 2)
            {
                if (!(val % dev))
                {
                    is_prime = false;
                    break;
                }
            }
        }

        if (is_prime)
        {
            int percent = static_cast<int>(index * 100.f / count);
            if (percent != prev)
            {
                prev = percent;
                std::unique_lock<std::mutex> ul{ mtx };
#ifdef  __linux__ 
                std::system("clear");
#elif defined(TARGET_OS_MAC)
                std::system("clear");
#elif defined (_WIN32) || defined (_WIN64)
                std::system("cls");
#endif    
                std::cout << "Progress: " << percent << "%" << std::endl;
            }

            if (index == count)
            {
                return val;
            }
            index++;
        }
        val++;
    }
}

int main()
{
    // ====== TASK #1 ====== 
    std::thread thr1{ print_int };
    std::thread thr2{ print_char };

    if(thr1.joinable())
    {
        thr1.join();
    }
    if(thr2.joinable())
    {
        thr2.join();
    }

    // ====== TASK #2 ====== 
    std::cout << "Input index of prime: ";
    int index;
    std::cin >> index;
    __int64 value{ 0 };
    std::thread thr3{ [&value, index]() { value = find_prime(index); } };

    if (thr3.joinable())
    {
        thr3.join();
    }
    std::cout << value << std::endl;


    std::this_thread::sleep_for(3s);

    std::future<__int64> result = std::async(find_prime, index);
    try
    {
        std::cout << result.get() << std::endl;
    }
    catch (std::exception& ex)
    {
        std::cerr << ex.what() << std::endl;
    }

    // ====== TASK #3 ====== 
    std::vector<int> goods(10);
    srand(static_cast<unsigned>(time(nullptr)));
    std::generate_n(goods.begin(), 10, []() { return rand() % 1000;  });
    
    std::thread thr4([&goods]()
        {
            while(true)
            {
                {
                    std::unique_lock<std::mutex> lock{ mtx };
                    if (goods.empty())
                    {
                        return;
                    }
                    goods.emplace_back(rand() % 1000);
                }
                std::this_thread::sleep_for(1000ms);
            }
            
        });
    std::thread thr5([&goods]()
        {
            while(true)
            {
                {
                    std::unique_lock<std::mutex> lock{ mtx };
                    if (!goods.empty())
                    {
                        auto it = std::max_element(goods.begin(), goods.end());
                        std::cout << *it << std::endl;
                        std::swap(*it, goods.back());
                        goods.pop_back();
                    }
                    else
                    {
                        return;
                    }
                }
                std::this_thread::sleep_for(500ms);
            }
        });
    
    if (thr4.joinable())
    {
        thr4.join();
    }
    
    if (thr5.joinable())
    {
        thr5.join();
    }

    return 0;
}