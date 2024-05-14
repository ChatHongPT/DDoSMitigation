Arkime
=============

Arkime는 네트워크 트래픽 분석 및 보안 감사를 위한 오픈 소스 도구이다.
대규모 네트워크 트래픽을 수집, 저장하고 이를 분석하여 네트워크 상태를 모니터링하고 보안 이슈를 탐지하는 데 사용된다.

Arkime는 크게 3가지 요소로 구성된다.

Capture: 네트워크 트래픽을 모니터링하고 PCAP(패킷 캡처) 형식으로 디스크에 저장한다. 캡쳐된 패킷을 분석하고 메타데이터를 Elasticsearch와 같은 데이터베이스에 전송하는 C 어플리케이션다.

viewer: 캡처된 데이터를 시각화하고 검색할 수 있는 웹 인터페이스를 제공하는 Node.js 어플리케이션이다. 사용자는 이를 통해 네트워크 상태를 모니터링하고 보안 이슈를 탐지할 수 있다. 또한 PCAP 파일을 열람하고 검색할 수 있는 기능도 제공된다.

OpenSearch/Elasticsearch: Arkime가 사용하는 검색 데이터베이스 기술이다. 이를 통해 캡처된 데이터와 메타데이터를 저장하고 검색할 수 있다. Elasticsearch는 대규모 데이터를 실시간으로 색인화하고 검색할 수 있는 뛰어난 성능을 제공한다.




설정 적용
=============
Arkime는 지정한 네트워크 인터페이스의 모든 네트워크 트래픽을 탐지하는데 내부 서버들끼리 통신하는 패킷도 탐지해버려서 PCAP의 용량이 커지며, Elasticsearch의 성능에도 영향을 미친다. 

따라서 설정을 통해 필요없는 패킷을 탐지 안하도록 설정해야한다.

https://arkime.com/faq

/data/moloch/etc/config.ini 파일에서 설정한다.

#bpf

거부하고 싶은 트래픽을 필터링한다. 

bpf=not port 9200 # 9200포트 필터링 (Elasticsearch)

#dontSaveBPFs

허용하지 않는 bpf 목록이다. port의 ':' 뒤에 필터당 저장할 패킷 수슬 지정할 수도 있다.

dontSaveBPFs=port22:5 # 22번 포트에 대해 5개의 패킷만 저장한다.

#packet-drop-ips

Drop IP address를 지정한다. packet-drop-ips는 패킷이 moloch-capture 프로세스에 직접 도달한다.

-많은 범위의 ip를 drop시킬 때 bpf보다 유용함.

-drop 범위에 포함되는 allow 범위를 만들수 있음 (블랙리스트 정책)

[packet-drop-ips]
192.168.1.0/24=drop # 192.168.1.1~255 Drop
192.168.1.10=allow  # 192.168.1.10은 Allow
fe60::5d9b:1ce3:3dc7:9fc2=drop # ipv6도 가능
