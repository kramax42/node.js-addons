#include "wrapped_class.h"

Napi::FunctionReference WrappedClass::constructor;

Napi::Object WrappedClass::Init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);

  // 'env' is the environment that represent
  // an independent instance of the JavaScript runtime.

  // 'func' is used to define the class that will be exported to JS.
  Napi::Function func =
      DefineClass(env,
                  "WrappedClass",
                  {
                      InstanceMethod("add", &WrappedClass::Add),
                      InstanceMethod("getValue", &WrappedClass::GetValue),
                  });

  // 'func' is assigned to constructor
  // which is a static function reference in c++.
  constructor = Napi::Persistent(func);
  constructor.SuppressDestruct();

  exports.Set("WrappedClass", func);
  return exports;
}

WrappedClass::WrappedClass(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<WrappedClass>(info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 1) {
    Napi::TypeError::New(env, "Only one argument expected")
        .ThrowAsJavaScriptException();
  }

  // Make new instance from instance derived in constructor.
  if (!info[0].IsNumber()) {
    Napi::Object object_parent = info[0].As<Napi::Object>();

    WrappedClass* example_parent =
        Napi::ObjectWrap<WrappedClass>::Unwrap(object_parent);

    ClassCPP* parent_actual_class_instance =
        example_parent->GetInternalInstance();

    this->class_cpp_instance =
        new ClassCPP(parent_actual_class_instance->getValue());

  } else {
    Napi::Number value = info[0].As<Napi::Number>();
    this->class_cpp_instance = new ClassCPP(value.DoubleValue());
  }
}

Napi::Value WrappedClass::GetValue(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  double value = this->class_cpp_instance->getValue();
  return Napi::Number::New(env, value);
}

Napi::Value WrappedClass::Add(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if (info.Length() != 1 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
  }

  Napi::Number toAdd = info[0].As<Napi::Number>();
  double answer = this->class_cpp_instance->add(toAdd.DoubleValue());

  return Napi::Number::New(info.Env(), answer);
}

ClassCPP* WrappedClass::GetInternalInstance() {
  return this->class_cpp_instance;
}