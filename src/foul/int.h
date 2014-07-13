#ifndef FOUL_INT_H
#define FOUL_INT_H

#include "obj.h"

typedef struct foul_int_obj {
	foul_obj_t super;
	int value;
} foul_int_obj_t;

extern foul_obj_vtable_t const foul_int_obj_vtable;

inline void foul_int_obj_init(foul_int_obj_t *obj) {
	foul_obj_init(&obj->super, &foul_int_obj_vtable);
}

inline int foul_int(foul_int_obj_t const *obj) {
	return obj->value;
}

inline void foul_set_int(foul_int_obj_t *obj, int value) {
	obj->value = value;
}

#endif
