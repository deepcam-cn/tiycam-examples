#ifndef _jbuffer_h_
#define _jbuffer_h_

#ifdef __cplusplus
extern "C" {
#endif

enum {
	JBUFFER_OPT_INVALID = 0,
	JBUFFER_OPT_OVERWRITE_MODE,		/* int */
	JBUFFER_OPT_BLOCK_NUMBER,		/* unsigned int */
};

typedef struct _jbuffer_ctx		jbuffer_ctx_t;
typedef struct _jbuffer_ctx*	jbuffer_hdl_t;

jbuffer_hdl_t jbuffer_create(const char *name, int size);
void jbuffer_destroy(jbuffer_hdl_t hdl);
int jbuffer_set_options(jbuffer_hdl_t hdl, int opt, const void *val, int len);
void *jbuffer_alloc(jbuffer_hdl_t hdl, int size);
int jbuffer_release(jbuffer_hdl_t hdl, int size);

jbuffer_hdl_t jbuffer_open(const char *name);
void jbuffer_close(jbuffer_hdl_t hdl);
const void *jbuffer_get(jbuffer_hdl_t hdl, int *size);
const void *jbuffer_get_last(jbuffer_hdl_t hdl, int *size);

#ifdef __cplusplus
}
#endif

#endif /* _jbuffer_h_ */

