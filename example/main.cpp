#include "../include/progressbar.hpp"
#include <thread>
#include <chrono>

int main() {
    const size_t total_items = 200;
    ProgressBar bar(total_items, 30);

    for (size_t i = 0; i < total_items; ++i) {
        ++bar;
        // Simulate work
        std::this_thread::sleep_for(std::chrono::milliseconds(20));
    }

    bar.finish();
    return 0;
}