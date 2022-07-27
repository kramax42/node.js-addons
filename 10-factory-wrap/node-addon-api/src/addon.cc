#include <napi.h>
#include "my_object.h"

Napi::Object CreateObject(const Napi::CallbackInfo& info) {
  if (info.Length() <= 0 || !info[0].IsNumber()) {
    Napi::TypeError::New(info.Env(), "Number expected")
        .ThrowAsJavaScriptException();
    Napi::Object obj = Napi::Object::New(info.Env());
    return obj;
  }
  return MyObject::NewInstance(info.Env(), info[0]);
}

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  Napi::Object new_exports =
      Napi::Function::New(env, CreateObject, "CreateObject");
  return MyObject::Init(env, new_exports);
}

NODE_API_MODULE(addon, InitAll)
