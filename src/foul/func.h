#ifndef FOUL_FUNC_H
#define FOUL_FUNC_H

#include "frame.h"
#include "obj.h"

typedef foul_obj_t foul_env_t;

typedef void foul_func1_t(foul_frame_t *, foul_env_t *, foul_obj_t *);

typedef struct foul_func1_obj {
	foul_obj_t super;
	foul_func1_t *func;
	foul_env_t *env;
} foul_func1_obj_t;

extern foul_obj_vtable_t const foul_func1_obj_vtable;

inline void foul_func1_obj_init(foul_func1_obj_t *obj, foul_func1_t *func, foul_env_t *env) {
	foul_obj_init(&obj->super, &foul_func1_obj_vtable);
	obj->func = func;
	obj->env = env;
}

inline void foul_call1(foul_frame_t *parent, foul_func1_obj_t *obj, foul_obj_t *arg) {
	obj->func(parent, obj->env, arg);
}

#endif
