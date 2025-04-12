#include <iostream>
#include <cstring>
#ifdef _WIN32
#include <winsock2.h>
#include <io.h>
#define access _access
#else
#include <netinet/in.h>
#include <unistd.h>
#endif

constexpr int g_reuse = 1;
char g_buffer[512];
struct message; // forward

class udp_socket
{
public:
    udp_socket()
    {
        m_udp_socket = socket(AF_INET, SOCK_DGRAM, 0);
    }

    ~udp_socket()
    {
        close(this->m_udp_socket);
    }

    void check_validity()
    {
        if (this->m_udp_socket == -1)
        {
            std::cerr << "Socket creation failed: " << strerror(errno) << "..." << std::endl;
            return;
        }
    }

    void make_reusable()
    {
        // Since the tester restarts your program quite often, setting REUSE_PORT
        // ensures that we don't run into 'Address already in use' errors
        if (setsockopt(this->m_udp_socket, SOL_SOCKET, SO_REUSEPORT, &g_reuse, sizeof(g_reuse)) < 0)
        {
            std::cerr << "SO_REUSEPORT failed: " << strerror(errno) << std::endl;
            return;
        }
    }

    void bind_server()
    {
        sockaddr_in serv_addr = {
            .sin_family = AF_INET,
            .sin_port = htons(2053),
            .sin_addr = {htonl(INADDR_ANY)}, // sin_addr.s_addr = inet_addr("127.0.0.1"); // Target IP
        };

        if (bind(this->m_udp_socket, reinterpret_cast<struct sockaddr *>(&serv_addr), sizeof(serv_addr)) != 0)
        {
            std::cerr << "Bind failed: " << strerror(errno) << std::endl;
        }
    }

    bool receive_from(sockaddr_in& clientAddress)
    {
        socklen_t clientAddrLen = sizeof(clientAddress);
        int bytesRead = recvfrom(this->m_udp_socket, g_buffer, sizeof(g_buffer), 0, reinterpret_cast<struct sockaddr *>(&clientAddress), &clientAddrLen);
        
        if (bytesRead == -1)
        {
            perror("Error receiving data");
            return false;
        }

        g_buffer[bytesRead] = '\0';
        std::cout << "Received " << bytesRead << " bytes: " << g_buffer << std::endl;
        
        return true;
    }

    void send_to(message& dns_message, sockaddr_in& clientAddress)
    {
        if (sendto(this->m_udp_socket, reinterpret_cast<char *>(&dns_message.m_header), sizeof(dns_message.m_header), 0, reinterpret_cast<struct sockaddr *>(&clientAddress), sizeof(clientAddress)) == -1)
        {
            perror("Failed to send response");
        }
    }

    int m_udp_socket;
};