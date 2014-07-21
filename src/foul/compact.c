#include "compact.h"

#include "obj.h"

char *foul_compact(char *first, char *last) {
	char *i = first;
	char *j = first;
	for (i = first; i != last;) {
		foul_obj_t *obj = (foul_obj_t *) i;
		size_t n = foul_size(obj);
		if (foul_is_marked(obj)) {
			foul_set_unmarked(obj);
			obj->offset = j - first;
			j += n;
		}
		i += n;
	}
	return i;
}
