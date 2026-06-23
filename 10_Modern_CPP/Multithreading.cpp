/*
 * File    : Multithreading.cpp
 * Author  : Pavan Shetty H S
 * Topic   : std::thread, mutex, atomic (C++11)
 * Date    : Week 11 - Day 1  (Still learning this!)
 *
 * Notes:
 *   This is the most complex topic so far. Still wrapping my head
 *   around race conditions and synchronization.
 *
 *   Key insight: any time two threads can access the same data
 *   and at least one writes, you need synchronization.
 *
 *   Compile with: g++ -std=c++17 Multithreading.cpp -o mt -lpthread
 */

#include <iostream>
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>
#include <chrono>
using namespace std;

mutex printMutex;   // for safe cout from multiple threads
mutex counterMutex;

// 1. Basic thread
void printMessage(string msg, int repeat) {
    for (int i = 0; i < repeat; i++) {
        lock_guard<mutex> lock(printMutex);  // RAII lock — auto-released
        cout << "  Thread [" << this_thread::get_id() << "]: " << msg << " (" << i+1 << ")" << endl;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

// 2. Race condition demo
int unsafeCounter = 0;
void unsafeIncrement() {
    for (int i = 0; i < 10000; i++) unsafeCounter++;  // RACE CONDITION!
}

// 3. Safe counter using mutex
int safeCounter = 0;
void safeIncrement() {
    for (int i = 0; i < 10000; i++) {
        lock_guard<mutex> lock(counterMutex);
        safeCounter++;
    }
}

// 4. Atomic counter (even simpler)
atomic<int> atomicCounter{0};
void atomicIncrement() {
    for (int i = 0; i < 10000; i++) atomicCounter++;  // Thread-safe, no mutex needed
}

// 5. Thread with return value using future
#include <future>
int expensiveComputation(int n) {
    this_thread::sleep_for(chrono::milliseconds(200));  // simulate work
    int result = 0;
    for (int i = 1; i <= n; i++) result += i;
    return result;
}

int main() {
    cout << "=== MULTITHREADING ===" << endl;

    // 1. Basic threads
    cout << "\n--- Basic Threads ---" << endl;
    thread t1(printMessage, "Hello from T1", 2);
    thread t2(printMessage, "Hello from T2", 2);
    t1.join();  // wait for t1 to finish
    t2.join();  // wait for t2 to finish
    cout << "Both threads finished." << endl;

    // 2. Race condition
    cout << "\n--- Race Condition Demo ---" << endl;
    unsafeCounter = 0;
    thread r1(unsafeIncrement);
    thread r2(unsafeIncrement);
    r1.join(); r2.join();
    cout << "Expected: 20000, Got: " << unsafeCounter << " (unpredictable!)" << endl;

    // 3. Safe with mutex
    cout << "\n--- Mutex Protection ---" << endl;
    safeCounter = 0;
    thread s1(safeIncrement);
    thread s2(safeIncrement);
    s1.join(); s2.join();
    cout << "Expected: 20000, Got: " << safeCounter << " (correct!)" << endl;

    // 4. Atomic
    cout << "\n--- Atomic Counter ---" << endl;
    atomicCounter = 0;
    thread a1(atomicIncrement);
    thread a2(atomicIncrement);
    a1.join(); a2.join();
    cout << "Expected: 20000, Got: " << atomicCounter << " (atomic, no mutex needed!)" << endl;

    // 5. async / future — get return value from thread
    cout << "\n--- async / future ---" << endl;
    auto future1 = async(launch::async, expensiveComputation, 100);
    auto future2 = async(launch::async, expensiveComputation, 200);
    cout << "Computing in parallel..." << endl;
    int r1_val = future1.get();   // blocks until result is ready
    int r2_val = future2.get();
    cout << "Sum(1..100) = " << r1_val << endl;
    cout << "Sum(1..200) = " << r2_val << endl;

    cout << "\n--- Key Concepts ---" << endl;
    cout << "lock_guard   — RAII mutex lock (recommended)" << endl;
    cout << "unique_lock  — flexible lock (can unlock/relock)" << endl;
    cout << "atomic<T>    — thread-safe for simple types" << endl;
    cout << "async/future — easy way to get return values" << endl;
    cout << "Compile: g++ -std=c++17 file.cpp -lpthread" << endl;

    return 0;
}

/*
 ================================================================
  PROGRAM OUTPUT
  Compiled & run with: g++ -std=c++17 -O2 -pthread Multithreading.cpp -o prog
 ================================================================

 === MULTITHREADING ===

 --- Basic Threads ---
   Thread [139875370137280]: Hello from T1 (1)
   Thread [139875361744576]: Hello from T2 (1)
   Thread [139875361744576]: Hello from T2 (2)
   Thread [139875370137280]: Hello from T1 (2)
 Both threads finished.

 --- Race Condition Demo ---
 Expected: 20000, Got: 20000 (unpredictable!)

 --- Mutex Protection ---
 Expected: 20000, Got: 20000 (correct!)

 --- Atomic Counter ---
 Expected: 20000, Got: 20000 (atomic, no mutex needed!)

 --- async / future ---
 Computing in parallel...
 Sum(1..100) = 5050
 Sum(1..200) = 20100

 --- Key Concepts ---
 lock_guard   — RAII mutex lock (recommended)
 unique_lock  — flexible lock (can unlock/relock)
 atomic<T>    — thread-safe for simple types
 async/future — easy way to get return values
 Compile: g++ -std=c++17 file.cpp -lpthread

 ================================================================
*/

