#ifndef MY_OBJECT_H
#define MY_OBJECT_H

#include <node_api.h>

class MyObject {
 public:
  static napi_status Init(napi_env env);
  static void Destructor(napi_env env, void* nativeObject, void* finalize_hint);
  static napi_status NewInstance(napi_env env,
                                 napi_value arg,
                                 napi_value* instance);
  double Val() const { return val; }

 private:
  MyObject();
  ~MyObject();

  static inline napi_value Constructor(napi_env env);
  static napi_value New(napi_env env, napi_callback_info info);
  double val;
  napi_env env;
  napi_ref wrapper;
};

#endif
