FROM ubuntu:22.04

RUN apt update
RUN apt install -y \
  autoconf \
  build-essential \
  cmake \
  curl \
  g++ \
  git \
  libnetcdf-dev \
  libtool \
  pkg-config \
  vim

WORKDIR /home

RUN git clone -b v1.51.3 https://github.com/grpc/grpc.git

WORKDIR /home/grpc
RUN git submodule update --init
RUN mkdir build
WORKDIR /home/grpc/build

RUN cmake .. \
  -DBUILD_SHARED_LIBS=OFF \
  -DCMAKE_BUILD_TYPE=Release \
  -DgRPC_ABSL_PROVIDER=module \
  -DgRPC_BUILD_TESTS=OFF \
  -DgRPC_CARES_PROVIDER=module \
  -DgRPC_INSTALL=ON \
  -DgRPC_PROTOBUF_PACKAGE_TYPE=CONFIG \
  -DgRPC_RE2_PROVIDER=module \
  -DgRPC_SSL_PROVIDER=module \
  -DgRPC_ZLIB_PROVIDER=module

RUN make
RUN make install

RUN mkdir /home/grpc-cpp
WORKDIR /home/grpc-cpp

COPY CMakeLists.txt .
COPY proto proto
COPY server server
COPY cmake cmake

RUN mkdir build
WORKDIR /home/grpc-cpp/build
RUN cmake ..
RUN make

WORKDIR /home/grpc-cpp

ENTRYPOINT ["./build/server/server"]
