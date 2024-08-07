#include "cspd.h"

#include <csp/drivers/can_socketcan.h>

void *handle_csp_packet(void *param)
{
	csp_socket_t sock = {0};
	csp_bind(&sock, CSP_ANY);
	csp_listen(&sock, 10);

	while (1) {
		csp_conn_t *conn;
		if ((conn = csp_accept(&sock, 10000)) == NULL) {
			continue;
		}

		csp_packet_t *packet;
		while ((packet = csp_read(conn, 50)) != NULL) {
			switch (csp_conn_dport(conn)) {
			case PORT_A:
				csp_print("recived: %s\n", (char *)packet->data);
				csp_buffer_free(packet);
				break;

			default:
				csp_service_handler(packet);
				break;
			}
		}
		csp_close(conn);
	}
}
