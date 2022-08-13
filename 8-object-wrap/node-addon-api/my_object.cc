#include "my_object.h"

Napi::Object MyObject::Init(Napi::Env env, Napi::Object exports) {
  // This method is used to hook the accessor and method callbacks.
  Napi::Function func =
      DefineClass(env,
                  "MyObject",
                  {
                      InstanceMethod("plusOne", &MyObject::PlusOne),
                      InstanceMethod("value", &MyObject::GetValue),
                      InstanceMethod("multiply", &MyObject::Multiply),
                      
                      // StaticMethod<&MyObject::CreateNewItem>(
                      //     "CreateNewItem",
                      //     static_cast<napi_property_attributes>(
                      //         napi_writable | napi_configurable)),
                  });

  Napi::FunctionReference* constructor = new Napi::FunctionReference();

  // Create a persistent reference to the class constructor. This will allow
  // a function called on a class prototype and a function
  // called on instance of a class to be distinguished from each other.
  *constructor = Napi::Persistent(func);
  exports.Set("MyObject", func);

  // Store the constructor as the add-on instance data. This will allow this
  // add-on to support multiple instances of itself running on multiple worker
  // threads, as well as multiple instances of itself running in different
  // contexts on the same thread.
  //
  // By default, the value set on the environment here will be destroyed when
  // the add-on is unloaded using the `delete` operator, but it is also
  // possible to supply a custom deleter.
  env.SetInstanceData(constructor);

  return exports;
}

MyObject::MyObject(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<MyObject>(info) {
  Napi::Env env = info.Env();

  if (info.Length() <= 0 || !info[0].IsNumber()) {
    Napi::TypeError::New(env, "Number expected").ThrowAsJavaScriptException();
    return;
  }

  Napi::Number value = info[0].As<Napi::Number>();
  this->value = value.DoubleValue();
}

Napi::Value MyObject::GetValue(const Napi::CallbackInfo& info) {
  return Napi::Number::New(info.Env(), this->value);
}

Napi::Value MyObject::PlusOne(const Napi::CallbackInfo& info) {
  this->value = this->value + 1;
  return MyObject::GetValue(info);
}

Napi::Value MyObject::Multiply(const Napi::CallbackInfo& info) {
  Napi::Number multiple;

  if (info.Length() <= 0 || !info[0].IsNumber()) {
    multiple = Napi::Number::New(info.Env(), 1);
  } else {
    multiple = info[0].As<Napi::Number>();
  }

  Napi::Object obj = info.Env().GetInstanceData<Napi::FunctionReference>()->New(
      {Napi::Number::New(info.Env(), this->value * multiple.DoubleValue())});

  return obj;
}

// Create a new item using the constructor stored during Init.
// Napi::Value MyObject::CreateNewItem(const Napi::CallbackInfo& info) {
//   // Retrieve the instance data we stored during `Init()`. We only stored the
//   // constructor there, so we retrieve it here to create a new instance of the
//   // JS class the constructor represents.
//   Napi::FunctionReference* constructor =
//       info.Env().GetInstanceData<Napi::FunctionReference>();
//   return constructor->New({Napi::Number::New(info.Env(), 42)});
// }