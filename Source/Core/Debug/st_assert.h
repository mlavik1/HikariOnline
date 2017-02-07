#ifndef HIKARI_ASSERT_H
#define HIKARI_Assert_H

#include <assert.h>
#include "debug.h"

#define __Assert(expr) \
	if(!(expr)) \
		LOG_ERROR() << "Assertion error on " << #expr; \
	assert(expr);

#define __AssertComment(expr, comment) \
	if(!(expr)) \
		LOG_ERROR() << "Assertion error on " << #expr << ", \"" << comment << "\""; \
	assert(expr);
	

#endif
