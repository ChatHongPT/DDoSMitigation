# Suricata란?
Suricata는 고성능 네트워크 IDS, IPS 및 네트워크 보안 모니터링 엔진이다. <br>
이는 오픈 소스이며 커뮤니티 주도의 비영리 재단인 Open Information Security Foundation (OISF)이 소유하고 있다. <br>
Suricata는 OISF에 의해 개발되었다. <br>
네트워크 속도가 빨라지면서 Snort의 단점인 느린 처리 속도를 보완하였다. <br>
비영리재단 OISF에 의해 개발된 IDS 오픈소스 솔루션으로 기존 Snort의 거의 모든 기능 및 Rule의 적용이 가능하다. <br>
또한 멀티코어와 멀티 스레드 방식 및 GPU 가속까지 지원하여 매우 빠른 패킷 분석 및 공격 차단이 가능한 장점이 있다. <br>
또한 YAML 형식지원으로 설정이 직관적이다. <br>

## 환경 설정 가이드

1. suricata를 설치한다.
~~~
sudo apt-get install software-properties-common
sudo add-apt-repository ppa:oisf/suricata-stable
sudo apt-get update
sudo apt-get install suricata jq
~~~

2. 기본 이더넷 설정
~~~
sudo vim /etc/suricata/suricata.yaml

af-packet:
    - interface: 이더넷명
      cluster-id: 99
      cluster-type: cluster_flow
      defrag: yes
      use-mmap: yes
      tpacket-v3: yes

위와 같이 설정 해준다.
기본적으로 설정 되어있지만 use-nmap과 tpacket-v3는 주석 처리되어있으므로 해당 부분은 주석을 지우고 위와같이 설정하면 된다.
~~~

3. suricata 업데이트 후 재기동
~~~
sudo suricata-update
sudo systemctl restart suricata
sudo tail /var/log/suricata/suricata.log // 로그 확인해서 제대로 동작하는지 확인한다.
~~~

