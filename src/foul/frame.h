#ifndef FOUL_FRAME_H
#define FOUL_FRAME_H

#include <stddef.h>

typedef struct foul_frame foul_frame_t;

struct foul_frame {
	foul_frame_t *parent;
	void *param_begin;
	size_t param_size;
	void *local_begin;
	size_t local_size;
};

inline void foul_frame_init(foul_frame_t *frame, foul_frame_t *parent) {
	frame->parent = parent;
	frame->param_begin = 0;
	frame->param_size = 0;
	frame->local_begin = 0;
	frame->local_size = 0;
}

inline void foul_frame_push_param(foul_frame_t *frame, void *addr, size_t size) {
	if (frame->param_begin < addr) {
		frame->param_begin = addr;
	}
	frame->param_size += size;
}

inline void foul_frame_push_local(foul_frame_t *frame, void *addr, size_t size) {
	if (frame->local_begin < addr) {
		frame->local_begin = addr;
	}
	frame->local_size += size;
}

#endif
