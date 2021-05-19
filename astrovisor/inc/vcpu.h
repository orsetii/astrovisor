#pragma once
#include "vmcb.h"

struct __vcpu_t {
	struct __vmcb_t* vmcb;
	unsigned __int64 vmcb_physical;
};
