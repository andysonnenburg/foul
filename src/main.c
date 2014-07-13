#include "foul.h"

#include <stddef.h>
#include <stdio.h>

void to_zero(foul_frame_t *head, foul_int_obj_t *x, foul_func1_obj_t *cont) {
	foul_frame_t tail;
	foul_int_obj_t y;
	printf("head: %p\n", &head);
	printf("x: %p\n", &x);
	printf("cont: %p\n", &cont);
	foul_frame_init(&tail, head);
	foul_frame_push_param(&tail, &head, sizeof(head));
	foul_frame_push_param(&tail, &x, sizeof(x));
	foul_frame_push_param(&tail, &cont, sizeof(cont));
	printf("param_begin: %p\n", tail.param_begin);
	foul_int_obj_init(&y);
	foul_frame_push_local(&tail, &y, foul_size(foul_obj(&y)));
	foul_mark(foul_obj(x));
	foul_mark(foul_obj(cont));
	if (foul_int(x) <= 1) {
		foul_call1(&tail, cont, foul_obj(x));
	} else {
		foul_set_int(&y, foul_int(x) - 1);
		to_zero(&tail, &y, cont);
	}
}

void print(foul_frame_t *parent, foul_env_t *env, foul_obj_t *arg) {
	printf("%i\n", foul_int((foul_int_obj_t *) arg));
}

int main(void) {
	foul_frame_t root;
	foul_int_obj_t x;
	foul_func1_obj_t print_func;
	foul_int_obj_t print_func_env;
	foul_frame_init(&root, NULL);
	foul_int_obj_init(&x);
	foul_frame_push_local(&root, foul_obj(&x), foul_size(foul_obj(&x)));
	foul_int_obj_init(&print_func_env);
	foul_frame_push_local(&root, foul_obj(&print_func_env), foul_size(foul_obj(&print_func_env)));
	foul_set_int(&x, 10);
	foul_func1_obj_init(&print_func, print, foul_obj(&print_func_env));
	to_zero(&root, &x, &print_func);
}
