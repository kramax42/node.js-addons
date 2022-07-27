#ifndef MY_OBJECT_H
#define MY_OBJECT_H

#include <napi.h>

class MyObject : public Napi::ObjectWrap<MyObject> {
 public:
  static void Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(Napi::Env env, Napi::Value arg);
  double Val() const { return val; }
  MyObject(const Napi::CallbackInfo& info);

 private:
  double val;
};

#endif
