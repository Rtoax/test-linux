#include <stdio.h>
#include <json-c/json.h>

int main(void)
{
	json_object *root, *header, *footer, *array, *body, *item;

	root = json_object_new_object();
	header = json_object_new_object();
	body = json_object_new_object();
	footer = json_object_new_object();

	json_object_object_add(root, "header", header);
	json_object_object_add(root, "body", body);
	json_object_object_add(root, "footer", footer);

	json_object_object_add(header, "author",
			       json_object_new_string("Rong Tao"));
	json_object_object_add(header, "age", json_object_new_int(18));

	array = json_object_new_array();
	json_object_array_add(array, json_object_new_int(1));
	json_object_array_add(array, json_object_new_int(2));
	json_object_array_add(array, json_object_new_string("3"));

	json_object_object_add(header, "array", array);

	/* Note: item1, item2 could not have same name */
	item = json_object_new_object();
	json_object_object_add(item, "type", json_object_new_string("ball"));
	json_object_object_add(body, "item1", item);

	item = json_object_new_object();
	json_object_object_add(item, "type", json_object_new_string("cook"));
	json_object_object_add(body, "item2", item);

	printf("%s\n",
	       json_object_to_json_string_ext(root, JSON_C_TO_STRING_PRETTY));

	json_object_to_file_ext("tmp.json", root, JSON_C_TO_STRING_PRETTY);

	json_object_put(root);

	return 0;
}
