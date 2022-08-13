#ifndef INCREMENT_ASYNC_WORKER_H
#define INCREMENT_ASYNC_WORKER_H

#include <napi.h>
#include <chrono>
#include <thread>

class IncrementWorker : public Napi::AsyncWorker {
 public:
  IncrementWorker(uint32_t num, Napi::Function& callback);
  virtual ~IncrementWorker(){};

  void Execute();
  void OnOK();

 private:
  uint32_t num;
};

#endif