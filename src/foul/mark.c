#include "mark.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

void set_marked(foul_obj_t *obj) {
	obj->vtable = (foul_obj_vtable_t *) (((uintptr_t) obj->vtable) | 1);
}

void foul_mark(foul_obj_t *obj) {
	for (foul_obj_t *parent = NULL, *child = obj;;) {
		puts("current");
		set_marked(child);
		printf("offset: %u\n", (unsigned int) child->offset);
		if (foul_begin(child) + child->offset != foul_end(child)) {
			puts("down");
			foul_obj_t **i = foul_begin(child) + child->offset;
			++child->offset;
			printf("%p\n", i);
			foul_obj_t *tmp = *i;
			printf("%p\n", tmp);
			if (!foul_is_marked(tmp)) {
				*i = parent;
				parent = child;
				child = tmp;
			}
		} else {
			puts("up");
			if (!parent) {
				return;
			}
			foul_obj_t *tmp = parent;
			foul_obj_t **i = foul_begin(tmp) + tmp->offset;
			parent = *i;
			*i = child;
			child = tmp;
		}
	}
}
