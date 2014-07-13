#include "func.h"

extern inline void foul_func1_obj_init(foul_func1_obj_t *, foul_func1_t *, foul_env_t *);
extern inline void foul_call1(foul_frame_t *, foul_func1_obj_t *, foul_obj_t *);

static size_t foul_func1_obj_size(foul_obj_t const *obj) {
	return sizeof(*(foul_func1_obj_t *) obj);
}

static foul_obj_t **foul_func1_obj_begin(foul_obj_t *obj) {
	return &((foul_func1_obj_t *) obj)->env;
}

static foul_obj_t **foul_func1_obj_end(foul_obj_t *obj) {
	return &((foul_func1_obj_t *) obj)->env + 1;
}

foul_obj_vtable_t const foul_func1_obj_vtable = {
	.size = foul_func1_obj_size,
	.begin = foul_func1_obj_begin,
	.end = foul_func1_obj_end
};