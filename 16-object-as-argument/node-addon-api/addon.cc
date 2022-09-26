#include <napi.h>

Napi::Value SumAllProps(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();

  if (info.Length() != 1) {
    Napi::TypeError::New(env, "Wrong number of arguments")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!info[0].IsObject()) {
    Napi::TypeError::New(env, "Wrong argument! Should be an object.")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  Napi::Object arg = info[0].As<Napi::Object>().ToObject();

  if (!arg.Has("a") || !arg.Has("b")) {
    Napi::TypeError::New(
        env,
        "Wrong object structure! Object should contain 'a' and 'b' properties.")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  if (!arg.Get("a").IsNumber() || !arg.Get("b").IsNumber()) {
    Napi::TypeError::New(
        env, "Wrong object properties! 'a' and 'b' should be number.")
        .ThrowAsJavaScriptException();
    return env.Null();
  }

  double propA = arg.Get("a").As<Napi::Number>().DoubleValue();
  double propB = arg.Get("b").As<Napi::Number>().DoubleValue();

  Napi::Number sum = Napi::Number::New(env, propA + propB);

  return sum;
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  exports.Set(Napi::String::New(env, "sumAllProps"),
              Napi::Function::New(env, SumAllProps));
  return exports;
}

NODE_API_MODULE(addon, Init)
