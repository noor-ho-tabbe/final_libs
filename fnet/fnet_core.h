#ifndef _NET_UTIL_H_
#define    _NET_UTIL_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <netinet/in.h>

#define SOCKET_IDLE     -2
#define SOCKET_ERROR    -1
#define SOCKET_CLOSE    0

// host struct
typedef struct {
    int    alias_count;
    int    ip_count;
    char*  official_name;
    char** alias_names;
    char** ips;
} host_info_t;

// use it avoid gcc throw error 'break strict-aliasing rules'
typedef union {
    struct sockaddr_storage storage;
    struct sockaddr_in      in;
    struct sockaddr_in6     in6;
    struct sockaddr         sa;
} sockaddr_u_t;

unsigned int fnet_get_lowdata(unsigned int data);
unsigned int fnet_get_highdata(unsigned int data);

void    fnet_set_keepalive(int fd, int idle_time, int interval, int count);
void    fnet_set_nonblocking(int fd);
int     fnet_set_nodelay(int fd);
void    fnet_set_recv_buffsize(int fd, int size);
void    fnet_set_send_buffsize(int fd, int size);
void    fnet_set_recv_timeout(int fd, int timeout);
void    fnet_set_send_timeout(int fd, int timeout);
void    fnet_set_linger(int fd);
void    fnet_set_reuse_addr(int fd);
void    fnet_set_reuse_port(int fd);

int     fnet_create_listen(const char* ip, int port, int max_link, int isblock);
int     fnet_accept(int listen_fd);
int     fnet_send(int fd, const void* data, int len);
int     fnet_recv(int fd, char* data, int len);
int     fnet_conn(const char* ip, int port, int isblock);
int     fnet_conn_async(const char* ip, int port, int* outfd);
int     fnet_send_safe(int fd, const void* data, int len);

char*   fnet_get_localip(int fd);
char*   fnet_get_peerip(int fd);

// dns , after use must call net_free_host
int     fnet_get_host(const char* host_name, host_info_t* hinfo);
void    fnet_free_host(host_info_t* hinfo);

#ifdef __cplusplus
}
#endif

#endif
