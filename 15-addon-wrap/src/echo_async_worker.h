#ifndef ECHO_ASYNC_WORKER_H
#define ECHO_ASYNC_WORKER_H

#include <napi.h>
#include <chrono>
#include <thread>

class EchoWorker : public Napi::AsyncWorker {
 public:
  EchoWorker(std::string& echo, Napi::Function& callback);
  virtual ~EchoWorker(){};

  void Execute();
  void OnOK();

 private:
  std::string echo;
};

#endif