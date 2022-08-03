#include "simple_async_worker.h"

Napi::Value RunSimpleAsyncWorker(const Napi::CallbackInfo& info) {
  int run_time = info[0].As<Napi::Number>();
  Napi::Function callback = info[1].As<Napi::Function>();
  SimpleAsyncWorker* asyncWorker = new SimpleAsyncWorker(run_time, callback);
  asyncWorker->Queue();
  std::string msg =
      "SimpleAsyncWorker for " + std::to_string(run_time) + " seconds queued.";
  return Napi::String::New(info.Env(), msg.c_str());
};

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports["runSimpleAsyncWorker"] = Napi::Function::New(
      env, RunSimpleAsyncWorker, std::string("runSimpleAsyncWorker"));
  return exports;
}

NODE_API_MODULE(addon, Init)