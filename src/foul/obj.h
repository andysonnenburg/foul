#ifndef FOUL_OBJ_H
#define FOUL_OBJ_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

typedef struct foul_obj foul_obj_t;
typedef struct foul_obj_vtable foul_obj_vtable_t;

struct foul_obj {
	foul_obj_vtable_t const *vtable;
	size_t offset;
};

typedef foul_obj_t **foul_obj_iterator_t;
typedef size_t (*foul_obj_size_t)(foul_obj_t const *);
typedef foul_obj_iterator_t (*foul_obj_begin_t)(foul_obj_t *);
typedef foul_obj_iterator_t (*foul_obj_end_t)(foul_obj_t *);

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

inline bool foul_is_marked(foul_obj_t const* obj) {
	return ((uintptr_t) obj->vtable) & 1;
}

inline void foul_set_marked(foul_obj_t *obj) {
	obj->vtable = (foul_obj_vtable_t *) (((uintptr_t) obj->vtable) | 1);
}

inline void foul_set_unmarked(foul_obj_t *obj) {
	obj->vtable = (foul_obj_vtable_t *) (((uintptr_t) obj->vtable) & ~1);
}

inline size_t foul_size(foul_obj_t const *obj) {
	return ((foul_obj_vtable_t *) (((uintptr_t) obj->vtable) & ~1))->size(obj);
}

inline foul_obj_iterator_t foul_begin(foul_obj_t *obj) {
	return ((foul_obj_vtable_t *) (((uintptr_t) obj->vtable) & ~1))->begin(obj);
}

inline foul_obj_iterator_t foul_end(foul_obj_t *obj) {
	return ((foul_obj_vtable_t *) (((uintptr_t) obj->vtable) & ~1))->end(obj);
}

#endif
