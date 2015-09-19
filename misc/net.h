/*
 * This file is part of the ssl-sim project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef UTILS_NET_H_
#define UTILS_NET_H_
#ifdef __cplusplus
extern "C" {
#endif
// -----------------------------------------------------------------------------

#include <stdbool.h>

struct Socket *new_socket(int port, const char *addr);
struct Socket *new_socket_iface(int port, const char *addr, const char *iface);
void delete_socket(struct Socket *socket);

bool socket_receiver_bind(struct Socket *socket);
bool socket_sender_bind(struct Socket *socket);

int socket_receive(struct Socket *socket, char *into_buffer, int buffer_size);
int socket_send(struct Socket *socket, const char *from_buffer, int send_size);

// -----------------------------------------------------------------------------
#ifdef __cplusplus
}
#endif
#endif
