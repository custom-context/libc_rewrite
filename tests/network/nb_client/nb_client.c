#include "nb_client.h"
#include <network/nb_client/nb_client.h>
#include <errno.h>

DEFINE_RESULT_TYPE_STATIC_METHODS(int, int)

IMPLEMENT_TYPE_TESTS(nb_client) {
#if defined(WIN32)
    WSADATA wsa_data;
    ASSERT(!WSAStartup(MAKEWORD(2, 2), &wsa_data));
    ASSERT(LOBYTE(wsa_data.wVersion) == 2 && HIBYTE(wsa_data.wVersion) == 2);
#endif
    TEST_BLOCK("ping ya.ru || google.com") {
        struct domain_address_with_request {
            char const* const domain_address;
            char const* const request;
        };
        struct domain_address_with_request const domain_addresses_with_requests[] = {
            {
                .domain_address="ya.ru",
                .request=                
                    "OPTIONS / HTTP/1.1\r\n"
                    "Host: ya.ru\r\n"
                    "Content-Type: application/x-www-form-urlencoded\r\n"
                    "Connection: close\r\n"
                    "Accept: */*\r\n"
                    "\r\n"
            }, {
                .domain_address="www.google.com",
                .request=
                    "OPTIONS / HTTP/1.1\r\n"
                    "Host: www.google.com\r\n"
                    "Content-Type: application/x-www-form-urlencoded\r\n"
                    "Connection: close\r\n"
                    "Accept: */*\r\n"
                    "\r\n"
            }};
        SOCKET_DOMAIN_ENUM() const domains[] = {SOCKET_DOMAIN_ENUM_VALUE(IPv4)/*, SOCKET_DOMAIN_ENUM_VALUE(IPv6)*/};
        ADDRESS_INFO_CRITERIAS_TYPE() address_info_criterias;
        address_info_criterias.socket_type = SOCKET_TYPE_ENUM_VALUE(STREAM);
        address_info_criterias.socket_protocol.native_protocol = 0;
        address_info_criterias.native_extra_flags = 0;

        char response_buffer[100000];

        NB_CLIENT_TYPE() nb_client;
        NB_CLIENT_METHOD(construct_at)(&nb_client);
        
        usize domain_encounter;
        usize address_encounter;
        for (domain_encounter = 0u; domain_encounter < sizeof(domains) / sizeof(*domains); ++domain_encounter)
        for (address_encounter = 0u; address_encounter < sizeof(domain_addresses_with_requests) / sizeof(*domain_addresses_with_requests); ++address_encounter) {
            char const* const domain_address = domain_addresses_with_requests[address_encounter].domain_address;
            char const* const request = domain_addresses_with_requests[address_encounter].request;
            usize const request_size = RAW_STRING_FUNCTION(char, length)(request);
            SOCKET_DOMAIN_ENUM() const domain = domains[domain_encounter];
            address_info_criterias.socket_domain = domain;

            /*connect to server*/{            
                NB_CLIENT_METHOD(connect)(&nb_client,
                    domain_address,
                    "http",
                    &address_info_criterias
                );

                CHECK(NB_CLIENT_METHOD(is_connection_established)(&nb_client));

                struct RESULT_TYPE(int, int) connection_status = NB_CLIENT_METHOD(status)(&nb_client);
                CHECK(RESULT_METHOD(int, int, has_value)(&connection_status));
                CHECK(!*RESULT_METHOD(int, int, value)(&connection_status)); 
                RESULT_METHOD(int, int, destroy_at)(&connection_status);
            }

            /*send request*/{
                int sent_package_size;
                do {
                    sent_package_size = NB_CLIENT_METHOD(send)(&nb_client,
                        (void const*)request,
                        request_size
                    );
                } while (sent_package_size == -1 &&
#if defined(WIN32)
                    NAMESPACE_NETWORK(get_last_error)() == WSAEWOULDBLOCK
#else
                    NAMESPACE_NETWORK(get_last_error)() == EWOULDBLOCK
#endif
                );
                CHECK(sent_package_size > 0);
                CHECK(sent_package_size == (int)request_size);
            }
            /*receive response*/{
                int received_package_size;
                do {
                    received_package_size = NB_CLIENT_METHOD(receive)(&nb_client,
                        (void*)response_buffer,
                        sizeof(response_buffer)
                    );
                } while (received_package_size == -1 &&
#if defined(WIN32)
                    NAMESPACE_NETWORK(get_last_error)() == WSAEWOULDBLOCK
#else
                    NAMESPACE_NETWORK(get_last_error)() == EWOULDBLOCK
#endif
                );
                CHECK(received_package_size > 0);
                CHECK(received_package_size <= (int)sizeof(response_buffer));
            }
        }

        NB_CLIENT_METHOD(destroy_at)(&nb_client);
    }
#if defined(WIN32)
    WSACleanup();
#endif
}
