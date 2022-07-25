#ifndef WRAPPED_CLASS
#define WRAPPED_CLASS

#include <napi.h>
#include "class_cpp.h"

class WrappedClass : public Napi::ObjectWrap<WrappedClass> {
 public:
  WrappedClass(const Napi::CallbackInfo& info);

  // Init function for setting the export key to JS.
  static Napi::Object Init(Napi::Env env, Napi::Object exports);

  ClassCPP* GetInternalInstance();

 private:
  // Reference to store the class definition that needs to be exported to JS.
  static Napi::FunctionReference constructor;

  // Wrapped functions.
  Napi::Value GetValue(const Napi::CallbackInfo& info);
  Napi::Value Add(const Napi::CallbackInfo& info);

  // Internal instance of ClassCPP used to perform actual operations.
  ClassCPP* class_cpp_instance;
};

#endif