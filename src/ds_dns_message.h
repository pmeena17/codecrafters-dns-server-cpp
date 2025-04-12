#ifdef _WIN32
#include <winsock2.h>
#include <io.h>
#define access _access
#else
#include <netinet/in.h>
#include <unistd.h>
#endif

class dns_header
{
public:
    dns_header()
    {
        packet_id     = htons(1234);
        qr_indicator  = htons(1);
        opcode        = htons(0);
        auth_ans      = htons(0);
        truncation    = htons(0);
        rec_desired   = htons(0);
        rec_available = htons(0);
        reserved      = htons(0);
        response_code = htons(0);
        question_cnt  = htons(0);
        ans_rec_cnt   = htons(0);
        auth_rec_cnt  = htons(0);
        add_rec_cnt   = htons(0);
    }

    uint16_t packet_id;
    bool qr_indicator;
    uint8_t opcode;
    bool auth_ans;
    bool truncation;
    bool rec_desired;
    bool rec_available;
    uint8_t reserved;
    uint8_t response_code;
    uint16_t question_cnt;
    uint16_t ans_rec_cnt;
    uint16_t auth_rec_cnt;
    uint16_t add_rec_cnt;
};

struct message
{
    dns_header m_header;
};