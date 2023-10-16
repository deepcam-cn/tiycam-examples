#ifndef _jbus_h_
#define _jbus_h_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _jbus_ctx			jbus_ctx_t;
typedef struct _jbus_ctx*			jbus_hdl_t;

jbus_hdl_t jbus_init(const char *name);
void jbus_cleanup(jbus_hdl_t hdl);
const char *jbus_get_name(jbus_hdl_t hdl);

typedef struct _jbus_publisher_ctx	jbus_pub_t;
typedef struct _jbus_subscriber_ctx	jbus_sub_t;
typedef struct _jbus_requester_ctx	jbus_req_t;
typedef struct _jbus_replier_ctx	jbus_rep_t;

#define JBUS_INTERFACE_BROADCAST		"broadcast"
typedef void (*jbus_subscriber_cb)(void*, const char*, const void*, int);
typedef void (*jbus_replier_cb)(void*, const char*, const void*, int);

jbus_pub_t *jbus_create_publisher(jbus_hdl_t hdl, const char *iface);
void jbus_destroy_publisher(jbus_hdl_t hdl, jbus_pub_t *pub);
int jbus_publish(jbus_pub_t *pub, const char *name, const void *content, int length);

jbus_sub_t *jbus_create_subscriber(jbus_hdl_t hdl, const char *iface);
void jbus_destroy_subscriber(jbus_hdl_t hdl, jbus_sub_t *sub);
int jbus_sub_set_callback(jbus_sub_t *sub, jbus_subscriber_cb cb, void *arg);

jbus_req_t *jbus_create_requester(jbus_hdl_t hdl, const char *dest, const char *iface);
void jbus_destroy_requester(jbus_hdl_t hdl, jbus_req_t *req);
int jbus_req_set_timeout(jbus_req_t *req, int timeout);
int jbus_request(jbus_req_t *req, const char *name, const void *arg, int length);
int jbus_req_get_reply(jbus_req_t *req, void *buffer, int length);
int jbus_req_clean_reply(jbus_req_t *req);

jbus_rep_t *jbus_create_replier(jbus_hdl_t hdl, const char *iface);
void jbus_destroy_replier(jbus_hdl_t hdl, jbus_rep_t *rep);
int jbus_rep_set_callback(jbus_rep_t *rep, jbus_replier_cb cb, void *arg);
int jbus_reply(jbus_rep_t *rep, const void *arg, int length);

#ifdef __cplusplus
}
#endif

#endif /* _jbus_h_ */

