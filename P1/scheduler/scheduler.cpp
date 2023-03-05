#include "scheduler.hpp"
#include <numeric>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>
#include <queue>
#include <random>
#include <array>

using namespace std;

scheduler::~scheduler() {};

scheduler::scheduler() {
  end_time = 10;

  priorities = 1;

  srand(time(NULL));
}

scheduler::scheduler(int end_time, int priorities) {
  this->end_time = end_time;
  this->priorities = priorities;
  srand(time(NULL));
}

void scheduler::pefectly_fair() {
  int time = 0;
  int jobs_left = 0;

  queue<job> queue;

  vector<int> latencies[this->priorities];

  for(; time < this->end_time; time++) {
    if(time % 5 == 0) { 
      job new_job = this->generate_job();
      new_job.starttime = time;
      queue.push(new_job);
      jobs_left++;
    }
    if(queue.empty()) continue; // There are no jobs to do

    job *curr = &queue.front();
    if(curr->progress++ == curr->duration) {
      int total_time = time - curr->starttime;

      latencies[curr->priority - 1].push_back(total_time);

      jobs_left--;
    } else {
      queue.push(*curr);
    }
    queue.pop();
  }

  for(int i = 0; i < this->priorities; i++) {
    sort(latencies[i].begin(),latencies[i].end());
  }

  cout << "JOBS LEFT: " << jobs_left << endl;

  for(int i = 1; i <= this->priorities; i++) {
    cout <<  endl << "PRIORITY: " << i << endl;
    if(latencies[i - 1].size()) {
      int count = latencies[i - 1].size();

      cout << "NUM JOBS: " << count << endl;

      cout << "AVERAGE WAIT: " << (double) reduce(latencies[i - 1].begin(), latencies[i - 1].end()) / count << endl;
      cout << "MAX WAIT: " << latencies[i - 1].back() << endl;
      cout << "MIN WAIT: " << latencies[i - 1].front() << endl;

      cout << "25TH: " << latencies[i - 1][count / 4] << " MEDIAN: " << latencies[i - 1][count / 2] << " 75TH: " << latencies[i - 1][3 * count / 4] << endl;
    }
    else cout << "NO JOBS DONE" << endl;
  }
}

void scheduler::first_in_first_out() {
  int time = 0;
  int jobs_left = 0;

  queue<job> queue;

  vector<int> latencies[this->priorities];

  for(; time < this->end_time; time++) {
    if(time % 5 == 0) { 
      job new_job = this->generate_job();
      new_job.starttime = time;
      queue.push(new_job);
      jobs_left++;
    }
    if(queue.empty()) continue; // There are no jobs to do

    job *curr = &queue.front();
    if(curr->progress++ == curr->duration) {
      int total_time = time - curr->starttime;

      latencies[curr->priority - 1].push_back(total_time);

      queue.pop(); // Job is done

      jobs_left--;
    }
  }

  for(int i = 0; i < this->priorities; i++) {
    sort(latencies[i].begin(),latencies[i].end());
  }

  cout << "JOBS LEFT: " << jobs_left << endl;

  for(int i = 1; i <= this->priorities; i++) {
    cout <<  endl << "PRIORITY: " << i << endl;
    if(latencies[i - 1].size()) {
      int count = latencies[i - 1].size();

      cout << "NUM JOBS: " << count << endl;

      cout << "AVERAGE WAIT: " << (double) reduce(latencies[i - 1].begin(), latencies[i - 1].end()) / count << endl;
      cout << "MAX WAIT: " << latencies[i - 1].back() << endl;
      cout << "MIN WAIT: " << latencies[i - 1].front() << endl;

      cout << "25TH: " << latencies[i - 1][count / 4] << " MEDIAN: " << latencies[i - 1][count / 2] << " 75TH: " << latencies[i - 1][3 * count / 4] << endl;
    }
    else cout << "NO JOBS DONE" << endl;
  }
}

void scheduler::by_priority() {
  int time = 0;
  int jobs_left = 0;
  
  auto compare = [](job a, job b) { return (b.priority) > (a.priority); };

  priority_queue<job, vector<job>, decltype(compare)> queue;

  vector<int> latencies[this->priorities];

  for(; time < this->end_time; time++) {
    if(time % 5 == 0) {
      job new_job = this->generate_job();
      new_job.starttime = time;
      queue.push(new_job);
      jobs_left++;
    }
    if(queue.empty()) continue; // There are no jobs to do

    job curr = queue.top();
    queue.pop();

    if(curr.progress++ == curr.duration) {
      int total_time = time - curr.starttime;

      latencies[curr.priority - 1].push_back(total_time);

      jobs_left--;
    } else {
      queue.push(curr);
    }
  }

  for(int i = 0; i < this->priorities; i++) {
    sort(latencies[i].begin(),latencies[i].end());
  }

  cout << "JOBS LEFT: " << jobs_left << endl;

  for(int i = 1; i <= this->priorities; i++) {
    cout <<  endl << "PRIORITY: " << i << endl;
    if(latencies[i - 1].size()) {
      int count = latencies[i - 1].size();

      cout << "NUM JOBS: " << count << endl;

      cout << "AVERAGE WAIT: " << (double) reduce(latencies[i - 1].begin(), latencies[i - 1].end()) / count << endl;
      cout << "MAX WAIT: " << latencies[i - 1].back() << endl;
      cout << "MIN WAIT: " << latencies[i - 1].front() << endl;

      cout << "25TH: " << latencies[i - 1][count / 4] << " MEDIAN: " << latencies[i - 1][count / 2] << " 75TH: " << latencies[i - 1][3 * count / 4] << endl;
    }
    else cout << "NO JOBS DONE" << endl;
  }
}

void scheduler::shortest_remaining_time_first() {
  int time = 0;
  int jobs_left = 0;

  auto compare = [](job a, job b) { return (b.duration - b.progress) < (a.duration - a.progress); };

  priority_queue<job, vector<job>, decltype(compare)> queue;

  vector<int> latencies[this->priorities];

  for(; time < this->end_time; time++) {
    if(time % 5 == 0) { 
      job new_job = this->generate_job();
      new_job.starttime = time;
      queue.push(new_job);
      jobs_left++;
    }
    if(queue.empty()) continue; // There are no jobs to do

    job curr = queue.top();
    queue.pop();

    if(curr.progress++ == curr.duration) {
      int total_time = time - curr.starttime;

      latencies[curr.priority - 1].push_back(total_time);

      jobs_left--;
    } else {
      queue.push(curr);
    }
  }

  for(int i = 0; i < this->priorities; i++) {
    sort(latencies[i].begin(),latencies[i].end());
  }

  cout << "JOBS LEFT: " << jobs_left << endl;

  for(int i = 1; i <= this->priorities; i++) {
    cout <<  endl << "PRIORITY: " << i << endl;
    if(latencies[i - 1].size()) {
      int count = latencies[i - 1].size();

      cout << "NUM JOBS: " << count << endl;

      cout << "AVERAGE WAIT: " << (double) reduce(latencies[i - 1].begin(), latencies[i - 1].end()) / count << endl;
      cout << "MAX WAIT: " << latencies[i - 1].back() << endl;
      cout << "MIN WAIT: " << latencies[i - 1].front() << endl;

      cout << "25TH: " << latencies[i - 1][count / 4] << " MEDIAN: " << latencies[i - 1][count / 2] << " 75TH: " << latencies[i - 1][3 * count / 4] << endl;
    }
    else cout << "NO JOBS DONE" << endl;
  }
}

void scheduler::weighted_round_robin() {
  int time = 0;
  int jobs_left = 0;

  queue<job> queues[this->priorities];

  vector<int> latencies[this->priorities];
  
  int last_gen = 0;

  while(time < this->end_time) {
    int prev_time = time;
    for(int i = 1; i <= this->priorities; i++) {
      for(int j = 0; j < i; j++) {
        time++;

        if(time - 5 == last_gen) {
          job new_job = this->generate_job();
          new_job.starttime = time;
          queues[new_job.priority - 1].push(new_job);
          jobs_left++;

          last_gen = time;
        }



        if(queues[i - 1].empty()) {
          time--;
          continue;
        }


        job *curr = &queues[i - 1].front();

        if(curr->progress++ == curr->duration) {
          int total_time = time - curr->starttime;

          latencies[i - 1].push_back(total_time);

          queues[i - 1].pop();
          jobs_left--;
        }
      }
    }

    if(prev_time == time) time++;
  }

  cout << "JOBS LEFT: " << jobs_left << endl;

  for(int i = 0; i < this->priorities; i++) {
    sort(latencies[i].begin(),latencies[i].end());
  }

  for(int i = 1; i <= this->priorities; i++) {
    cout <<  endl << "PRIORITY: " << i << endl;
    if(latencies[i - 1].size()) {
      int count = latencies[i - 1].size();

      cout << "NUM JOBS: " << count << endl;

      cout << "AVERAGE WAIT: " << (double) reduce(latencies[i - 1].begin(), latencies[i - 1].end()) / count << endl;
      cout << "MAX WAIT: " << latencies[i - 1].back() << endl;
      cout << "MIN WAIT: " << latencies[i - 1].front() << endl;

      cout << "25TH: " << latencies[i - 1][count / 4] << " MEDIAN: " << latencies[i - 1][count / 2] << " 75TH: " << latencies[i - 1][3 * count / 4] << endl;
    }
    else cout << "NO JOBS DONE" << endl;
  }
}

void scheduler::round_robin() {
  int time = 0;
  int jobs_left = 0;

  queue<job> queues[this->priorities];

  vector<int> latencies[this->priorities];

  int last_gen = 0;

  while(time < this->end_time) {
    int prev_time = time;
    for(int i = 1; i <= this->priorities; i++) {
      time++;

      if(time - 5 == last_gen) {
        job new_job = this->generate_job();
        new_job.starttime = time;
        queues[new_job.priority - 1].push(new_job);

        jobs_left++;

        last_gen = time;
      }


      if(queues[i - 1].empty()) {
        time--;
        continue;
      }

      job *curr = &queues[i - 1].front();

      if(curr->progress++ == curr->duration) {
        int total_time = time - curr->starttime;

        latencies[curr->priority - 1].push_back(total_time);

        queues[i - 1].pop();

        jobs_left--;
      }
    }

    if(time == prev_time) time++;
  }

  for(int i = 0; i < this->priorities; i++) {
    sort(latencies[i].begin(),latencies[i].end());
  }

  cout << "JOBS LEFT: " << jobs_left << endl;

  for(int i = 1; i <= this->priorities; i++) {
    cout <<  endl << "PRIORITY: " << i << endl;
    if(latencies[i - 1].size()) {
      int count = latencies[i - 1].size();

      cout << "NUM JOBS: " << count << endl;

      cout << "AVERAGE WAIT: " << (double) reduce(latencies[i - 1].begin(), latencies[i - 1].end()) / count << endl;
      cout << "MAX WAIT: " << latencies[i - 1].back() << endl;
      cout << "MIN WAIT: " << latencies[i - 1].front() << endl;

      cout << "25TH: " << latencies[i - 1][count / 4] << " MEDIAN: " << latencies[i - 1][count / 2] << " 75TH: " << latencies[i - 1][3 * count / 4] << endl;
    }
    else cout << "NO JOBS DONE" << endl;
  }
}

// Generate a new random job with random priority and duration
job scheduler::generate_job() {
  job job;

  job.priority = rand() % (this->priorities) + 1;
  job.duration = rand() % (6) + 1;
  job.starttime = 0;

  job.progress = 0;

  return job;
}
