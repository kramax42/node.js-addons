#include "simple_async_worker.h"
#include <chrono>
#include <thread>

SimpleAsyncWorker::SimpleAsyncWorker(Napi::Function& callback, int run_time)
    : AsyncWorker(callback), run_time(run_time){};

void SimpleAsyncWorker::Execute() {
  std::this_thread::sleep_for(std::chrono::seconds(run_time));
  if (run_time == 4) SetError("Oops! Failed after 'working' 4 seconds.");
};

void SimpleAsyncWorker::OnOK() {
  std::string msg = "SimpleAsyncWorker returning after 'working' " +
                    std::to_string(run_time) + " seconds.";
  Callback().Call({Env().Null(), Napi::String::New(Env(), msg)});
};