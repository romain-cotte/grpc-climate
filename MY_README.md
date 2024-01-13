## Prerequisites


### ncdump

```sh
sudo apt install netcdf-bin
```

### grpcurl

```sh

grpcurl_version=$(curl -sS https://api.github.com/repos/fullstorydev/grpcurl/tags | jq .[0].name | tr -d 'v"')

curl -sSL "https://github.com/fullstorydev/grpcurl/releases/download/v${grpcurl_version}/grpcurl_${grpcurl_version}_linux_x86_64.tar.gz" | sudo tar -xz -C /usr/local/bin
```



Grpc cmake example

 * git@github.com:faaxm/exmpl-cmake-grpc.git


# TODO

 * reorganize code into functions

