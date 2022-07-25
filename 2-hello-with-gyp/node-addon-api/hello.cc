#include <napi.h>

Napi::String SayHello(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  return Napi::String::New(env, "Hello world!");
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "sayHello"),
              Napi::Function::New(env, SayHello));
  return exports;
}

// First argument - GYP target name.
// Second argument - function-initializer.
NODE_API_MODULE(say_hello, Init)
