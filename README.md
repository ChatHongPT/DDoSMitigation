4월 25일
- 레퍼런스 서치

5월 3일
- 논문 리뷰 중간 점검

5월 13일
- 격주 보고서 초안

5월 14일
- 격주 보고서 초안 검토 및 피드백

5월 15일
- 격주 보고서 피드백 반영

5월 16일
- 격주 보고서 마무리

5월 17일
- 격주 보고서 제출 - (도환, 도현)

5월 18일
### 논문 리뷰
- 강성원 BGP Anycast Tuner Intuitive Route Management for Anycast Services
- 최홍석 Routing Around Congestion Defeating DDoS Attacks and Adverse Network Conditions via Reactive BGP Routing
- 지도환 DDoS Mitigation AMeasurement-Based Approach & Understanding the Behaviors of BGP-based DDoS Protection Services

5월 19일
- 함준형 Anycast Agility Network Playbooks to Fight DDoS
- 라민우 Fast packet processing with ebpf and xdp: Concepts, code, challenges, and applications
- 임정훈 Extended Berkeley Packet Filter: An Application Perspective
- 김도현 An eBPF-XDP hardware-based network slicing architecture for future 6G front to back haul networks

5월 28일
- 중간 발표

5월 31일
- 격주 보고서 제출 - (홍석, 정훈)

6월 14일
- 격주 보고서 제출 - (성원, 준형)

6월 28일
- 격주 보고서 제출 - (민우)

7월 6일
- 최종 발표




# 해야할 일
__모든 인원__ : 논문 요약 및 번역본 github 업로드<br>
__도환, 도현__ : 격주 보고서 초안 작성<br>
__준형, 민우__ : XDP 보안 코드 개발<br>
__홍석__ : DDoS 공격 종류 및 각 공격 유형별 대응 방안 조사<br>
__성원, 정훈__ : 논문 초안 작성<br>


- 준형 Anycast Agility Network Playbooks to Fight DDoS __논문 요약 및 번역 완료__
- 성원 BGP Anycast Tuner Intuitive Route Management for Anycast Services
- 홍석 Routing Around Congestion Defeating DDoS Attacks and Adverse Network Conditions via Reactive BGP Routing
- 도환 DDoS Mitigation AMeasurement-Based Approach & Understanding the Behaviors of BGP-based DDoS Protection Services
- 민우 Fast packet processing with ebpf and xdp: Concepts, code, challenges, and applications __논문 요약 및 번역 완료__
- 정훈 Extended Berkeley Packet Filter: An Application Perspective
- 도현 An eBPF-XDP hardware-based network slicing architecture for future 6G front to back haul networks

- 
## 논문 핵심

- 핵심: 대용량 패킷을 BGP를 이용한 Anycast 구축으로 패킷을 분산 시킴, BGP Flowspec, eBPF/XDP를 이용해 악성 패킷 분류 및 필터링 진행하여 대용량 패킷부터 세밀한 패킷까지 정교하게 필터링 하는 방법에 대해 알려줌
- 추가: AI를 이용해 악성 패킷과 정상 패킷을 구분, 로그에 쌓이는 패킷 데이터를 기반으로 AI가 점점 쌓이는 패킷 로그를 기반으로 정교한 패킷 분류 알고리즘을 생성
- 추가: 웹과 연동하여서 실시간으로 모니터링 할 수 있도록 기능 제공
