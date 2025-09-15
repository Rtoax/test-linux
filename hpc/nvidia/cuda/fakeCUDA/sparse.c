#define DISABLE_CUSPARSE_DEPRECATED	1
#include <cusparse.h>

#include "debug.h"


cusparseStatus_t cusparseGetProperty(libraryPropertyType type, int *value)
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
		return CUSPARSE_STATUS_INVALID_VALUE;
	}
	return CUSPARSE_STATUS_SUCCESS;
}
