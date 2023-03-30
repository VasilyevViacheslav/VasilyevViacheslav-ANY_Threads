#include <algorithm>
#include <vector>
#include <functional>
#include <thread>
#include <string>
#include <iostream>

using namespace std;

template <typename T,typename Predicate>
bool _any(const vector<T>& data, Predicate predicate = false, size_t threads = 1) {
    bool result = false;

    if (threads == 1) {
        for (const auto& item : data) {
            if (predicate(item)) {
                result = true;
                break;
            }
        }
    }
    else {
        vector<thread> thread_pool;
        size_t chunk_size = data.size() / threads;
        size_t remainder = data.size() % threads;

        auto process_chunk = [&](size_t begin, size_t end) {
            for (size_t i = begin; i < end; i++) {
                if (predicate(data[i])) {
                    result = true;
                    break;
                }
            }
        };

        for (size_t i = 0; i < threads; i++) {
            size_t begin = i * chunk_size;
            size_t end = begin + chunk_size;

            if (i == threads - 1) {
                end += remainder;
            }

            thread_pool.emplace_back(process_chunk, begin, end);
        }

        for (auto& thread : thread_pool) {
            thread.join();
        }
    }

    return result;
}
int main() {
    vector<string> words = { "hello","Abdomen","Abduct","AbeAbel","asdaw","dwadwas","dwadwa" };
    size_t n;
    cout << "Колическтво потоков - ";
    cin >> n;
    if (n < 2 * thread::hardware_concurrency())
    for (size_t threads = 1; (unsigned)threads <= n; ++threads){
       _any(words, [](const auto& word) {return true;},n);
    }
    return 0;
}