#ifndef ECHO_ASYNC_WORKER_H
#define ECHO_ASYNC_WORKER_H

#include <napi.h>
#include <chrono>
#include <thread>

class EchoWorker : public Napi::AsyncWorker {
 public:
  EchoWorker(Napi::Function& callback, std::string& echo);
  virtual ~EchoWorker(){};

  void Execute();
  void OnOK();

 private:
  std::string echo;
};

#endif