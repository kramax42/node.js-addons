#ifndef SIMPLE_ASYNC_WORKER_H
#define SIMPLE_ASYNC_WORKER_H

#include <napi.h>
// using namespace Napi;

class SimpleAsyncWorker : public Napi::AsyncWorker {
 public:
  SimpleAsyncWorker(int run_time, Napi::Function& callback);
  virtual ~SimpleAsyncWorker(){};

  void Execute();
  void OnOK();

 private:
  int run_time;
};

#endif