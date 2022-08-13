#ifndef INCREMENT_ASYNC_WORKER_H
#define INCREMENT_ASYNC_WORKER_H

#include <napi.h>
#include <chrono>
#include <thread>

class IncrementWorker : public Napi::AsyncWorker {
 public:
  IncrementWorker(Napi::Function& callback, std::string& echo);
  virtual ~IncrementWorker(){};

  void Execute();
  void OnOK();

 private:
  std::string echo;
};

#endif