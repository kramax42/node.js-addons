#include <assert.h>
#include <node_api.h>
#include <stdio.h>

static napi_value SumAllProps(napi_env env, napi_callback_info info) {
  napi_status status;

  size_t argc = 1;
  napi_value args[1];
  status = napi_get_cb_info(env, info, &argc, args, NULL, NULL);
  assert(status == napi_ok);

  if (argc != 1) {
    napi_throw_type_error(env, NULL, "Wrong number of arguments!");
    return NULL;
  }

  napi_valuetype arg_type;
  status = napi_typeof(env, args[0], &arg_type);
  assert(status == napi_ok);

  if (arg_type != napi_object) {
    napi_throw_type_error(env, NULL, "Wrong argument! Should be an object.");
    return NULL;
  }

  // Transform function argument to JS-like object.
  napi_value arg;
  status = napi_coerce_to_object(env, args[0], &arg);
  assert(status == napi_ok);

  // Get 'a' property of object.
  napi_value prop_a_str;
  status = napi_create_string_utf8(env, "a", NAPI_AUTO_LENGTH, &prop_a_str);
  assert(status == napi_ok);

  napi_value prop_a_napi;
  status = napi_get_property(env, arg, prop_a_str, &prop_a_napi);
  assert(status == napi_ok);

  napi_valuetype prop_a_valuetype;
  status = napi_typeof(env, prop_a_napi, &prop_a_valuetype);
  assert(status == napi_ok);

  if (prop_a_valuetype != napi_number) {
    napi_throw_type_error(
        env, NULL, "Wrong object property type. 'a' should be a number");
    return NULL;
  }

  double prop_a;
  status = napi_get_value_double(env, prop_a_napi, &prop_a);
  assert(status == napi_ok);

  // Get 'a' property of object.
  napi_value prop_b_str;
  status = napi_create_string_utf8(env, "b", NAPI_AUTO_LENGTH, &prop_b_str);
  assert(status == napi_ok);

  napi_value prop_b_napi;
  status = napi_get_property(env, arg, prop_b_str, &prop_b_napi);
  assert(status == napi_ok);

  napi_valuetype prop_b_valuetype;
  status = napi_typeof(env, prop_b_napi, &prop_b_valuetype);
  assert(status == napi_ok);

  if (prop_b_valuetype != napi_number) {
    napi_throw_type_error(
        env, NULL, "Wrong object property type. 'b' should be a number");
    return NULL;
  }

  double prop_b;
  status = napi_get_value_double(env, prop_b_napi, &prop_b);
  assert(status == napi_ok);

  // Calculate sum of properties.
  napi_value sum;
  status = napi_create_double(env, prop_a + prop_b, &sum);
  assert(status == napi_ok);

  return sum;
}

#define DECLARE_NAPI_METHOD(name, func)                                        \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_value Init(napi_env env, napi_value exports) {
  napi_property_descriptor addDescriptor =
      DECLARE_NAPI_METHOD("sumAllProps", SumAllProps);
  napi_status status = napi_define_properties(env, exports, 1, &addDescriptor);
  assert(status == napi_ok);
  return exports;
}

NAPI_MODULE(addon, Init)
