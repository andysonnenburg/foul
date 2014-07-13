#include "frame.h"

extern inline void foul_frame_init(foul_frame_t *, foul_frame_t *);
extern inline void foul_frame_push_param(foul_frame_t *, void *, size_t);
extern inline void foul_frame_push_local(foul_frame_t *, void *, size_t);
