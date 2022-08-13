#include "echo_async_worker.h"
#include <iostream>

EchoWorker::EchoWorker(Napi::Function& callback, std::string& echo)
    : Napi::AsyncWorker(callback), echo(echo) {}

void EchoWorker::Execute() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
};

void EchoWorker::OnOK() {
  Napi::HandleScope scope(Env());
  Callback().Call({Napi::String::New(Env(), echo)});
};