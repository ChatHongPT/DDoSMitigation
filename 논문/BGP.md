# BGP(Border Gateway Protocol)

키워드: [[Anycast]]

BGP(Border Gateway Protocol)란?
ISP나 대규모 기업 네트우크에서 사용하는 라우팅 프로토콜로 AS(자율 시스템) 사이에서 경로 정보를 교환하고, 이를 기반으로 최적의 경로를 선택하여 트래픽을 전달한다. 이를 통해 인터넷에서 데이터 패킷이 목적지로 안정적이고 효율적으로 전달될 수 있도록 한다.

BGP 종류에는 iBGP와 eBGP가 있다.

![Pasted image 20240508183514](https://github.com/DDoSMitigation/main/assets/45961274/60ddf103-fe11-4c77-8b4a-313840348e95)

iBGP - 서로 같은 AS 상의 Border Gateway들 끼리 연결을 담당하는 BGP

eBGP - 서로 다른 AS 상의 Border Gateway들 끼리의 연결을 담당하는 BGP

## BGP 과정

![Pasted image 20240508184007](https://github.com/DDoSMitigation/main/assets/45961274/37dd0582-80b3-4c37-9348-0cd9907aa5e3)

1. 우선 **AS2**에 존재하는 BG(192.32.7.0) 가 자신과 연결된 **AS1**에게 메시지를 보낸다. 메시지에는 **AS2**의 aggregation된 IP주소(192.32.0.0/21) 가 담겨져 있으며, 해당 IP주소로 접근하기 위해 가야하는 경로인 **AS2**를 함께 보낸다.
   
2. 다음으로 **AS1**에 존재하는 두개의 BG(202.32.1.0, 202.32.9.0) 사이에 BGP 메시지를 보낸다. 메시지를 통해 **AS1**의 다른 BG(202.32.9.0) 가 목표 IP 주소(192.32.0.0/21) 로 접근하기 위해 가야하는 경로인 **AS2**를 알게 된다.
   
3. **AS1**과 인접한 **AS3**의 BG에게 BGP 메시지를 보낸다. 메시지를 통해 **AS3**의 BG(143.248.5.0) 는 목표 IP 주소(192.32.0.0/21) 와, 해당 주소로 접근하기 위해 가야하는 경로인 **AS1 AS2**를 알게된다.

즉, 특정 AS에 존재하는 특정 IP 주소를 다른 AS 들에게 소문내서 서로를 연결시키는 과정이라고 보면된다.

BGP 메시지를 주고받는 와중에, Intra-AS 프로토콜인 OSPF나 RIP를 통해 해당 AS 내의 모든 라우터들이 다른 AS에 존재하는 IP 주소를 서로 공유하고, 경로를 설정하게 된다.

