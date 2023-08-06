#include <iostream>
#include <future>
#include <chrono>


int big_work() {
    int sum = 0;
    for (int i = 0; i < 200; i++) {
        sum += i;
    }
    return sum;
}

int main() {
    std::future<int> some_work = std::async(&big_work);

    int sum = 0;
    for (int i = 0; i < 100; i++) {
        sum += i;
    }

    std::cout << "The sum calculated in the background: " << sum << std::endl;
    std::cout << "The work's result is: " << some_work.get() << std::endl;
    return 0;
}