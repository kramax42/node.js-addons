#ifndef TEST_ADDONS_NAPI_7_FACTORY_WRAP_MYOBJECT_H_
#define TEST_ADDONS_NAPI_7_FACTORY_WRAP_MYOBJECT_H_

#include <node_api.h>

class MyObject {
 public:
  static napi_status Init(napi_env env);
  static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);
  static napi_status NewInstance(napi_env env,
                                 napi_value arg,
                                 napi_value* instance);

 private:
  MyObject();
  ~MyObject();

  static inline napi_value Constructor(napi_env env);
  static napi_value New(napi_env env, napi_callback_info info);
  static napi_value PlusOne(napi_env env, napi_callback_info info);
  double counter;
  napi_env env;
  napi_ref wrapper;
};

#endif  // TEST_ADDONS_NAPI_7_FACTORY_WRAP_MYOBJECT_H_
