#include <json-c/json.h>

int main(void)
{
	json_object *root, *header;

	root = json_object_new_object();
	header = json_object_new_object();

	json_object_object_add(root, "header", header);

	json_object_to_file_ext("tmp.json", root, JSON_C_TO_STRING_PRETTY);

	json_object_put(root);

	return 0;
}
