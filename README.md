## Prerequisites

- Redis server
```
$ sudo apt-get install redis-server
$ sudo systemctl status redis-server
```

- To test the Redis server
```
$ redis-cli monitor

$ redis-cli
127.0.0.1:6379> ping
PONG
```

- hiredis library
```
$ sudo apt-get install libhiredis0.13
$ sudo apt-get install libhiredis-dev 
```

## Build and Execute
```
$ make all
$ ./hiredis_app
```




