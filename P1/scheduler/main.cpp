#include "scheduler.cpp"

int main() {
  scheduler sched = scheduler(10000000, 3);

  /*
   * fifo
   * shortest_remaining_time_first
   * by_priority
   * round_robin
   * weighted_round_robin
   */

   cout << endl << "FIRST IN FIRST OUT:" << endl;
   sched.first_in_first_out();
  //
  // cout << endl << "SHORTEST REMAINING FIRST:" << endl;
  // sched.shortest_remaining_time_first();
  //
  // cout << endl << "BY PRIORITY:" << endl;
  // sched.by_priority();
  //
  // cout << endl << "ROUND ROBIN:" << endl;
  // sched.round_robin();
  //
  // cout << endl << "WEIGHTED ROUND ROBIN:" << endl;
  // sched.weighted_round_robin();

   cout << endl << "PEFECTLY FAIR:" << endl;
   sched.pefectly_fair();
  return 0;
}
