***
# 🚀 eBPF/XDP 를 활용한 DDoS 방어 최종 솔루션
#방어_솔루션 #프로세스_자동화

##### 📝프로그램 구성

> - Kernel Space / User Space 프로그램으로 구성(prog_kern.c prog_user.c)
> 1. Kernel Space 프로그램
> 	DDoS 방어 종합 솔루션 코드
> 	XDP_DROP or XDP_REDIRECT(XDP 소켓으로 리다이렉팅)
> 2. User Space 프로그램
> 	Kernel Space 프로그램 로드, 등록
> 	ARP table 리셋
> 	패킷 처리(자동화)
> 	XDP Socket, U Memory 구성
###### main (일부)
![code](./Main_flow.jpg)
##### 🛠️프로그램 실행 
- 참고
	1. VM || Host Ubuntu 버전 22.04 LTS 이상 권장
	2. Docker Container 구성 -> 공격 컨테이너, 방어용 컨테이너(XDP 프로그램 작동), 백앤드 컨테이너, Packet beat 컨테이너 or 포함된 컨테이너(수정 가능)
>1. Dockerfile 빌드, 컨테이너 생성
>2. apt install linux-header-$(uname -r) 
>3. 컴파일
	clang -O2 -target bpf -o prog_kern.o -c prog_kern.c -g
	gcc -o process prog_user.c -g -lbpf -lxdp 
>4. 실행
	./process

![flow](./Process_load.jpg)

##### 🔍참고 자료

 >1. eBPF 프로그램 작성 : [main/레퍼런스/원본/Fast packet processing with ebpf and xdp Concepts, code, challenges, and applications.pdf at main · DDoSMitigation/main (github.com)](https://github.com/DDoSMitigation/main/blob/main/%EB%A0%88%ED%8D%BC%EB%9F%B0%EC%8A%A4/%EC%9B%90%EB%B3%B8/Fast%20packet%20processing%20with%20ebpf%20and%20xdp%20Concepts%2C%20code%2C%20challenges%2C%20and%20applications.pdf)
 >2. DDoS 방어 솔루션 구축 : [main/DDoS 공격 종류 및 대응 방안.pdf at main · DDoSMitigation/main (github.com)](https://github.com/DDoSMitigation/main/blob/main/DDoS%20%EA%B3%B5%EA%B2%A9%20%EC%A2%85%EB%A5%98%20%EB%B0%8F%20%EB%8C%80%EC%9D%91%20%EB%B0%A9%EC%95%88.pdf)
> 3. libbpf 활용 : [LIBBPF API — libbpf documentation (libbpf-test.readthedocs.io)](https://libbpf-test.readthedocs.io/en/latest/api.html)
> 4. AF_XDP Socket 핵심 코드 : [xdp-tutorial/advanced03-AF_XDP/af_xdp_user.c at master · xdp-project/xdp-tutorial (github.com)](https://github.com/xdp-project/xdp-tutorial/blob/master/advanced03-AF_XDP/af_xdp_user.c)