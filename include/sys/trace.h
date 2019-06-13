/*
 * CDDL HEADER START
 *
 * The contents of this file are subject to the terms of the
 * Common Development and Distribution License (the "License").
 * You may not use this file except in compliance with the License.
 *
 * You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
 * or http://www.opensolaris.org/os/licensing.
 * See the License for the specific language governing permissions
 * and limitations under the License.
 *
 * When distributing Covered Code, include this CDDL HEADER in each
 * file and include the License file at usr/src/OPENSOLARIS.LICENSE.
 * If applicable, add the following below this CDDL HEADER, with the
 * fields enclosed by brackets "[]" replaced with your own identifying
 * information: Portions Copyright [yyyy] [name of copyright owner]
 *
 * CDDL HEADER END
 */

#if defined(_KERNEL)

/*
 * Calls to DTRACE_PROBE are mapped to standard Linux kernel trace points
 * when they are available.  Otherwise, stub functions are generated which
 * can be traced using kprobes.
 */
#if defined(HAVE_DECLARE_EVENT_CLASS)

#undef TRACE_SYSTEM
#define	TRACE_SYSTEM zfs

#if !defined(_TRACE_ZFS_H) || defined(TRACE_HEADER_MULTI_READ)
#define	_TRACE_ZFS_H

#include <linux/tracepoint.h>
#include <sys/types.h>

/*
 * The sys/trace_dbgmsg.h header defines tracepoint events for
 * dprintf(), dbgmsg(), and SET_ERROR().
 */
#define	_SYS_TRACE_DBGMSG_INDIRECT
#include <sys/trace_dbgmsg.h>
#undef _SYS_TRACE_DBGMSG_INDIRECT

#define	DTRACE_PROBE(name) \
	trace_zfs_##name((void))

#define	DTRACE_PROBE1(name, t1, arg1) \
	trace_zfs_##name((arg1))

#define	DTRACE_PROBE2(name, t1, arg1, t2, arg2) \
	trace_zfs_##name((arg1), (arg2))

#define	DTRACE_PROBE3(name, t1, arg1, t2, arg2, t3, arg3) \
	trace_zfs_##name((arg1), (arg2), (arg3))

#define	DTRACE_PROBE4(name, t1, arg1, t2, arg2, t3, arg3, t4, arg4) \
	trace_zfs_##name((arg1), (arg2), (arg3), (arg4))

#endif /* _TRACE_ZFS_H */

#undef TRACE_INCLUDE_PATH
#undef TRACE_INCLUDE_FILE
#define	TRACE_INCLUDE_PATH sys
#define	TRACE_INCLUDE_FILE trace
#include <trace/define_trace.h>

#else /* HAVE_DECLARE_EVENT_CLASS */

#define	DTRACE_PROBE(name) \
	trace_zfs_##name((void))

#define	DTRACE_PROBE1(name, t1, arg1) \
	trace_zfs_##name((uintptr_t)(arg1))

#define	DTRACE_PROBE2(name, t1, arg1, t2, arg2) \
	trace_zfs_##name((uintptr_t)(arg1), (uintptr_t)(arg2))

#define	DTRACE_PROBE3(name, t1, arg1, t2, arg2, t3, arg3) \
	trace_zfs_##name((uintptr_t)(arg1), (uintptr_t)(arg2), \
	(uintptr_t)(arg3))

#define	DTRACE_PROBE4(name, t1, arg1, t2, arg2, t3, arg3, t4, arg4) \
	trace_zfs_##name((uintptr_t)(arg1), (uintptr_t)(arg2), \
	(uintptr_t)(arg3), (uintptr_t)(arg4))

#if defined(CREATE_TRACE_POINTS)

#define	FUNC_DTRACE_PROBE(name)					\
noinline void trace_zfs_##name(void) { }			\
EXPORT_SYMBOL(trace_zfs_##name)

#define	FUNC_DTRACE_PROBE1(name)				\
noinline void trace_zfs_##name(uintptr_t arg1) { }		\
EXPORT_SYMBOL(trace_zfs_##name)

#define	FUNC_DTRACE_PROBE2(name)				\
noinline void trace_zfs_##name(uintptr_t arg1,			\
    uintptr_t arg2) { }						\
EXPORT_SYMBOL(trace_zfs_##name)

#define	FUNC_DTRACE_PROBE3(name)				\
noinline void trace_zfs_##name(uintptr_t arg1,			\
    uintptr_t arg2, uintptr_t arg3) { }				\
EXPORT_SYMBOL(trace_zfs_##name)

#define	FUNC_DTRACE_PROBE4(name)				\
noinline void trace_zfs_##name(uintptr_t arg1,			\
    uintptr_t arg2, uintptr_t arg3, uintptr_t arg4) { }		\
EXPORT_SYMBOL(trace_zfs_##name)

#undef	DEFINE_DTRACE_PROBE
#define	DEFINE_DTRACE_PROBE(name)	FUNC_DTRACE_PROBE(name)

#undef	DEFINE_DTRACE_PROBE1
#define	DEFINE_DTRACE_PROBE1(name)	FUNC_DTRACE_PROBE1(name)

#undef	DEFINE_DTRACE_PROBE2
#define	DEFINE_DTRACE_PROBE2(name)	FUNC_DTRACE_PROBE2(name)

#undef	DEFINE_DTRACE_PROBE3
#define	DEFINE_DTRACE_PROBE3(name)	FUNC_DTRACE_PROBE3(name)

#undef	DEFINE_DTRACE_PROBE4
#define	DEFINE_DTRACE_PROBE4(name)	FUNC_DTRACE_PROBE4(name)

#else

#define	PROTO_DTRACE_PROBE(name)				\
	noinline void trace_zfs_##name(void)
#define	PROTO_DTRACE_PROBE1(name)				\
	noinline void trace_zfs_##name(uintptr_t)
#define	PROTO_DTRACE_PROBE2(name)				\
	noinline void trace_zfs_##name(uintptr_t, uintptr_t)
#define	PROTO_DTRACE_PROBE3(name)				\
	noinline void trace_zfs_##name(uintptr_t, uintptr_t,	\
	uintptr_t)
#define	PROTO_DTRACE_PROBE4(name)				\
	noinline void trace_zfs_##name(uintptr_t, uintptr_t,	\
	uintptr_t, uintptr_t)

#define	DEFINE_DTRACE_PROBE(name)	PROTO_DTRACE_PROBE(name)
#define	DEFINE_DTRACE_PROBE1(name)	PROTO_DTRACE_PROBE1(name)
#define	DEFINE_DTRACE_PROBE2(name)	PROTO_DTRACE_PROBE2(name)
#define	DEFINE_DTRACE_PROBE3(name)	PROTO_DTRACE_PROBE3(name)
#define	DEFINE_DTRACE_PROBE4(name)	PROTO_DTRACE_PROBE4(name)
#endif /* CREATE_TRACE_POINTS */

#endif /* HAVE_DECLARE_EVENT_CLASS */
#endif /* _KERNEL */
