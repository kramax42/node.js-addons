#include <assert.h>
#include <node_api.h>

static napi_value CreateObject(napi_env env, const napi_callback_info info) {
  napi_status status;

  size_t argc = 1;
  napi_value args[1];
  status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  assert(status == napi_ok);

  napi_value obj;
  status = napi_create_object(env, &obj);
  assert(status == napi_ok);

  napi_valuetype arg_type;
  status = napi_typeof(env, args[0], &arg_type);
  assert(status == napi_ok);

  if (arg_type != napi_string) {
    napi_throw_type_error(
        env, NULL, "Wrong argument type! Should be as string");
    return obj;
  }

  status = napi_set_named_property(env, obj, "msg", args[0]);
  assert(status == napi_ok);

  return obj;
}

static napi_value Init(napi_env env, napi_value exports) {
  napi_value new_exports;
  napi_status status = napi_create_function(
      env, "", NAPI_AUTO_LENGTH, CreateObject, NULL, &new_exports);
  assert(status == napi_ok);
  return new_exports;
}

NAPI_MODULE(addon, Init)
