#include "icmpv4.h"
#include "ipv4.h"
#include "utils.h"

void icmpv4_incoming(struct netdev *netdev, struct eth_hdr *hdr) 
{
    struct iphdr *iphdr = (struct iphdr *) hdr->payload;
    struct icmp_v4 *icmp = (struct icmp_v4 *) iphdr->data;

    //TODO: Check csum

    switch (icmp->type) {
        case ICMP_V4_ECHO:
            icmpv4_reply(netdev, hdr);
            break;
        default:
            perror("ICMPv4 did not match supported types");
            return;
    }
}

void icmpv4_reply(struct netdev *netdev, struct eth_hdr *hdr)
{
    struct iphdr *iphdr = (struct iphdr *) hdr->payload;
    struct icmp_v4 *icmp = (struct icmp_v4 *) iphdr->data;
    uint16_t icmp_len = iphdr->len - (iphdr->ihl * 4);
    
    icmp->type = ICMP_V4_REPLY;
    icmp->csum = 0;
    icmp->csum = checksum(icmp, icmp_len, 0);
}
