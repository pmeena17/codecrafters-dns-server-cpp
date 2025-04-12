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
    bool qr_indicator;
    // uint8_t opcode;
    // bool auth_ans;
    // bool truncation;
    // bool rec_desired;
    // bool rec_available;
    // uint8_t reserved;
    // uint8_t response_code;
    uint16_t question_cnt;
    uint16_t ans_rec_cnt;
    uint16_t auth_rec_cnt;
    uint16_t add_rec_cnt;
};

struct message
{
    dns_header m_header;
};