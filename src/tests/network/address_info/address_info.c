#include "address_info.h"

#include <network/address_info/address_info.h>

IMPLEMENT_TYPE_TESTS(address_info) {
#if defined(WIN32)
    WSADATA wsa_data;
    ASSERT(!WSAStartup(MAKEWORD(2, 2), &wsa_data));
    ASSERT(LOBYTE(wsa_data.wVersion) == 2 && HIBYTE(wsa_data.wVersion) == 2);
#endif
    TEST_BLOCK("addrinfo ya.ru || google.com") {
        char const* const domain_addresses[2] = {"ya.ru", "google.com"};
        SOCKET_DOMAIN_ENUM() const domains[2] = {SOCKET_DOMAIN_ENUM_VALUE(IPv4), SOCKET_DOMAIN_ENUM_VALUE(IPv6)};
        ADDRESS_INFO_CRITERIAS_TYPE() address_info_criterias;
        address_info_criterias.socket_type = SOCKET_TYPE_ENUM_VALUE(DATAGRAM);
        address_info_criterias.socket_protocol.native_protocol = 0;
        address_info_criterias.native_extra_flags = 0;

        usize domain_encounter;
        usize address_encounter;
        usize ip_address_count = 0u;
        for (domain_encounter = 0; domain_encounter < sizeof(domains) / sizeof(*domains); ++domain_encounter)
        for (address_encounter = 0; address_encounter < sizeof(domain_addresses) / sizeof(*domain_addresses); ++address_encounter) {
            char const* const domain_address = domain_addresses[address_encounter];
            SOCKET_DOMAIN_ENUM() const domain = domains[domain_encounter];
            address_info_criterias.socket_domain = domain;
            
            ADDRESS_INFO_TYPE() address_info;
            ADDRESS_INFO_METHOD(construct_with_fetch_at)(&address_info,
                domain_address,
                NULL,
                &address_info_criterias
            );

            ADDRESS_INFO_ITERATOR_TYPE()
                iterator = ADDRESS_INFO_METHOD(begin)(&address_info),
                end_iterator = ADDRESS_INFO_METHOD(end)(&address_info);

            for (; ADDRESS_INFO_ITERATOR_METHOD(compare)(&iterator, &end_iterator); ADDRESS_INFO_ITERATOR_METHOD(next)(&iterator)) {
                ADDRESS_INFO_TYPE() const* const current_address_info = ADDRESS_INFO_ITERATOR_METHOD(value)(&iterator);

                SOCKET_ADDRESS_INFO_DESCRIPTOR_TYPE() socket_address_info_descriptor;
                SOCKET_ADDRESS_INFO_DESCRIPTOR_METHOD(construct_at)(&socket_address_info_descriptor, current_address_info);

                STRING_TYPE() ip_address = SOCKET_ADDRESS_INFO_DESCRIPTOR_METHOD(get_ip_address)(&socket_address_info_descriptor);

                ++ip_address_count;

                STRING_METHOD(destroy_at)(&ip_address);
                SOCKET_ADDRESS_INFO_DESCRIPTOR_METHOD(destroy_at)(&socket_address_info_descriptor);
            }
            ADDRESS_INFO_METHOD(destroy_at)(&address_info);
        }
        CHECK(ip_address_count);
    }
#if defined(WIN32)
    WSACleanup();
#endif
}
