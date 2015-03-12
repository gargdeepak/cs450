
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void exiterror(const char* s){
    printf("%s", s);
    exit(1);
}

int main(int argc, char* argv[]){
    if(argc < 1){
        exiterror("Please pass the hostname");
    }

    struct addrinfo hints;
    struct addrinfo* result;
    struct addrinfo* tempnode;
    memset(&hints, 0, sizeof hints);

    int code = getaddrinfo(argv[1], NULL, &hints, &result);
    if(code !=0){
        fprintf(stderr, "getaddrinfo error:  %s\n", gai_strerror(code));
        exit(EXIT_FAILURE);
    }

    for(tempnode = result; tempnode != NULL; tempnode = tempnode->ai_next){
        if(tempnode->ai_family == AF_INET){
            char ip4[INET_ADDRSTRLEN];

            struct sockaddr_in *addr4 = (struct sockaddr_in* )tempnode->ai_addr;
            printf("IP4 address: %s  Port: %d\n", inet_ntop(AF_INET, &addr4->sin_addr, ip4, INET_ADDRSTRLEN), addr4->sin_port);
        }else{
            char ip6[INET6_ADDRSTRLEN];
            struct sockaddr_in6* addr6 = (struct sockaddr_in6*)tempnode->ai_addr;
            printf("IP6 address: %s  Port: %d\n", inet_ntop(AF_INET6, &addr6->sin6_addr, ip6, INET6_ADDRSTRLEN), addr6->sin6_port);
        }
    }
    freeaddrinfo(result);
}
