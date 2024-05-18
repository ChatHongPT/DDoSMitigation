# DDoS
DDoS(Distributed Denial of Service) 공격은 인터넷 서비스를 지연 혹은 중단 시키는 공격이다. <br>
악성코드로 수 많은 좀비 PC를 만든다음 공격자는 좀비 PC에게 공격 명령을 내림으로서 공격 대상 서버는 한 번에 많은 트래픽을 감당하지 못해 마비되어버린다.<br>
![image](https://github.com/DDoSMitigation/main/assets/45961274/00cd15f1-34b8-4bbf-963e-b02b8149be4b)
<br>

# 공격 유형
공격 유형에는 여러가지 종류가 있다.

## 1. 볼륨 기반 공격
이 유형의 공격은 네트워크의 대역폭을 소모시키는 것을 목표로 한다. <br>
대량의 트래픽을 생성하여 네트워크를 포화시키고, 정상적인 트래픽이 서버에 도달하지 못하게 한다.<br>

|공격 기법|설명|
|----|----|
|UDP Flood|임의의 포트로 큰 수의 UDP 패킷을 보내서 대상 시스템을 포화시킴|
|ICMP (Ping) Flood|대상에게 무수히 많은 ICMP(Echo Request)를 보내 응답을 강요하며 자원을 소모|
|DNS Amplification| DNS 서버를 이용해 작은 요청으로 큰 응답을 유도하여 목표 시스템으로 반사|
|NTP Amplification| NTP 서버를 이용해 작은 요청으로 큰 응답을 유도하여 목표 시스템으로 반사|
|DNS Flood| 다수의 DNS 요청을 목표 DNS 서버에 보내서 서버의 대역폭을 소진|
|VoIP Flood | 대량의 SIP 패킷을 보내서 VoIP 시스템 자원을 소진|
|SSDP Flood| 다수의 SSDP 요청을 네트워크 브로드캐스트 주소로 보내서 네트워크 자원을 소진|
|Chargen Flood| Chargen 요청을 보내 대량의 응답 트래픽을 유도하여 네트워크 대역폭을 소진|
|DNS Reflection Attack| 위조된 소스 IP 주소를 사용하여 DNS 서버에 요청을 보내고 응답을 목표 시스템으로 반사|
|UDP Amplification Attack| 작은 요청을 UDP 서비스로 보내고 큰 응답 트래픽을 목표 시스템으로 반사|
|ICMP Echo Request Flood| 대량의 ICMP Echo Request (ping) 패킷을 보내서 네트워크 대역폭을 소진|

<br>




## 2. 프로토콜 공격
이 공격은 네트워크 계층과 전송 계층의 프로토콜 오류를 이용하여 서버의 리소스를 고갈시킨다.<br>

|공격 기법|설명|
|----|----|
|SYN Flood| 대량의 SYN 요청을 보내서 서버의 연결 대기 큐를 가득 채워 서비스 거부를 유발|
|ACK Flood| 다수의 ACK 패킷을 보내 서버 자원을 소진|
|FIN Flood| 대량의 FIN 패킷을 보내서 연결 해제를 시도해 서버 자원을 소진|
|TCP Connection Flood| 대량의 TCP 연결을 열어서 서버 자원을 소진|
|TCP RST Attack| TCP 연결을 리셋하는 RST 패킷을 보내서 기존 연결을 끊어 서비스 거부를 유발|
|Fragmented Packet Attack| 큰 패킷을 여러 조각으로 나누어 전송, 재조합 과정에서 서버 자원을 소진|
|Ping of Death| 비정상적으로 큰 ICMP 패킷을 보내 서버의 네트워크 스택을 오버플로우시킴|
|Smurf Attack| ICMP Echo 요청을 브로드캐스트 주소로 보내고 응답을 목표 시스템으로 반사시켜 네트워크 자원을 소진|
|Land Attack| 출발지와 목적지 IP 주소를 동일하게 설정해 패킷을 전송, 서버를 혼란에 빠뜨려 자원을 소진|
|IP/ICMP Fragmentation| 잘못된 IP 조각을 보내 재조합 과정에서 서버 자원을 소진|

<br>



## 3. 응용 프로그램 계층 공격
응용 프로그램 계층(레이어 7)에 직접 공격을 가하여 서버의 리소스를 소모시킨다.<br>
이는 특정 웹 애플리케이션의 취약점을 대상으로 한다.<br>

|공격 기법|설명|
|----|----|
|HTTP Flood| 대량의 HTTP 요청을 보내 웹 서버의 자원을 소진|
|Slowloris| HTTP 헤더를 천천히 전송해 서버의 연결을 장시간 점유함으로써 자원을 소진|
|RUDY (R U Dead Yet)| HTTP POST 요청을 천천히 전송해 서버의 연결을 점유하고 자원을 소진|
|LOIC (Low Orbit Ion Cannon)| 많은 수의 HTTP 요청을 자동으로 생성하여 서버 자원을 소진|
|Cache Busting| 캐시 무효화를 위해 URL 매개변수를 조작하여 대량의 요청을 보내 웹 서버의 자원을 소진|
|DNS Query Flood| 대량의 DNS 요청을 보내 DNS 서버 자원을 소진|
|XML Bomb| XML 문서의 확장을 유발하여 서버 자원을 소진|
|Session Flood| 대량의 세션을 생성해 웹 서버 자원을 소진|
|WordPress Pingback Attack| WordPress의 핑백 기능을 악용해 대량의 요청을 보내 웹 서버 자원을 소진|
|VoIP Flood| 대량의 VoIP 요청을 보내 VoIP 서버 자원을 소진|

<br>



## 4. 멀티 벡터 공격
여러 유형의 공격 기법을 조합하여 동시에 시행하는 것을 말한다.<br>
이는 방어책을 복잡하게 만들어 공격의 효과를 극대화한다.<br>
각 유형의 DDoS 공격은 특정 목적과 기술에 기반을 두고 있으며, 공격을 효과적으로 방어하기 위해서는 공격 유형을 정확히 이해하고 적절한 대응책을 마련해야 한다. <br>
