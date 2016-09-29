#define MK_array(name, type)\
struct name {\
	size_t s;\
	size_t c;\
	type *a;\
};\
/* Definitions of all functions. */\
static inline bool name##_alloc(struct name *a, size_t size);\
static inline bool name##_push(struct name *a, type o);\
static inline bool name##_mpush(struct name *a, type *o, size_t size);\
static inline bool name##_reserve(struct name *a, size_t sized);\
static inline bool name##_trim(struct name *a);\
static bool name##_setsize(struct name *a, size_t size);\
\
static inline bool name##_alloc(struct name *a, size_t size) {\
	a->s = 0;\
	a->c = 0;\
	a->a = NULL;\
	return name##_setsize(a, size);\
}\
\
static inline bool name##_push(struct name *a, type o) {\
	if (name##_reserve(a, 1)) {\
		return true;\
	}\
	a->a[a->c] = o;\
	a->c++;\
	return false;\
}\
\
static inline bool name##_mpush(struct name *a, type *o, size_t size) {\
	if (name##_reserve(a, size)) {\
		return true;\
	}\
	memcpy(a->a + a->c, o, size * sizeof(type));\
	a->c += size;\
	return false;\
}\
\
static inline bool name##_reserve(struct name *a, size_t size) {\
	if (a->c + size > a->s) {\
		size_t new_size = a->s * 5 / 4 + size;\
		return name##_setsize(a, new_size);\
	}\
	return false;\
}\
static inline bool name##_trim(struct name *a) {\
	if (a->s > a->c) {\
		return name##_setsize(a, a->c);\
	}\
	return false;\
}\
\
static bool name##_setsize(struct name *a, size_t size) {\
	/* Silence waring about unused functions. */\
	(void) name##_alloc;\
	(void) name##_push;\
	(void) name##_mpush;\
	(void) name##_reserve;\
	(void) name##_trim;\
	\
	/* Try to resize array. */\
	type *tmp;\
	tmp = realloc(a->a, sizeof(type) * size);\
	if (!tmp) {\
		return true;\
	}\
	if (a->c > size) {\
		a->c = size;\
	}\
	a->s = size;\
	a->a = tmp;\
	return false;\
}
