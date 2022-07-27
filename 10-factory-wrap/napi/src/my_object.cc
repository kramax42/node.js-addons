#include "my_object.h"
#include <assert.h>

MyObject::MyObject() : env(nullptr), wrapper(nullptr) {}

MyObject::~MyObject() {
  napi_delete_reference(env, wrapper);
}

void MyObject::Destructor(napi_env env,
                          void* nativeObject,
                          void* finalize_hint) {
  reinterpret_cast<MyObject*>(nativeObject)->~MyObject();
}

#define DECLARE_NAPI_METHOD(name, func)                                        \
  { name, 0, func, 0, 0, 0, napi_default, 0 }

napi_status MyObject::Init(napi_env env) {
  napi_status status;
  napi_property_descriptor properties[] = {
      DECLARE_NAPI_METHOD("plusOne", PlusOne),
  };

  napi_value cons;
  status = napi_define_class(
      env, "MyObject", NAPI_AUTO_LENGTH, New, nullptr, 1, properties, &cons);
  if (status != napi_ok) return status;

  // We will need the constructor `cons` later during the life cycle of the
  // addon, so we store a persistent reference to it as the instance data for
  // our addon. This will enable us to use `napi_get_instance_data` at any
  // point during the life cycle of our addon to retrieve it. We cannot simply
  // store it as a global static variable, because that will render our addon
  // unable to support Node.js worker threads and multiple contexts on a single
  // thread.
  //
  // The finalizer we pass as a lambda will be called when our addon is unloaded
  // and is responsible for releasing the persistent reference and freeing the
  // heap memory where we stored the persistent reference.
  napi_ref* constructor = new napi_ref;
  status = napi_create_reference(env, cons, 1, constructor);
  assert(status == napi_ok);
  status = napi_set_instance_data(
      env,
      constructor,
      [](napi_env env, void* data, void* hint) {
        napi_ref* constructor = static_cast<napi_ref*>(data);
        napi_status status = napi_delete_reference(env, *constructor);
        assert(status == napi_ok);
        delete constructor;
      },
      nullptr);
  assert(status == napi_ok);

  return napi_ok;
}

napi_value MyObject::New(napi_env env, napi_callback_info info) {
  napi_status status;

  size_t argc = 1;
  napi_value args[1];
  napi_value js_this;
  status = napi_get_cb_info(env, info, &argc, args, &js_this, nullptr);
  assert(status == napi_ok);

  napi_valuetype value_type;
  status = napi_typeof(env, args[0], &value_type);
  assert(status == napi_ok);

  MyObject* obj = new MyObject();

  if (value_type == napi_undefined) {
    obj->counter = 0;
  } else {
    status = napi_get_value_double(env, args[0], &obj->counter);
    assert(status == napi_ok);
  }

  obj->env = env;
  status = napi_wrap(env,
                     js_this,
                     reinterpret_cast<void*>(obj),
                     MyObject::Destructor,
                     nullptr, /* finalize_hint */
                     &obj->wrapper);
  assert(status == napi_ok);

  return js_this;
}

napi_value MyObject::Constructor(napi_env env) {
  void* instance_data = nullptr;
  napi_status status = napi_get_instance_data(env, &instance_data);
  assert(status == napi_ok);
  napi_ref* constructor = static_cast<napi_ref*>(instance_data);

  napi_value cons;
  status = napi_get_reference_value(env, *constructor, &cons);
  assert(status == napi_ok);
  return cons;
}

napi_status MyObject::NewInstance(napi_env env,
                                  napi_value arg,
                                  napi_value* instance) {
  napi_status status;

  const int argc = 1;
  napi_value argv[argc] = {arg};

  status = napi_new_instance(env, Constructor(env), argc, argv, instance);
  if (status != napi_ok) return status;

  return napi_ok;
}

napi_value MyObject::PlusOne(napi_env env, napi_callback_info info) {
  napi_status status;

  napi_value js_this;
  status = napi_get_cb_info(env, info, nullptr, nullptr, &js_this, nullptr);
  assert(status == napi_ok);

  MyObject* obj;
  status = napi_unwrap(env, js_this, reinterpret_cast<void**>(&obj));
  assert(status == napi_ok);

  obj->counter += 1;

  napi_value returnNumber;
  status = napi_create_double(env, obj->counter, &returnNumber);
  assert(status == napi_ok);

  return returnNumber;
}
