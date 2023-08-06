#include <thread>
#include <iostream>
#include <vector>

using namespace std;

static int shared_counter = 0;
constexpr int NUM_THREADS = 100;

void increment() {
    shared_counter = shared_counter + 1;
}

int main() {
    vector<thread> threads;
    for(int i = 0; i < NUM_THREADS; i++) {
        threads.push_back(thread(increment));
    } 

    for (int i = 0; i < NUM_THREADS; i++) {
        threads[i].join();
    }

    cout << shared_counter << endl;
    return 0;
}