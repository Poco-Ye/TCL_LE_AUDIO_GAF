/*
 * Copyright (c) 2020 Friedt Professional Engineering Services, Inc
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifdef CONFIG_ARCH_POSIX
#include <fcntl.h>
#else
#include <zephyr/posix/fcntl.h>
#endif

#include <zephyr/logging/log.h>
LOG_MODULE_DECLARE(net_test, CONFIG_NET_SOCKETS_LOG_LEVEL);

#include <stdio.h>
#include <string.h>
#include <zephyr/net/socket.h>
#include <zephyr/sys/util.h>
#include <zephyr/posix/unistd.h>

#include <zephyr/ztest_assert.h>

#undef read
#define read(fd, buf, len) zsock_recv(fd, buf, len, 0)

#undef write
#define write(fd, buf, len) zsock_send(fd, buf, len, 0)

ZTEST_USER(net_socketpair, test_socketpair_expected_failures)
{
	int res;
	int sv[2] = {-1, -1};

	/* Use invalid values in fields starting from left to right */

	res = socketpair(AF_INET, SOCK_STREAM, 0, sv);
	if (res != -1) {
		close(sv[0]);
		close(sv[1]);
	}
	zassert_equal(res, -1, "socketpair with fail with bad address family");
	zassert_equal(errno, EAFNOSUPPORT,
				  "errno should be EAFNOSUPPORT with bad address family");

	res = socketpair(AF_UNIX, 42, 0, sv);
	if (res != -1) {
		close(sv[0]);
		close(sv[1]);
	}
	zassert_equal(res, -1,
				  "socketpair should fail with unsupported socket type");
	zassert_equal(errno, EPROTOTYPE,
				  "errno should be EPROTOTYPE with bad socket type");

	res = socketpair(AF_UNIX, SOCK_STREAM, IPPROTO_TLS_1_0, sv);
	if (res != -1) {
		close(sv[0]);
		close(sv[1]);
	}
	zassert_equal(res, -1,
				  "socketpair should fail with unsupported protocol");
	zassert_equal(errno, EPROTONOSUPPORT,
				  "errno should be EPROTONOSUPPORT with bad protocol");

	/* This is not a POSIX requirement, but should be safe */
	res = socketpair(AF_UNIX, SOCK_STREAM, 0, NULL);
	if (res != -1) {
		close(sv[0]);
		close(sv[1]);
	}
	zassert_equal(res, -1,
				  "socketpair should fail with invalid socket vector");
	zassert_equal(errno, EFAULT,
				  "errno should be EFAULT with bad socket vector");
}
