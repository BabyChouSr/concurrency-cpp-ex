#include <thread>
#include <atomic>
#include <vector>
#include <iostream>

using namespace std;

mutex mu;
condition_variable cv;

int main() {
    int result = 0;
    bool notified = false;

    thread reporter([&](){
        unique_lock lock(mu);

        if (!notified) {
            cv.wait(lock);
        }

        cout << "Result: " << result << endl;
    });

    thread worker([&](){
        unique_lock lock(mu);

        result = 420;

        notified = true;

        cv.notify_one();
    });

    reporter.join();
    worker.join();

    cout << "Program complete" << endl;

    return 0;
}