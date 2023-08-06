#include <thread>
#include <atomic>
#include <vector>
#include <iostream>

using namespace std;

constexpr int NUM_THREADS = 100;

static int shared_counter = 0;

std::mutex mu; 

void increment() {
    mu.lock();
    shared_counter = shared_counter + 1;
    mu.unlock();
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