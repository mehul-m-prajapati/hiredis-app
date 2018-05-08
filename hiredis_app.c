#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include </usr/include/hiredis/hiredis.h>

#define HOST_ADDR		"127.0.0.1"
#define HOST_PORT_NO		6379


int main(int argc, char **argv) 
{
    unsigned int j;
    redisContext *c;
    redisReply *reply;
    const char *hostname = (argc > 1) ? argv[1] : HOST_ADDR;
    int port = (argc > 2) ? atoi(argv[2]) : HOST_PORT_NO;

    struct timeval timeout = { 1, 500000 }; // 1.5 seconds

    /* Connect to Server */
    c = redisConnectWithTimeout(hostname, port, timeout);
    
    if (c == NULL || c->err) 
    {
        if (c) 
	{
            printf("Connection error: %s\n", c->errstr);
            redisFree(c);
        } 
	else 
	{
            printf("Connection error: can't allocate redis context\n");
        }
        exit(1);
    }

    /* PING server */
    reply = redisCommand(c, "PING");
    printf("PING: %s\n", reply->str);
    freeReplyObject(reply);

    /* Set a key */
    reply = redisCommand(c, "SET %s %s", "project", "syslog-ng");
    printf("SET project syslog-ng: %s\n", reply->str);
    freeReplyObject(reply);

    /* Try a GET */
    reply = redisCommand(c,"GET project");
    printf("GET project: %s\n", reply->str);
    freeReplyObject(reply);

    /* Create a list of fruits */
    reply = redisCommand(c,"DEL fruits");
    freeReplyObject(reply);
    
    reply = redisCommand(c,"LPUSH fruits banana");
    freeReplyObject(reply);
    
    reply = redisCommand(c,"LPUSH fruits apple");
    freeReplyObject(reply);
    
    reply = redisCommand(c,"LPUSH fruits kiwi");
    freeReplyObject(reply);

    reply = redisCommand(c,"LPUSH fruits mango");
    freeReplyObject(reply);

    printf("\nList of fruits\n"); 

   /* Let's check what we have inside the list */
    reply = redisCommand(c,"LRANGE fruits 0 -1");
    
    if (reply->type == REDIS_REPLY_ARRAY) 
    {
        for (j = 0; j < reply->elements; j++) 
	{
            printf("%u) %s\n", j, reply->element[j]->str);
        }
    }
    freeReplyObject(reply);

    /* Disconnects and frees the context */
    redisFree(c);

    return 0;
}
