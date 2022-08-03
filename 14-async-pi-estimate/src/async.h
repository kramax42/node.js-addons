#ifndef ASYNC_CALCULATIONS_H
#define ASYNC_CALCULATIONS_H

#include <napi.h>
#include "pi_estimate.h"  // NOLINT(build/include)

class AsyncPiWorker : public Napi::AsyncWorker {
 public:
  AsyncPiWorker(Napi::Function& callback, int points);
  ~AsyncPiWorker() {}

  // Executed inside the worker-thread.
  // It is not safe to access JS engine data structure
  // here, so everything we need for input and output
  // should go on `this`.
  void Execute();

  // Executed when the async work is complete
  // this function will be run inside the main event loop
  // so it is safe to use JS engine data again
  void OnOK();

 private:
  int points;
  double estimate;
};

Napi::Value CalculateAsync(const Napi::CallbackInfo& info);

#endif
