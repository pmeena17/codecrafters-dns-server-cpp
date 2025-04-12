#ifdef _WIN32
#include <winsock2.h>
#include <io.h>
#define access _access
#else
#include <netinet/in.h>
#include <unistd.h>
#endif

struct dns_header
{
    uint16_t packet_id;
    uint16_t flags; // QR, Opcode, AA, TC, RD, RA, Z, RCODE packed together
    uint16_t question_cnt;
    uint16_t ans_rec_cnt;
    uint16_t auth_rec_cnt;
    uint16_t add_rec_cnt;
};

struct message
{
    dns_header m_header;
};