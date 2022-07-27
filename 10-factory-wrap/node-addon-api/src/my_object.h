#ifndef MY_OBJECT
#define MY_OBJECT

#include <napi.h>

class MyObject : public Napi::ObjectWrap<MyObject> {
 public:
  static Napi::Object Init(Napi::Env env, Napi::Object exports);
  static Napi::Object NewInstance(Napi::Env env, Napi::Value arg);
  MyObject(const Napi::CallbackInfo& info);

 private:
  Napi::Value PlusOne(const Napi::CallbackInfo& info);
  double counter;
};

#endif
