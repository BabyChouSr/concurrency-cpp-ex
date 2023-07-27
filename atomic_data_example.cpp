#include <thread>
#include <atomic>
#include <vector>
#include <iostream>

using namespace std;

constexpr int NUM_THREADS = 100;
static std::atomic<int> shared_counter = 0;

// Check link for all overloaded operators: https://en.cppreference.com/w/cpp/atomic/atomic
void increment() {
    shared_counter++;
}

int main() {
    vector<thread> threads;
    for (int i = 0; i < NUM_THREADS; i++) {
        threads.push_back(thread(increment));
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }

    cout << shared_counter << endl;

    return 0;
}