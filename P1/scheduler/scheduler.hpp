#ifndef SCHEDULER_HPP
#define SCHEDULER_HPP

#include <random>

using namespace std;

typedef struct {
  int priority;
  int duration;
  int starttime;
  int endtime;
  int progress;
} job;

class scheduler {

  int end_time;

  int priorities;

  public:
    scheduler();
    scheduler(int end_time, int priorities);
    ~scheduler();

    void first_in_first_out();
    void shortest_remaining_time_first();
    void by_priority();
    void round_robin();
    void weighted_round_robin();
    void pefectly_fair();


  private:
    bool first = true;

    job generate_job();
    bool comp(job a, job b);
};

#endif
