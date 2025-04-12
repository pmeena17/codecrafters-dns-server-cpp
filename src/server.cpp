
#include "ds_dns_message.h"
#include "ds_udp_socket.h"

int main()
{
    // Flush after every std::cout / std::cerr
    std::cout << std::unitbuf;
    std::cerr << std::unitbuf;

    // Disable output buffering
    setbuf(stdout, NULL);

    // udp_socket constructor
    udp_socket udp_socket_obj;
    udp_socket_obj.check_validity();
    udp_socket_obj.make_reusable();
    udp_socket_obj.bind_server();
    
    struct sockaddr_in clientAddress;
    message dns_message;

    while (true)
    {
        // Receive data
        if (!udp_socket_obj.receive_from(clientAddress))
            break;

        // Create dns message header
        dns_message.m_header.packet_id    = htons(1234);
        dns_message.m_header.qr_indicator = htons(0x8000);
        dns_message.m_header.question_cnt = htons(0);
        dns_message.m_header.ans_rec_cnt  = htons(0);
        dns_message.m_header.auth_rec_cnt = htons(0);
        dns_message.m_header.add_rec_cnt  = htons(0);

        // Send response
        udp_socket_obj.send_to(dns_message, clientAddress);
    }

    return 0;
}
