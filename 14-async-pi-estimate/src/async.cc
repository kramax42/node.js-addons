#include "async.h"  // NOLINT(build/include)

AsyncPiWorker::AsyncPiWorker(Napi::Function& callback, int points)
    : Napi::AsyncWorker(callback), points(points), estimate(0) {}

void AsyncPiWorker::Execute() {
  estimate = Estimate(points);
}

void AsyncPiWorker::OnOK() {
  Callback().Call({Env().Undefined(), Napi::Number::New(Env(), estimate)});
}

// Asynchronous access to the `Estimate()` function
Napi::Value CalculateAsync(const Napi::CallbackInfo& info) {
  int points = info[0].As<Napi::Number>().Uint32Value();
  Napi::Function callback = info[1].As<Napi::Function>();
  AsyncPiWorker* asyncPiWorker = new AsyncPiWorker(callback, points);
  asyncPiWorker->Queue();
  return info.Env().Undefined();
}
