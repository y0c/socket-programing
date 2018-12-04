//syn_port_scan.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <netdb.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <time.h>

#define START_PORT 20
#define END_PORT 90   

#define LOCAL_IP "0.0.0.0"
#define LOCAL_PORT 9000

unsigned short cksum_in(unsigned short *, int);
void scan_syn_port(unsigned long target, int port);

struct pseudohdr {
    unsigned long s_addr;
    unsigned long d_addr;
    char zero;
    unsigned char protocol;
    unsigned short length;
};

int main(int argc, char *argv[])
{
    unsigned long target;
    int portNum;
    struct hostent *h;

    if(argc < 2) {
        printf("usage : portscan domain_name\n");
        exit(-1);
    }

    if((target = inet_addr(argv[1])) == -1) {
        h = gethostbyname(argv[1]);
        if(!h) {
            printf("gethostbyname error\n");
            return 4;
        }
        target = ((struct in_addr*)h->h_addr)->s_addr;
    }
   
    for(portNum = START_PORT; portNum <= END_PORT; portNum++) {
        printf("port %d scanning..", portNum);
        scan_syn_port(target, portNum);
    }
}

void scan_syn_port(unsigned long target, int port)
{
    int sd;

    int on = 1;
    int len;

    int tx_packet_size = sizeof(struct iphdr) + sizeof(struct tcphdr) + sizeof(struct pseudohdr);
    int rx_packet_size = sizeof(struct iphdr) + sizeof(struct tcphdr);
    char *rx_packet = (char *)malloc(rx_packet_size);
    char *tx_packet = (char *)malloc(tx_packet_size);

    struct tcphdr *tcph, *rx_tcph;
    struct iphdr *iph, *rx_iph;
    struct pseudohdr *pseudoh;

    struct in_addr s_addr, d_addr;
    struct sockaddr_in local, remote;
   
    struct servent *serv;

    iph = (struct iphdr *)(tx_packet);
    tcph = (struct tcphdr *)(tx_packet + sizeof(struct iphdr));
    pseudoh = (struct pseudohdr *)(tx_packet + sizeof(struct iphdr) + sizeof(struct tcphdr));

    if((sd = socket(PF_INET, SOCK_RAW, IPPROTO_TCP)) < 0) {
        printf("socket open error\n");
        exit(-1);
    }

    if(setsockopt(sd, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof(on)) < 0) {
        printf("set socket option error\n");
        exit(-2);
    }

    memset(tx_packet, 0, tx_packet_size);

    d_addr.s_addr = target;
    s_addr.s_addr = inet_addr(LOCAL_IP);
   
    pseudoh->s_addr = s_addr.s_addr;
    pseudoh->d_addr = d_addr.s_addr;
    pseudoh->protocol = IPPROTO_TCP;
    pseudoh->zero = 0;
    pseudoh->length = htons(sizeof(struct tcphdr));

    tcph->source = htons(LOCAL_PORT);
    tcph->dest = htons(port);
    tcph->seq = htons(random()%time(NULL));
    tcph->ack_seq = 0;
    tcph->doff = 5;
    tcph->res1 = 0;
    tcph->fin = 0;
    tcph->syn = 1;
    tcph->rst = 0;
    tcph->psh = 0;
    tcph->ack = 0;
    tcph->urg = 0;
    tcph->window = htons(1024);
    tcph->check = (unsigned short)cksum_in((unsigned short *)tcph, (sizeof(struct tcphdr) + sizeof(struct pseudohdr)));

    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = htons(tx_packet_size) - sizeof(struct pseudohdr);
    iph->id = 0;
    iph->frag_off =0;
        iph->ttl = IPDEFTTL;
        iph->protocol = IPPROTO_TCP;
        iph->saddr = s_addr.s_addr;
        iph->daddr = d_addr.s_addr;
        iph->check = (unsigned short)cksum_in((unsigned short *)iph,sizeof(struct iphdr));

        remote.sin_family = PF_INET;
        remote.sin_addr = d_addr;
        remote.sin_port =htons(port);
        remote.sin_port =0;  



       if(sendto(sd,tx_packet,(tx_packet_size - sizeof(struct pseudohdr)),0x0,(struct sockaddr*)&remote,sizeof(remote))<0)
        {
            printf("send error\n");
            exit(-3);
        }



        printf("[tx] %u->%u  ",ntohs(tcph->source),ntohs(tcph->dest));
        (tcph->urg ==1)?printf("U"):printf("-");
        (tcph->ack ==1)?printf("A"):printf("-");
        (tcph->psh ==1)?printf("P"):printf("-");
        (tcph->rst ==1)?printf("R"):printf("-");
        (tcph->syn ==1)?printf("S"):printf("-");
        (tcph->fin == 1)?printf("F"):printf("-");

        while(recvfrom(sd,rx_packet,rx_packet_size,0x0,(struct sockaddr*)&local,&len)>0)
        {


            rx_iph  = (struct iphdr *)(rx_packet);
            rx_tcph = (struct tcphdr*)(rx_packet + rx_iph->ihl *4);
      


            if(rx_iph->saddr != iph->daddr) continue;


            if((ntohs(tcph->source) == ntohs(rx_tcph->dest))&&(ntohs(tcph->dest) == ntohs(rx_tcph->source)))
            {
                    printf("[rx] %u->%u  ",ntohs(rx_tcph->source),ntohs(rx_tcph->dest));


                    (rx_tcph->urg ==1)?printf("U"):printf("-");
                    (rx_tcph->ack ==1)?printf("A"):printf("-");
                    (rx_tcph->psh ==1)?printf("P"):printf("-");
                    (rx_tcph->rst ==1)?printf("R"):printf("-");
                    (rx_tcph->syn ==1)?printf("S"):printf("-");
                    (rx_tcph->fin ==1)?printf("F"):printf("-");


                    if(rx_tcph->syn == 1 && rx_tcph->ack==1){
                        serv = getservbyport(htons(port),"tcp");
                        printf("port[%d] open/%s \n",ntohs(rx_tcph->source),serv->s_name);
                    }          
                    else if(rx_tcph->rst == 1){
                        printf(" *\n");
                    }
                    else{
                        printf("protocol error\n");
                        exit(-1);
                    }
                    break;
            }
        }
        close(sd);
}



unsigned short
cksum_in(unsigned short *addr, int len)
{

        unsigned long sum =0;
        unsigned short answer =0;
        unsigned short *w = addr;
        int nleft = len;

        while(nleft>1){
            sum+=*w++;
            if(sum & 0x80000000)
                sum=(sum&0xffff)+(sum>>16);
            nleft -=2;
           
    }
        if(nleft ==1){
            *(unsigned char*)(&answer)=*(unsigned char *)w;
            sum+= answer;
        }
        while(sum>>16)
            sum = (sum & 0xffff)+(sum>>16);
        return (sum==0xffff)?sum:~sum; 
}








