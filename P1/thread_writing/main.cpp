#include <thread>
#include <iostream>
#include <fstream>
#include <chrono>
#include <mutex>

using namespace std;

void locked_write(char in, int total_writes, mutex *mtx) {
  ofstream locked("locked.txt", ios::app);

  for(int i = 0; i < total_writes; i++) {
    mtx->lock();
    locked << in << endl;
    mtx->unlock();
  }

  locked.close();
}

void unlocked_write(char in, int total_writes) {
  ofstream unlocked("unlocked.txt", ios::app);

  for(int i = 0; i < total_writes; i++) {
    unlocked << in << endl;
  }

  unlocked.close();
}

void diff(int num_threads, int num_writes, mutex *mtx, double &output) {
  ofstream locked("locked.txt");
  locked.close();

  ofstream unlocked("unlocked.txt");
  unlocked.close();

  thread unlocked_threads[num_threads];
  thread locked_threads[num_threads];

  auto start_unlocked = chrono::system_clock::now();

  for(int i = 0; i < num_threads; i++) {
    unlocked_threads[i] = thread(unlocked_write, 'A' + i, num_writes);
  }

  for(int i = 0; i < num_threads; i++) {
    unlocked_threads[i].join();
  }

  auto end_unlocked = chrono::system_clock::now();

  chrono::duration<double> elapsed_seconds_unlocked = end_unlocked - start_unlocked;

  cout << endl << "UNLOCKED TIME: " << elapsed_seconds_unlocked.count() << endl;

  auto start_locked = chrono::system_clock::now();

  for(int i = 0; i < num_threads; i++) {
    locked_threads[i] = thread(locked_write, 'A' + i, num_writes, mtx);
  }

  for(int i = 0; i < num_threads; i++) {
    locked_threads[i].join();
  }

  auto end_locked = chrono::system_clock::now();

  chrono::duration<double> elapsed_seconds_locked = end_locked - start_locked;

  cout << "LOCKED TIME: " << elapsed_seconds_locked.count() << endl;

  output = elapsed_seconds_locked.count() - elapsed_seconds_unlocked.count();
}

int main() {
  int num_threads, num_writes, num_trials;

  cout << "NUMBER OF THREADS: ";
  cin >> num_threads;

  cout << "NUMBER OF WRITES: ";
  cin >> num_writes;

  cout << "NUMBER OF TRIALS: ";
  cin >> num_trials;

  mutex mtx;
  
  double result = 0;

  for(int i = 0; i < num_trials; i++) {
    double output;
    diff(num_threads, num_writes, &mtx, output);

    result += output;
  }
    

  cout << endl << "AVERAGE LOSS: " << result / num_trials << endl;
}
