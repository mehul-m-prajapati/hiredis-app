## Prerequisites

- Redis server
```
$ sudo apt-get install redis-server
$ sudo systemctl start redis-server
```

- To test the Redis server
```
$ redis-cli monitor

$ redis-cli
127.0.0.1:6379> ping
PONG
127.0.0.1:6379> set test "It's working!"  # result ok
127.0.0.1:6379> get test  # result "It's working!"
127.0.0.1:6379> exit
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




