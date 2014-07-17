#include "mark.h"

#include <stddef.h>
#include <stdint.h>

static void set_marked(foul_obj_t *obj) {
	obj->vtable = (foul_obj_vtable_t *) (((uintptr_t) obj->vtable) | 1);
}

void foul_mark(foul_obj_t *obj) {
	for (foul_obj_t *parent = NULL;;) {
		set_marked(obj);
		foul_obj_iterator_t i = foul_begin(obj) + obj->offset;
		if (i != foul_end(obj)) {
			foul_obj_t *tmp = *i;
			if (!foul_is_marked(tmp)) {
				*i = parent;
				parent = obj;
				obj = tmp;
			} else {
				++obj->offset;
			}
		} else {
			if (!parent) {
				break;
			}
			foul_obj_t *tmp = parent;
			i = foul_begin(tmp) + tmp->offset;
			parent = *i;
			*i = obj;
			obj = tmp;
		}
	}
}
