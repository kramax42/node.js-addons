#include <assert.h>
#include <node_api.h>

static napi_value SayHello(napi_env env, napi_callback_info info) {
  napi_value world;
  napi_status status =
      napi_create_string_utf8(env, "Hello, world!", NAPI_AUTO_LENGTH, &world);
  assert(status == napi_ok);
  return world;
}

#define DECLARE_NAPI_METHOD(name, func)                                        \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

static napi_value Init(napi_env env, napi_value exports) {
  napi_property_descriptor desc = DECLARE_NAPI_METHOD("sayHello", SayHello);
  napi_status status = napi_define_properties(env, exports, 1, &desc);
  assert(status == napi_ok);
  return exports;
}

NAPI_MODULE(addon, Init)
