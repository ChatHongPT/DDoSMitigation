FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get upgrade -y && \
    apt-get install -y libxdp-dev libelf-dev zlib1g-dev cmake libbfd-dev clang llvm libcap-dev pkg-config gcc-multilib libbpf-dev iproute2 git make linux-headers-6.5.0-35-generic 

WORKDIR /
