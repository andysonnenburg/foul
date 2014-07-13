#ifndef FOUL_OBJ_H
#define FOUL_OBJ_H

#include <stddef.h>

typedef struct foul_obj foul_obj_t;
typedef struct foul_obj_vtable foul_obj_vtable_t;

struct foul_obj {
	foul_obj_vtable_t const *vtable;
	union {
		size_t offset;
		foul_obj_t *forward;
	};
};

typedef size_t (*foul_obj_size_t)(foul_obj_t const *);
typedef foul_obj_t **(*foul_obj_begin_t)(foul_obj_t *);
typedef foul_obj_t **(*foul_obj_end_t)(foul_obj_t *);

struct foul_obj_vtable {
	foul_obj_size_t const size;
	foul_obj_begin_t const begin;
	foul_obj_end_t const end;
};

inline void foul_obj_init(foul_obj_t *obj, foul_obj_vtable_t const *vtable) {
	obj->vtable = vtable;
	obj->offset = 0;
}

#define foul_obj(obj) &(obj)->super

inline size_t foul_size(foul_obj_t const *obj) {
	return obj->vtable->size(obj);
}

inline foul_obj_t **foul_begin(foul_obj_t *obj) {
	return obj->vtable->begin(obj);
}

inline foul_obj_t **foul_end(foul_obj_t *obj) {
	return obj->vtable->end(obj);
}

#endif
