**설치방법**
```
sudo apt update
sudo apt install bird
```

**설정파일**
```
cd /etc/bird/bird.conf
sudo vi bird.conf
```

**설정방법**
예시 1)
```
log syslog all; //시스템 로그에 모든 이벤트를 기록

router id A.B.C.D; //라우터의 고유 식별자 설정(IP주소)

protocol device { 
        scan time 10; //스캔 주기 설정
}

protocol kernel {
        export all; //내부->외부로 모두 허용
        scan time 15; 
}

protocol static static_bgp { 
        import all; //외부->내부로 모두 허용

        route A.B.C.0/24 reject;  // 네트워크로의 라우팅을 거부
        route D.E.F.0/24 reject;  // D.E.F.0/24네트워크로의 라우팅을 거부
}

protocol static static_ospf {
        import all; 외부->내부로 모두 허용
        route 0.0.0.0/0 via W.X.Y.Z;  // 모든 목적지에 대한 기본 경로를 W.X.Y.Z 게이트웨이로 설정
}

protocol bgp {
        import none; // 외부->내부로 모두 거부
        export where proto = "static_bgp"; // static_bgp으로 설정된 경로만 외부로 보냄

        local as XXXX;  # 로컬 AS 번호를 XXXX로 설정
        neighbor W.X.Y.Z as YYYY;  # 이웃 AS와의 연결 정보를 설정
}

protocol ospf {
        import all; //외부->내부로 모두 허용
        export where proto = "static_ospf";  // static_ospf으로 설정된 경로만 외부로 보냄
}

```
예시2)
```
log syslog all; // 시스템 로그에 모든 이벤트를 기록

router id A.B.C.D; // 라우터의 고유 식별자 설정(IP주소)

protocol device {
        scan time 10; // 스캔 주기 설정
}

protocol kernel {
        export all; // 내부->외부로 모두 허용
        scan time 15; 
}

protocol static static_bgp { 
        import all; // 외부->내부로 모두 거부

        route A.B.C.0/24 reject; // A.B.C.0/24 네트워크로의 라우팅을 거부
        route D.E.F.0/24 reject; // D.E.F.0/24 네트워크로의 라우팅을 거부
}

protocol static static_ospf {
        import all; // 외부->내부로 모두 거부

        route 0.0.0.0/0 reject; // 기본 경로로서, 모든 목적지로의 라우팅을 거부
}

protocol bgp bgp_abc {
        import all; // 외부->내부로 모두 거부
        export where proto = "static_bgp"; // static_bgp 프로토콜을 통해 설정된 경로만 외부로 내보냄

        local as XXXX; // 로컬 자율 시스템 번호를 XXXX로 설정합니다.
        neighbor W1.X1.Y1.Z1 as YYYY; // AS 번호 YYYY를 가진 이웃 W1.X1.Y1.Z1과 BGP 세션을 설정
}

protocol bgp bgp_def {

```
