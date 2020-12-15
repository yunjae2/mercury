#ifndef __CASYS_H__
#define __CASYS_H__

/*
 * Client/server tracer
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define CASYS_TRACE_CLIENT		1

#if CASYS_TRACE_CLIENT

#define CASYS_TRACE_CLIENT_REQ_POST()				\
{								\
	if (casys_mercury_trace_client)				\
		casys_trace_client_req_post();			\
}

#define CASYS_TRACE_CLIENT_REPLY_GET()				\
{								\
	if (casys_mercury_trace_client)				\
		casys_trace_client_reply_get();			\
}

#else

#define CASYS_TRACE_CLIENT_REQ_POST()		do {} while (0)
#define CASYS_TRACE_CLIENT_REPLY_GET()		do {} while (0)

#endif /* CASYS_TRACE_CLIENT */

#define D_ERROR(...)	fprintf(stderr, __VA_ARGS__)

typedef struct {
	uint64_t start;
	uint64_t req;
	uint64_t req_post;
	uint64_t reply;
	uint64_t reply_get;
	uint64_t end;
} casys_mercury_client_lat_t;

extern bool casys_mercury_trace_client;
extern casys_mercury_client_lat_t *casys_mercury_lat;

/*
 * Utilities
 */
#ifndef NSEC_PER_SEC
#define NSEC_PER_SEC  1000000000
#endif
#ifndef NSEC_PER_MSEC
#define NSEC_PER_MSEC 1000000
#endif
#ifndef NSEC_PER_USEC
#define NSEC_PER_USEC 1000
#endif

static inline uint64_t casys_get_ntime(void)
{
	struct timespec	tv;
	int rc;

	rc = clock_gettime(CLOCK_MONOTONIC, &tv);
	if (rc) {
		D_ERROR("%s failed!\n", __func__);
		return 0;
	}

	return (tv.tv_sec * NSEC_PER_SEC + tv.tv_nsec); /* nano seconds */
}

static inline uint64_t casys_get_time(void)
{
	struct timespec	tv;
	int rc;

	rc = clock_gettime(CLOCK_MONOTONIC, &tv);
	if (rc) {
		D_ERROR("%s failed!\n", __func__);
		return 0;
	}

	return tv.tv_sec; /* seconds */
}

/*
 * Tracer functions
 */
static inline void casys_trace_client_req_post(void)
{
	casys_mercury_lat->start = casys_get_ntime();
}

static inline void casys_trace_client_reply_get(void)
{
	casys_mercury_lat->req = casys_get_ntime();
}

#endif /* __CASYS_H__ */

