/*
 * parse-json.c
 *
 *  Created on: Nov 19, 2018
 *      Author: bob
 */

#include <json-c/json.h>
#include <stdio.h>

#define BLUE 1

int main() {

	enum json_type type;
	char * string = "{\"tags\" : [ \"a\", \"b\", \"c\"], \"dataValue\" : 14, \"name\" : \"joys of programming\"}";

	json_object * jobj = json_tokener_parse(string);

	json_object_object_foreach(jobj, key, val) {
		printf("key: %s\n",key);

		printf("type: ");
		type = json_object_get_type(val);

		switch (type) {
		case json_type_null:
			printf("json_type_null\n");
			break;
		case json_type_boolean:
			printf("json_type_boolean\n");
			break;
		case json_type_double:
			printf("json_type_double\n");
			break;
		case json_type_int:
			printf("json_type_int: %d\n",json_object_get_int(val));
			break;
		case json_type_object:
			printf("json_type_object\n");
			break;
		case json_type_array:
			printf("json_type_array\n");
			break;
		case json_type_string:
			printf("json_type_string: %s\n",json_object_get_string(val));
			break;
		}

		printf("value: 0x%x\n",val);

	}
}
