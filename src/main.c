#include "foul.h"

#include <stddef.h>
#include <stdio.h>

void to_zero(foul_env_t *env, foul_int_obj_t *x, foul_func1_obj_t *cont) {
	foul_int_obj_t y;
	foul_int_obj_init(&y);
	size_t size = foul_mark(foul_obj(x), 0);
	printf("%u\n", size);
	size = foul_mark(foul_obj(cont), size);
	printf("%u\n", size);
	if (foul_int(x) <= 1) {
		foul_call1(env, cont, foul_obj(x));
	} else {
		foul_set_int(&y, foul_int(x) - 1);
		to_zero(env, &y, cont);
	}
}

void print(foul_env_t *env, foul_func_env_t *obj, foul_obj_t *arg) {
	printf("%i\n", foul_int((foul_int_obj_t *) arg));
}

int main(void) {
	foul_env_t env;
	if (setjmp(env.buf)) {
		foul_call0(&env, env.func);
	} else {
		foul_int_obj_t x;
		foul_func1_obj_t print_func;
		foul_int_obj_t print_func_env;
		foul_int_obj_init(&x);
		foul_int_obj_init(&print_func_env);
		foul_set_int(&x, 10);
		foul_func1_obj_init(&print_func, print, foul_obj(&print_func_env));
		to_zero(&env, &x, &print_func);
	}
}
