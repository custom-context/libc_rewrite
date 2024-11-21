#include "server.h"

#include <network/server/server.h>
#include <network/client/client.h>

#include <utils/string/helpers.h>

DEFINE_RESULT_STATIC_METHODS(int, int)

#if defined(WIN32)
    #include <WS2tcpip.h>
#else
    #include <netdb.h>
#endif

IMPLEMENT_TYPE_TESTS(server) {
#if defined(WIN32)
    WSADATA wsa_data;
    ASSERT(!WSAStartup(MAKEWORD(2, 2), &wsa_data));
    ASSERT(LOBYTE(wsa_data.wVersion) == 2 && HIBYTE(wsa_data.wVersion) == 2);
#endif
    TEST_BLOCK("client <-> server interaction") {
        SOCKET_DOMAIN_ENUM() const domains[] = {SOCKET_DOMAIN_ENUM_VALUE(IPv4)/*, SOCKET_DOMAIN_ENUM_VALUE(IPv6)*/};

        SERVER_TYPE() server;
        SERVER_METHOD(construct_at)(&server);

        ADDRESS_INFO_CRITERIAS_TYPE() address_info_criterias;
        address_info_criterias.socket_domain = SOCKET_DOMAIN_ENUM_VALUE(UNSPECIFIED);
        address_info_criterias.socket_type = SOCKET_TYPE_ENUM_VALUE(STREAM);
        address_info_criterias.socket_protocol.native_protocol = 0;
        
        struct STRING_TYPE() client_request;
        STRING_METHOD(construct_from_c_string_at)(&client_request, "test client request");
        char client_response_buffer[100];

        struct STRING_TYPE() server_response;
        STRING_METHOD(construct_from_c_string_at)(&server_response, "test server response");
        char server_request_buffer[100];

        CLIENT_TYPE() client;
        CLIENT_METHOD(construct_at)(&client);
        
        usize domain_encounter;
        for (domain_encounter = 0u; domain_encounter < sizeof(domains) / sizeof(*domains); ++domain_encounter) {
            SOCKET_DOMAIN_ENUM() const domain = domains[domain_encounter];
            address_info_criterias.socket_domain = domain;

            /*bind server to port & listen for connections*/{
                address_info_criterias.native_extra_flags = AI_PASSIVE;
                SERVER_METHOD(bind)(&server,
                    NULL, /*or "127.0.0.1"*/
                    "8080",
                    &address_info_criterias
                );
                CHECK(SERVER_METHOD(is_binded)(&server));
                SERVER_METHOD(listen)(&server, 1);
            }

            /*connect to server*/{
                address_info_criterias.native_extra_flags = 0;
                CLIENT_METHOD(connect)(&client,
                    NULL, /*or "127.0.0.1"*/
                    "8080",
                    &address_info_criterias
                );
                CHECK(CLIENT_METHOD(is_connection_established)(&client));

                struct RESULT_TYPE(int, int) connection_status = CLIENT_METHOD(status)(&client);
                CHECK(RESULT_METHOD(int, int, has_value)(&connection_status));
                CHECK(!*RESULT_METHOD(int, int, value)(&connection_status)); 
                RESULT_METHOD(int, int, destroy_at)(&connection_status);
            }

            /*accept connection*/
            CONNECTION_TYPE() connection;
            {
                connection = SERVER_METHOD(accept)(&server);
                CHECK(CONNECTION_METHOD(is_established)(&connection));

                struct RESULT_TYPE(int, int) connection_status = CONNECTION_METHOD(status)(&connection);
                CHECK(RESULT_METHOD(int, int, has_value)(&connection_status));
                CHECK(!*RESULT_METHOD(int, int, value)(&connection_status)); 
                RESULT_METHOD(int, int, destroy_at)(&connection_status);
            }

            /*send request to server*/{
                int const sent_package_size = CLIENT_METHOD(send)(&client,
                    (void const*)STRING_METHOD(data)(&client_request),
                    STRING_METHOD(size)(&client_request)
                );
                CHECK(sent_package_size > 0);
                CHECK(sent_package_size == (int const)STRING_METHOD(size)(&client_request));
            }

            /*receive request from client*/{
                int const received_package_size = CONNECTION_METHOD(receive)(&connection,
                    (void*)server_request_buffer,
                    sizeof(server_request_buffer)
                );
                CHECK(received_package_size > 0);
                CHECK(received_package_size == (int const)STRING_METHOD(size)(&client_request));
                for (STRUCT_SUBTYPE(STRING_TYPE(), size_type) index = 0u; index < STRING_METHOD(size)(&client_request); ++index) {
                    CHECK(*TYPE_METHOD(STRING_TYPE(), at)(&client_request, index) == server_request_buffer[index]);
                }
            }

            /*send response to client*/{
                int const sent_package_size = CONNECTION_METHOD(send)(&connection,
                    (void const*)STRING_METHOD(data)(&server_response),
                    STRING_METHOD(size)(&server_response)
                );
                CHECK(sent_package_size > 0);
                CHECK(sent_package_size == (int const)STRING_METHOD(size)(&server_response));
            }

            /*receive response from server*/{
                int const received_package_size = CLIENT_METHOD(receive)(&client,
                    (void*)client_response_buffer,
                    sizeof(client_response_buffer)
                );
                CHECK(received_package_size > 0);
                CHECK(received_package_size == (int const)STRING_METHOD(size)(&server_response));
                for (STRUCT_SUBTYPE(STRING_TYPE(), size_type) index = 0u; index < STRING_METHOD(size)(&server_response); ++index) {
                    CHECK(*TYPE_METHOD(STRING_TYPE(), at)(&server_response, index) == client_response_buffer[index]);
                }
            }

            /*disconnect*/{
                CONNECTION_METHOD(destroy_at)(&connection);
            }
        }

        CLIENT_METHOD(destroy_at)(&client);
        STRING_METHOD(destroy_at)(&server_response);
        STRING_METHOD(destroy_at)(&client_request);
        SERVER_METHOD(destroy_at)(&server);
    }
#if defined(WIN32)
    WSACleanup();
#endif
}
