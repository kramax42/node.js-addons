#ifndef SYNC_CALCULATIONS_H
#define SYNC_CALCULATIONS_H

#include <napi.h>
#include "pi_estimate.h"  // NOLINT(build/include)

Napi::Value CalculateSync(const Napi::CallbackInfo& info);

#endif
