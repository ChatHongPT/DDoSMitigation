# XDP-Tutorial 가이드라인

<!-- # [**XDP-Tutorial**](https://github.com/xdp-project/xdp-tutorial)
   - **설명**: eXpress Data Path의 기본적인 이해를 위한 튜토리얼 및 예제 모음.
   - **특징**: XDP의 동작 및 개발 방법에 대한 이해 촉진.
   - **장단점**:
     - **장점**: XDP 프로그래밍에 대한 학습에 유용한 자원 제공.
     - **단점**: 고급 사용자에게는 부족한 수준일 수 있음.
   - **설치 가이드**: 프로젝트의 GitHub 페이지 또는 문서를 따라 설치. -->

## 실습 환경 구성[\(Setup dependencies\)](https://github.com/xdp-project/xdp-tutorial/blob/master/setup_dependencies.org)
Docker 환경(Ubuntu 22.04, 24.02)에서 실습 환경을 구성하려 했으나, make 명령이 정상적으로 실행되지 않았음.
따라서 vmware로 만든 가상머신(Ubuntu 24.04)에서 실습 환경을 구성함.

1. 종속성 설치
```
sudo apt install -y git
sudo apt install -y clang llvm libelf-dev libpcap-dev build-essential libc6-dev-i386
sudo apt install -y linux-tools-$(uname -r)
sudo apt install -y linux-headers-$(uname -r)
sudo apt install -y linux-tools-common linux-tools-generic
sudo apt install -y tcpdump
```

2. git clone
```
git clone --recurse-submodules https://github.com/xdp-project/xdp-tutorial.git
```

## 실습
AF_XDP를 사용하기 위한 목적이므로, xdp-tutorial의 basic01, 2, 3과 advanced03-AF_XDP만 이용한다.

## basic01 xdp pass
이 단계의 목적은 xdp를 로드하는 방법으로 3가지가 있다.

### iproute2 ip
  - 로드
  `sudo ip link set dev lo xdpgeneric obj xdp_pass_kern.o sec xdp`

  - 확인
  `sudo ip link show`

  - 제거
  `sudo ip link set dev lo xdpgeneric off`

### xdp-loader
  - 로드
  `sudo xdp-loader load -m skb lo xdp_pass_kern.o`

  - 확인
  `sudo xdp-loader status lo`

### xdp_pass_user
  - 로드
  `sudo ./xdp_pass_user --dev lo`

  - 확인
  ```
  ip link list dev lo
  bpftool net list dev lo
  xdp-loader status lo
  ```

  - 제거
  \[ID\]만 제거
  `sudo ./xdp_pass_user --dev lo -U \[ID\]]`

  전부 제거
  `sudo ./xdp_pass_user --dev lo --unload-all`

## basic02 prog by name
## basic03 map counter
## advanced03 AF_XDP