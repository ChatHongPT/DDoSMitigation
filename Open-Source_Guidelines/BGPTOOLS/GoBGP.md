참고사이트 - https://github.com/osrg/gobgp?tab=readme-ov-file
GoBGP는 최신 환경을 위해 설계된 Go 프로그래밍 언어
대규모 네트워크 환경에서 유리, 다양한 환경지원, 프로그인 시스템을 지원
**설치방법**

```
> sudo apt install gobpgd
> git clone git://github.com/osrg/gobgp (현재 다운 안됌)
> cd gobgp && go mod download
```

**설정방법** (gobgpd.conf)
ex)
```
[global.config]
  as = 64512 // as번호
  router-id = "192.168.255.1" // ip주소

[[neighbors]]
  [neighbors.config]
    neighbor-address = "10.0.255.1" // ip 주소
    peer-as = 65001 // peer AS번호
    auth-password = "hoge1" // MD5 인증 패스워드
  [neighbors.transport.config]
    passive-mode = true // 수동모드
  [neighbors.route-server.config]
    route-server-client = true // 라우트 서버를 클라이언트로 설정

```

**실행방법** 
```
sudo -E gobgpd -f gobgpd.conf
```

**BGP 정보 조회 **
```
gobgp neighbor <홉 주소> local
```

**라우트 추가**
```
gobgp global rib add <네트워크 접두사> nexthop <홉 주소>

```

**라우트 삭제**
```
gobgp global rib del <네트워크 접두사> <홉 주소>

```

**모든 피어 정보**
```
gobgp neighbor
```

**특정 peer의 세부정보**
```
gobgp neighbor <peer 주소>
```

**글로벌 테이블 확인**
```
gobgp global rib
```

**인접한 rib-in, rib-out 확인**
```
gobgp neighbor <IP주소> adj-in
gobgp neighbor <IP주소> adj-out

```
