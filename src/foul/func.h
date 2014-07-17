#ifndef FOUL_FUNC_H
#define FOUL_FUNC_H

#include "obj.h"

#include <setjmp.h>

typedef struct foul_func0_obj foul_func0_obj_t;
typedef struct foul_func1_obj foul_func1_obj_t;

typedef struct foul_env {
	jmp_buf buf;
	foul_func0_obj_t *func;
} foul_env_t;

typedef foul_obj_t foul_func_env_t;

typedef void foul_func0_t(foul_env_t *, foul_func_env_t *);

struct foul_func0_obj {
	foul_obj_t super;
	foul_func0_t *func;
	foul_func_env_t *env;
};

extern foul_obj_vtable_t const foul_func0_obj_vtable;

inline void foul_func0_obj_init(foul_func0_obj_t *obj,
                                foul_func0_t *func,
                                foul_func_env_t *env) {
	foul_obj_init(&obj->super, &foul_func0_obj_vtable);
	obj->func = func;
	obj->env = env;
}

inline void foul_call0(foul_env_t *env, foul_func0_obj_t *obj) {
	obj->func(env, obj->env);
}

typedef void foul_func1_t(foul_env_t *, foul_func_env_t *, foul_obj_t *);

struct foul_func1_obj {
	foul_obj_t super;
	foul_func1_t *func;
	foul_func_env_t *env;
};

extern foul_obj_vtable_t const foul_func1_obj_vtable;

inline void foul_func1_obj_init(foul_func1_obj_t *obj,
                                foul_func1_t *func,
                                foul_func_env_t *env) {
	foul_obj_init(&obj->super, &foul_func1_obj_vtable);
	obj->func = func;
	obj->env = env;
}

inline void foul_call1(foul_env_t *env, foul_func1_obj_t *obj, foul_obj_t *arg) {
	obj->func(env, obj->env, arg);
}

#endif
