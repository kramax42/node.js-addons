#include <napi.h>

Napi::String SayHello(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::String::New(env, "Hello world!");
}

Napi::Function CreateFunction(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Function fn = Napi::Function::New(env, SayHello, "");
  return fn;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  return Napi::Function::New(env, CreateFunction, "createObject");
}

NODE_API_MODULE(addon, Init)
