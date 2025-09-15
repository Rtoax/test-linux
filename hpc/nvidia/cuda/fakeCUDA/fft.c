#include <cufft.h>
#include "debug.h"

cufftResult cufftGetProperty(libraryPropertyType type, int *value)
{
	LOG_DEBUG("type %d\n", type);

	switch (type) {
	case MAJOR_VERSION:
		*value = 12;
		break;
	case MINOR_VERSION:
		*value = 1;
		break;
	case PATCH_LEVEL:
		*value = 1;
		break;
	default:
		return CUFFT_INVALID_TYPE;
	}
	return CUFFT_SUCCESS;
}
