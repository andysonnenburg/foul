#include "int.h"

extern inline void foul_int_obj_init(foul_int_obj_t *);
extern inline int foul_int(foul_int_obj_t const *);
extern inline void foul_set_int(foul_int_obj_t *, int);

static size_t foul_int_obj_size(foul_obj_t const *obj) {
	return sizeof(*((foul_int_obj_t*) obj));
}

static foul_obj_t **foul_int_obj_begin(foul_obj_t *obj) {
	return NULL;
}

static foul_obj_t **foul_int_obj_end(foul_obj_t *obj) {
	return NULL;
}

foul_obj_vtable_t const foul_int_obj_vtable = {
	.size = foul_int_obj_size,
	.begin = foul_int_obj_begin,
	.end = foul_int_obj_end
};
