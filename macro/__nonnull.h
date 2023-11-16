#pragma once

#ifndef __attribute_nonnull__
#define __attribute_nonnull__(params) __attribute__((__nonnull__ params))
#endif
#ifndef __nonnull
#define __nonnull(params) __attribute_nonnull__(params)
#endif
