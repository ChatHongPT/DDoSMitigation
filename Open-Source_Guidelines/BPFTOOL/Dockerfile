FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y libelf-dev zlib1g-dev cmake libbfd-dev clang llvm libcap-dev pkg-config libbpf-dev iproute2 git make linux-headers-6.5.0-35-generic

WORKDIR /

RUN git clone --recurse-submodules https://github.com/libbpf/bpftool.git

WORKDIR /bpftool/src

RUN make && make install

