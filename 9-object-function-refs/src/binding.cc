#include <napi.h>
#include "native-addon.h"

Napi::Object Init(Napi::Env env, Napi::Object exports) {
  NativeAddon::Init(env, exports);
  return exports;
}

NODE_API_MODULE(addon, Init)