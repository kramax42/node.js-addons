#ifndef SIMPLE_ASYNC_WORKER_H
#define SIMPLE_ASYNC_WORKER_H

#include <napi.h>
// using namespace Napi;

class SimpleAsyncWorker : public Napi::AsyncWorker {
 public:
  SimpleAsyncWorker(Napi::Function& callback, int run_time);
  virtual ~SimpleAsyncWorker(){};

  void Execute();
  void OnOK();

 private:
  int run_time;
};

#endif