# Test


```sh
grpcurl -d '{"name": "aaa"}' \
-proto myproto/addressbook.proto \
-plaintext localhost:50051 \
expcmake.AddressBook/GetAddress
```


# Test locally

```sh
docker run --rm -d -p 8081:50051 grpc-cpp
```
Then:

```sh
grpcurl -d '{"name": "aaa"}' \
-proto myproto/addressbook.proto \
-plaintext localhost:8081 \
expcmake.AddressBook/GetAddress
```


# Deploy to fly


```sh
docker build . --tag nginx-test
docker run -it --rm -d -p 8080:80 nginx-test
```

Then:

```sh
cd ~/perso/fly/grpc-cpp/proto && grpcurl -d '{"name": "aaa"}' \
-proto myproto/addressbook.proto \
nginx-example.fly.dev:443 \
expcmake.AddressBook/GetAddress
```
grpcurl -proto hello.proto grpc-go.fly.dev:443 MainService/Hello
nginx-example




# TODO

 * reorganize code into functions
