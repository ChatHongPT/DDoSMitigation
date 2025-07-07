# 한국정보기술연구원 화이트햇 스쿨 2기 프로젝트

## 프로젝트 활동 내역
[Main Repository](https://github.com/DDoSMitigation/main)

## 프로젝트 개요
저사양 환경에서 패킷을 모니터링하여 악성 패킷을 분류하고 차단하는 것을 목표로 하며, 누구나 무료로 안전한 인프라를 구성하는 것을 프로젝트 목표로 하고 있습니다.

## 멘토 및 주요 인원

### 멘토
- **박건호** (Hyundai AutoEver)

### 프로젝트 리더 (PL)
- **곽송이** (Cloudflare)

### 프로젝트 매니저 (PM)
- **함준형** (배재대학교) [LinkedIn](https://www.linkedin.com/in/%EC%A4%80%ED%98%95-%ED%95%A8-669898284/)

### 팀원
- **강성원** (배재대학교)
- **최홍석** (전북대학교) [LinkedIn](https://www.linkedin.com/in/%ED%99%8D%EC%84%9D-%EC%B5%9C-089b23302?utm_source=share&utm_campaign=share_via&utm_content=profile&utm_medium=ios_app)
- **임정훈** (조선대학교) [LinkedIn](https://www.linkedin.com/in/%EC%A0%95%ED%9B%88-%EC%9E%84-235b06304/)
- **지도환** (국립한밭대학교) [LinkedIn](www.linkedin.com/in/정훈-임-235b06304/)
- **김도현** (강릉원주대학교)
- **라민우** (건국대학교) [LinkedIn](https://www.linkedin.com/in/raminwo/)

## 네트워크 정보
- **네트워크:** AS216362 (함준형)
- **업스트림:** AS20473 (The Constant Company, LLC), AS199524 (G-Core Labs S.A.)
- **애니캐스트 네트워크:** AS199524 (G-Core Labs S.A.)

[홈페이지](https://ddosmitigation.github.io/)

## 일정

### 4월
- **25일:** 논문, 오픈소스, 기술 정의, 공식문서 등 각종 참고할 문서 검색
- **29일:** 온라인 미팅, 깃헙 생성
- **30일:** 팀원 회의

### 5월
- **3일:** 논문 리뷰 중간 점검
- **5일:** BGP flowspec AS216362 적용 방안에 대한 논의
- **6일:** 온라인 미팅, GSLB 적용 방안 논의
- **7일:** XDP Firewall 적용 방안 논의
- **9일:** 민우, 준형 XDP 악성 패킷 차단 솔루션 개발, 논문 리뷰 대상 탐색.
- **10일:** 팀원 회의
- **11일:** DDoS 공격 종류 및 각 공격별 대응 방안 조사
- **13일:** 격주 보고서 초안 작성, 온라인 미팅, 팀원 회의, 논문 작성 시작, 배재대학교 함형민 교수님 논문 및 프로젝트에 대한 멘토링
- **14일:**
  - 격주 보고서 초안 검토 및 피드백
  - 도현 개발 솔루션 합류
  - Electrode: Accelerating Distributed Protocols with eBPF
  - BPFast: 클라우드 환경을 위한 eBPF/XDP 기반 고속 네트워크 패킷 페이로드 검사 시스템
  - eBPF/XDP Based Network Traffic Visualization and DoS Mitigation for Intelligent Service Protection
  - The eXpress Data Path (XDP): Fast Programmable Packet Processing in the Operating System Kernel
  - cilium bgp xdp docs, AWS 사용계획서 제출 후 KITRI 지원 예정
- **15일:** 격주 보고서 피드백 반영, 내부 팀원끼리 논문 초안 피드백, 논문 1차 초안 작성
- **16일:** 격주 보고서 마무리
- **17일:** 격주 보고서 제출 (도환, 도현), 한국해양대학교 이민우 교수님 논문 초안 피드백
- **18일:** 논문 리뷰, 세미나 발표 정리, 보안 솔루션 개발
  - 강성원: "BGP Anycast Tuner Intuitive Route Management for Anycast Services"
  - 최홍석: "Routing Around Congestion Defeating DDoS Attacks and Adverse Network Conditions via Reactive BGP Routing"
  - 지도환: "DDoS Mitigation AMeasurement-Based Approach & Understanding the Behaviors of BGP-based DDoS Protection Services"
- **19일:** 논문 리뷰, 세미나 발표 정리, 
  - 함준형: "Anycast Agility Network Playbooks to Fight DDoS"
  - 라민우: "Fast packet processing with ebpf and xdp: Concepts, code, challenges, and applications"
  - 임정훈: "Extended Berkeley Packet Filter: An Application Perspective"
  - 김도현: "An eBPF-XDP hardware-based network slicing architecture for future 6G front to back haul networks"
- **20일:** DoS 공격 코드 구현, flowchart 제작, 중간 발표를 위한 중간 점검
- **21일:** ELK Stack 컨테이너 생성 및 가이드라인 제작, 논문 피드백 반영, 추가 레퍼런스 서치, DPI 솔루션 개발
- **22일:** 내부 중간 점검
- **25일:** 온라인 중간 발표
- **26일:** 대전 오프라인 회식
- **31일:** 격주 보고서 제출 (홍석, 정훈)

### 6월
- **1일:** 이민우 교수님 논문 피드백
- **3일:** 박건호 멘토님 프로젝트 피드백
- **14일:** 격주 보고서 제출 (성원, 준형)
- **28일:** 격주 보고서 제출 (민우)

### 7월
- **6일:** ~~오프라인 최종 발표~~
- **14일:** 오프라인 최종 발표(연기됨)

## 해야 할 일

### 전체 인원
- 논문 요약 및 번역본 GitHub 업로드 (5월 9일 완료)

### 개별 할 일
- **도환, 도현:** 격주 보고서 초안 작성 (완료)
- **준형, 민우:** XDP 보안 코드 개발 (완료)
- **홍석:** DDoS 공격 종류 및 각 공격 유형별 대응 방안 조사 (완료)
- **성원, 정훈, 준형:** 논문 초안 작성 (완료)

- **준형, 민우, 도현:** XDP, DPI 보안 솔루션 개발
- **준형, 성원:** 논문 피드백 반영 및 논문 작성
- **정훈:** ELK 스택 환경 구축

### 논문 요약 및 번역 완료
- **준형:** "Anycast Agility Network Playbooks to Fight DDoS"
- **성원:** "BGP Anycast Tuner Intuitive Route Management for Anycast Services"
- **홍석:** "Routing Around Congestion Defeating DDoS Attacks and Adverse Network Conditions via Reactive BGP Routing"
- **도환:** "DDoS Mitigation AMeasurement-Based Approach & Understanding the Behaviors of BGP-based DDoS Protection Services"
- **민우:** "Fast packet processing with ebpf and xdp: Concepts, code, challenges, and applications"
- **정훈:** "Extended Berkeley Packet Filter: An Application Perspective"
- **도현:** "An eBPF-XDP hardware-based network slicing architecture for future 6G front to back haul networks"

## 오픈소스 가이드라인 작성, docker 컨테이너 배포 리스트
- **Zeek**
- **BCC**
- **Suricata**
- **BGP Tool**
- **XDP Firewall**
- **nDPI**
- **ELK Stack**
- **Arkime**~~(Reject)~~
- **GPT-2**~~(Reject)~~
- **BGP Anycast Tuner**~~(Reject)~~
- **Security Onion**~~(Reject)~~

## 논문 핵심
- **핵심:** 대용량 패킷을 BGP를 이용한 Anycast 구축으로 패킷을 분산. BGP Flowspec, eBPF/XDP를 이용해 악성 패킷을 분류 및 필터링하여 대용량 패킷부터 세밀한 패킷까지 정교하게 필터링 하는 방법 제시. DPI를 통해 악성 행위 판단.
- **추가:** AI를 이용해 악성 패킷과 정상 패킷을 구분. 로그에 쌓이는 패킷 데이터를 기반으로 AI가 점점 정교한 패킷 분류 알고리즘을 생성.
- **추가:** 웹과 연동하여 실시간으로 모니터링 기능 제공.

## 테스트 IP
141.11.245.2

## flowchart
![72cf414dba06509d drawio](https://github.com/DDoSMitigation/.github/assets/102852097/36a365a0-3fb5-467c-84a2-1044236c013e)

## [WBS](https://docs.google.com/spreadsheets/d/11F3qIhni2GcMfhcmm1Ut2klrN8I9nDpVzX6pdEuA2mY/edit?gid=60579148#gid=60579148)(Work Breakdown Structure)
![image](https://github.com/user-attachments/assets/fffcad79-8823-4904-832c-125820919c9f)

## XDP
![1](https://github.com/DDoSMitigation/main/assets/168432982/10a95c4a-39e9-4f48-adeb-2fcef664bdca)

![2](https://github.com/DDoSMitigation/main/assets/168432982/dd7d3edb-3f9a-4338-a16c-4a492ca32a4e)

![3](https://github.com/DDoSMitigation/main/assets/168432982/3b4aa8bd-4f9f-444f-b339-48021bca2907)

![4](https://github.com/DDoSMitigation/main/assets/168432982/f2bd05b2-b368-462a-97b5-c391ff8de74c)


## KITRI 화이트햇 스쿨 2기 프로젝트 고도화 선정(2024.08.01)
활동기간: 2024.08.05 ~ 09.13<br>
양식: https://url.kr/thdejd<br>
1회차: 2024. 08. 07(수). 23시 59분까지<br>
2회차: 2024. 08. 14(수). 23시 59분까지<br>
3회차: 2024. 08. 21(수). 23시 59분까지<br>
4회차: 2024. 08. 28(수). 23시 59분까지<br>
5회차: 2024. 09 04(수). 23시 59분까지<br>
6회차: 2024. 09. 11(수). 23시 59분까지<br>
제출링크: https://forms.gle/vfej4Qm2U44nuR5t7<br>
최종보고서 제출일: 2024. 09. 13(금). 23시 59분까지 제출양식 : 20p 이내의  보고서 PDF
