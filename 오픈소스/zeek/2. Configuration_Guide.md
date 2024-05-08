# Configuration_Guide

아래의 순서로 진행하면 된다.

1. docker pull zeek/zeek:latest

2. docker run -it zeek/zeek /bin/bash

3. apt-get update

4. apt-get install -y --no-install-recommends g++ cmake make libpcap-dev

5. apt-get install cmake make gcc g++ flex libfl-dev bison libpcap-dev libssl-dev python3 python3-dev swig zlib1g-dev

6. apt-get install python3-git python3-semantic-version

7. git clone --recurse-submodules https://github.com/zeek/zeek

8. cd zeek

9. ./configure

10. make

11. make install
