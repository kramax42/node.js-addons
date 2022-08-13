#include <napi.h>
#include "echo_async_worker.h"

class ExampleAddon : public Napi::Addon<ExampleAddon> {
 public:
  ExampleAddon(Napi::Env env, Napi::Object exports) {
    // In the constructor we declare the functions the add-on makes available
    // to JavaScript.
    DefineAddon(
        exports,
        {InstanceMethod("increment", &ExampleAddon::Increment),
         InstanceMethod("echoAsyncWorker", &ExampleAddon::EchoAsyncWorker),

         // We can also attach plain objects to `exports`, and instance methods
         // as properties of those sub-objects.
         InstanceValue(
             "subObject",
             DefineProperties(
                 Napi::Object::New(env),
                 {InstanceMethod("decrement", &ExampleAddon::Decrement)}),
             napi_enumerable)});
  }

 private:
  // This method has access to the data stored in the environment because it is
  // an instance method of `ExampleAddon` and because it was listed among the
  // property descriptors passed to `DefineAddon()` in the constructor.
  Napi::Value Increment(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), ++value);
  }

  // This method has access to the data stored in the environment because it is
  // an instance method of `ExampleAddon` and because it was exposed to
  // JavaScript by calling `DefineProperties()` with the object onto which it is
  // attached.
  Napi::Value Decrement(const Napi::CallbackInfo& info) {
    return Napi::Number::New(info.Env(), --value);
  }

  Napi::Value EchoAsyncWorker(const Napi::CallbackInfo& info) {
    // You need to validate the arguments here.
    std::string in = info[0].As<Napi::String>();
    Napi::Function cb = info[1].As<Napi::Function>();
    EchoWorker* wk = new EchoWorker(cb, in);
    wk->Queue();
    return info.Env().Undefined();
  }

  // Data stored in these variables is unique to each instance of the add-on.
  uint32_t value = 42;
};

// The macro announces that instances of the class `ExampleAddon` will be
// created for each instance of the add-on that must be loaded into Node.js.
NODE_API_ADDON(ExampleAddon)