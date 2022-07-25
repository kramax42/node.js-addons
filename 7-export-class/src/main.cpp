#include <napi.h>
#include "lib/wrapped_class.h"

Napi::Object InitAll(Napi::Env env, Napi::Object exports) {
  return WrappedClass::Init(env, exports);
}

// Module name, register function.
NODE_API_MODULE(addon, InitAll)
