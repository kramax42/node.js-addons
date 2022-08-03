#include "sync.h"  // NOLINT(build/include)

// Simple synchronous access to the `Estimate()` function.
Napi::Value CalculateSync(const Napi::CallbackInfo& info) {
  // Expect a number as the first argument.
  int points = info[0].As<Napi::Number>().Uint32Value();
  double est = Estimate(points);

  return Napi::Number::New(info.Env(), est);
}
