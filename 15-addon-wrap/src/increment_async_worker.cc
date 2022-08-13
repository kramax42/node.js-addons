#include "increment_async_worker.h"
#include <iostream>

IncrementWorker::IncrementWorker(uint32_t num, Napi::Function& callback)
    : Napi::AsyncWorker(callback), num(num) {}

void IncrementWorker::Execute() {
  std::this_thread::sleep_for(std::chrono::seconds(2));
};

void IncrementWorker::OnOK() {
  Napi::HandleScope scope(Env());
  Callback().Call({Napi::Number::New(Env(), num + 1)});
};