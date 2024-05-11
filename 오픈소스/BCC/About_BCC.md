#### BCC란?

BCC (BPF Compiler Collection) BCC는 Linux 시스템의 성능 모니터링과 네트워크 분석을 위해 설계된 도구다. eBPF(Extended Berkeley Packet Filter)기반으로 하여, 네트워크 패킷 필터링, 시스템 호출 분석, 성능 모니터링 등 다양한 시스템 이벤트에 대한 Linux 커널의 기능이다.
![[bcc tracing tool.png]]


#### **설치방법**
##### **도커**
```
	docker run -it --rm \ --privileged \ -v /lib/modules:/lib/modules:ro \ -v /usr/src:/usr/src:ro \ -v /etc/localtime:/etc/localtime:ro \ --workdir /usr/share/bcc/tools \ zlim/bcc
```
##### **ubuntu (22.04) 에서 설치방법**
```
sudo apt-get update
sudo apt-get install bpfcc-tools linux-headers-$(uname -r)
```
빌드 종속성이 다르니 https://github.com/iovisor/bcc/blob/master/INSTALL.md#ubuntu---source 참고 (ubuntu에 맞는 버전 설치) <!!매우중요!!>⬇️⬇️⬇️
```
sudo apt install -y zip bison build-essential cmake flex git libedit-dev \
  libllvm14 llvm-14-dev libclang-14-dev python3 zlib1g-dev libelf-dev libfl-dev python3-setuptools \
  liblzma-dev libdebuginfod-dev arping netperf iperf
```

```

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

cd /usr/share/bcc/tools/ 
ls (목록들이 모두 툴)

