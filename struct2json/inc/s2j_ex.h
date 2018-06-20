/*
 * This file is part of the struct2json Library.
 *
 * Copyright (c) 2018, YuXuebao, <yuxuebao@msn.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * 'Software'), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * Function: It is an head file for this library. You can see all be called functions.
 * Created on: 2018-06-20
 */

#ifndef __S2J_EX_H__
#define __S2J_EX_H__

#include "s2j.h"

#ifdef __cplusplus
extern "C" {
#endif

/* struct2json software version number */
//#define S2J_SW_VERSION                "2.0.0"

/* Set child structure type element for JSON object by function [cJSON * struct_to_json_##type(void*)] */
#define s2j_json_set_struct_element_by_func(to_json, from_struct, type, element) \
	cJSON_AddItemToObject(to_json, #element, struct_to_json_##type(&((from_struct)->element)))


/* Set child structure array type element for JSON object by function [cJSON * struct_to_json_##type(void*)] */
#define s2j_json_set_struct_array_element_by_func(to_json, from_struct, type, element, array_size) \
	cJSON * array_##element = cJSON_CreateArray();	\
	cJSON_AddItemToObject(to_json, #element, array_##element); \
	int i = 0; \
	for (; i < array_size; i++) \
		cJSON_AddItemToArray(array_##element, struct_to_json_##type(&((from_struct)->element[i])));  \


/* Get child structure type element for structure object by function [void *json_to_struct_#type(cJSON*)]*/
#define s2j_struct_get_struct_element_by_func(to_struct, from_json, type, element) \
		S2J_STRUCT_GET_STRUCT_ELEMENT(struct_##element, to_struct, json_##element, from_json, type, element)	 \
		type * p_##element = (type *)json_to_struct_##type(json_##element); \
		*(struct_##element) = *(p_##element); \
		s2j_delete_struct_obj(p_##element); 


/* Get struct array type element for structure object by function [void *json_to_struct_#type(cJSON*)] */
#define s2j_struct_get_struct_array_element_by_func(to_struct, from_json, type, element) \
	{ \
		cJSON *array_##element, *array_item_##element; \
		size_t index = 0, size = 0; \
		array_##element = cJSON_GetObjectItem(from_json, #element); \
		if (array_##element) { \
			size = cJSON_GetArraySize(array_##element); \
			for (;index < size; index++) { \
				array_item_##element = cJSON_GetArrayItem(array_##element, index); \
				if (array_item_##element) { \
					type *struct_##element = &((to_struct)->element[index]); \
					type * p##element = (type *)json_to_struct_##type(array_item_##element); \
					*(struct_##element) = *(p##element); \
					s2j_delete_struct_obj(p##element); \
				} \
			} \
		} \
	}

#ifdef __cplusplus
}
#endif /* end of __cplusplus */

#endif /* __S2J_EX_H__ */
