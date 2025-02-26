/**
 * ENOTCONN - Transport endpoint is not connected
 *
 * The ENOTCONN error code stands for "Transport endpoint is not connected."
 * This error typically occurs in the context of socket operations where an
 * operation is attempted on a socket that is not connected.
 *
 * - Was never connected (e.g., TCP sockets before connect() succeeds).
 * - Lost its connection (e.g., the peer closed the connection).
 * - Is being used inappropriately for its type (e.g., using send() on an
 *   unconnected UDP socket).
 */
