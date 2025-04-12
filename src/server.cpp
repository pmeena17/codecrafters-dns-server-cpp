
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
    // Since the tester restarts your program quite often, setting REUSE_PORT
    // ensures that we don't run into 'Address already in use' errors
    udp_socket_obj.make_reusable();
    udp_socket_obj.bind_server();
    
    struct sockaddr_in clientAddress;
    message dns_message;

    while (true)
    {
        // Receive data
        if (!udp_socket_obj.receive_from(clientAddress))
            break;

        // Create dns message

        // Send response
        // udp_socket_obj.send_to(dns_message, clientAddress);
        if (sendto(udp_socket_obj.m_udp_socket, reinterpret_cast<char *>(&dns_message.m_header), sizeof(dns_message.m_header), 0, reinterpret_cast<struct sockaddr *>(&clientAddress), sizeof(clientAddress)) == -1)
        {
            perror("Failed to send response");
        }
    }

    close(udp_socket_obj.m_udp_socket);

    return 0;
}
