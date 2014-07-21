#include "mark.h"

#include <stddef.h>

size_t foul_mark(foul_obj_t *obj, size_t offset) {
	if (foul_is_marked(obj)) {
		return offset;
	}
	foul_obj_t *parent = NULL;
	foul_obj_iterator_t first = foul_begin(obj);
	foul_obj_iterator_t last = foul_end(obj);
	foul_set_marked(obj);
	while (true) {
		foul_obj_iterator_t i = first + obj->offset;
		if (i != last) {
			foul_obj_t *tmp = *i;
			if (!foul_is_marked(tmp)) {
				*i = parent;
				parent = obj;
				obj = tmp;
				foul_set_marked(obj);
				first = foul_begin(obj);
				last = foul_end(obj);
			} else {
				++obj->offset;
			}
		} else {
			obj->offset = 0;
			offset += foul_size(obj);
			if (!parent) {
				return offset;
			}
			foul_obj_t *tmp = parent;
			first = foul_begin(tmp);
			last = foul_end(tmp);
			i = first + tmp->offset;
			parent = *i;
			*i = obj;
			obj = tmp;
			++obj->offset;
		}
	}
}
