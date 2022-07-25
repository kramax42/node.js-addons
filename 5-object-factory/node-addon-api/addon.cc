#include <napi.h>

Napi::Object CreateObject(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  Napi::Object obj = Napi::Object::New(env);

  if (!info[0].IsString()) {
    Napi::TypeError::New(env, "Wrong argument! Should be a string").ThrowAsJavaScriptException();
    return obj;
  }

  obj.Set(Napi::String::New(env, "msg"), info[0].ToString());

  return obj;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  return Napi::Function::New(env, CreateObject, "createObject");
}

NODE_API_MODULE(addon, Init)
