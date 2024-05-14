https://docs.rockylinux.org/guides/network/openbgpd_bgp_router/#checking-bgp-status
**설치방법**
```
> sudo apt-get install openbgpd
```

**설정방법**
```
> rm /etc/bgpd.conf 
> touch /etc/bgpd.conf 
> chmod 0600 /etc/bgpd.conf
```

**bgpd.conf 설정 예시**
```
AS <AS 번호>
router-id <IP주소> // 라우터 ID로 사용할 자신의 IP주소 지정

listen on 127.0.0.1 // bGP 서비스에 대한 로컬 접근 허용
listen on <IP주소> // BGP 서비스에 대한 IP주소 지정 (IPv4, IPv6)
listen on ::1 // IPv6에서 자신의 주소(로컬 루프백 주소)
log updates // 경로 변경사항 기록
network <IPV4 네트워크/MASK> // IPv4 네트워크 및 서브넷 마스크 지정
network <IPV6 네트워크/MASK> // IPv4 네트워크 및 서브넷 마스크 지정

// BGP에서 자신의 네트워크를 외부 BGP 피어에게 알림
allow to ebgp prefix { IPV4_TO_ADVERTISE/MASK IPV6_TO_ADVERTISE/MASK }

neighbor PEER_IPV4 {
    remote-as               <PEER_AS> // 피어 AS 번호
    announce IPv4           unicast // IPv4 유내캐스트 경로를 알리도록 설정
    announce IPv6           none // IPv6 경로를 알리지 않도록 설정
    local-address           <IPv4주소> // BGP 세션에 사용할 로컬 IPv4주소 지정
}

neighbor PEER_IPV6 {
    remote-as               <PEER_AS> // 피어 AS 번호
    announce IPv4           none // IPv4 경로를 알리지 않도록 설정
    announce IPv6           unicast // IPv6 유니캐스트 경로를 알리도록 설정
    local-address           <YOUR_IPV6> // BGP 세션에 사용할 로컬 IPv6주소 지정
}
```

**IP 포워딩 활성화**
```
/etc/sysctl.conf 작성
net.ipv4.ip_forward = 1
net.ipv6.conf.all.forwarding = 1

sysctl -p /etc/sysctl.conf //변경사항 적용
sudo systemctl enable --now bgpd
```

**OpenBGPD 서비스 시작**
```
sudo systemctl start bgpd
```

### 명령어

**BGP 상태 확인**
```
bgpctl show
```

**BGP 경로 확인**
```
bgpctl show rib
```

**BGPD의 FIB(Forwarding Information Base)에서의 라우팅 확인**
```
bgpctl show fib filter
```

**BGP 네트워크 접두사를 추가/제거**
```
bgpctl show add/delete
```

**디버그 로깅 활성화/비활성화**
```
bgpctl log brief/verbose
```

**이웃 세션 관리하거나 조작**
```
bgpctl neighbor [peer] [operation]
```
[operation]
- clear - 지정된 이웃과 BGP 세션을 중지하고 다시시작
- destoty - 이전에 복제된 이웃을 제거
- down - 지정된 이웃과 BGP 세션을 중단
- refresh - 이웃에게 모든 라우트를 다시 보내도록 요청
- up - 지정된 이웃과 BGP 세션 활성화

**flowspec 규칙 추가**
```
bgpctl flowspec add [IP버전] match [일치조건] 192.0.2.0/24 then [옵션]

```
[IP 버전]

inet - ipv4

inet6 - ipv6

[일치조건]

source - 출발 IP주소 or 범위 지정

desination - 목적지 IP주소 or 범위 지정

port - 출발지 or 목적지 포트 or 포트 범위

protocol - 프로토콜 식별 (TCP, UDP)

[옵션]

discard - 일치하는 패킷 폐기

rate-limit X - 일치하는 패킷의 대역폭을 초당 X바이트로 제한

redirect - 트래픽을 다른 목적지로 리다이렉션

mark - 추가 처리를 위해 패킷 표시

**flowspec 규칙 삭제**
```
bgpctl flowspec delete inet match source 192.0.2.0/24
```

**flowspec 규칙 조회**
```
bgpctl flowspec show inet
```

**모든 규칙 초기화**
```
bgpctl flowspec flush
```
