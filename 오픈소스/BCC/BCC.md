1. BCC에 대해서
	BCC (BPF Compiler Collection) BCC는 eBPF(extended Berkeley Packet Filter) 프로그램을 쉽게 생성할 수 있는 라이브러리입니다. eBPF 프로그램의 주요 유틸리티는 오버헤드 또는 보안 문제가 발생하지 않고 운영체제 성능 및 네트워크 성능을 분석하는 것이다.

2. 설치방법

##### **도커**
```
	docker run -it --rm \ --privileged \ -v /lib/modules:/lib/modules:ro \ -v /usr/src:/usr/src:ro \ -v /etc/localtime:/etc/localtime:ro \ --workdir /usr/share/bcc/tools \ zlim/bcc
```
##### **ubuntu (22.04) 에서 설치방법**
```
sudo apt-get update
sudo apt-get install bpfcc-tools linux-headers-$(uname -r)
```
# For Jammy (22.04) - 빌드 종속성이 다르니 https://github.com/iovisor/bcc/blob/master/INSTALL.md#ubuntu---source 참고 (ubuntu에 맞는 버전 설치)
```
sudo apt install -y zip bison build-essential cmake flex git libedit-dev \
  libllvm14 llvm-14-dev libclang-14-dev python3 zlib1g-dev libelf-dev libfl-dev python3-setuptools \
  liblzma-dev libdebuginfod-dev arping netperf iperf
  
 git clone https://github.com/iovisor/bcc.git
mkdir bcc/build; cd bcc/build
cmake ..
make (30분소요)
sudo make install
cmake -DPYTHON_CMD=python3 .. # build python3 binding
pushd src/python/
make
sudo make install
popd
```
