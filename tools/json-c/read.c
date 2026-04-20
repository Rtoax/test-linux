#include <stdio.h>
#include <json-c/json.h>

char *read_file(const char *filename)
{
	FILE *fp = fopen(filename, "rb");
	if (!fp) {
		perror("fopen");
		return NULL;
	}

	fseek(fp, 0, SEEK_END);
	long size = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	char *buffer = (char *)malloc(size + 1);
	if (!buffer) {
		perror("malloc");
		fclose(fp);
		return NULL;
	}

	fread(buffer, 1, size, fp);
	buffer[size] = '\0';
	fclose(fp);
	return buffer;
}

int main(void)
{
	char *json = read_file("tmp.json");
	json_object *root, *header;

	root = json_tokener_parse(json);
	json_object_object_get_ex(root, "header", &header);

	json_object *author_obj;
	if (json_object_object_get_ex(header, "author", &author_obj)) {
		const char *author = json_object_get_string(author_obj);
		printf("author: %s\n", author);
	} else {
		printf("author field not found\n");
	}

	json_object *age_obj;
	if (json_object_object_get_ex(header, "age", &age_obj)) {
		int age = json_object_get_int(age_obj);
		printf("age: %d\n", age);
	} else {
		printf("age field not found\n");
	}

	json_object *array_obj;
	if (json_object_object_get_ex(header, "array", &array_obj) &&
	    json_object_get_type(array_obj) == json_type_array) {
		int len = json_object_array_length(array_obj);
		printf("array length: %d\n", len);

		for (int i = 0; i < len; i++) {
			json_object *elem =
				json_object_array_get_idx(array_obj, i);
			json_type type = json_object_get_type(elem);

			if (type == json_type_int) {
				int val = json_object_get_int(elem);
				printf("array[%d] = int: %d\n", i, val);
			} else if (type == json_type_string) {
				const char *val = json_object_get_string(elem);
				printf("array[%d] = string: %s\n", i, val);
			} else {
				printf("array[%d] = other type\n", i);
			}
		}
	} else {
		printf("array field not found or not an array\n");
	}

	json_object *footer;
	if (json_object_object_get_ex(root, "footer", &footer)) {
		if (json_object_get_type(footer) == json_type_object) {
			printf("footer is an empty object (size: %d)\n",
			       json_object_object_length(footer));
		}
	} else {
		printf("footer field not found\n");
	}

	json_object_put(root);

	free(json);
	return 0;
}
