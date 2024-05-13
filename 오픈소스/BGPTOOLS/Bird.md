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

**라우팅 정책 설정**
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
#### **BGP_Filtering**
예시1)
**import 기능에서의 접두사 및 경로 필터링**
-> 인터넷에서 특수한 목적으로 예약된 IP 주소 범위를 필터링하기 위해

```
//martain IP 주소 범위에 대한 필터 정의
function net_martian()
{
  return net ~ [ 169.254.0.0/16+, 172.16.0.0/12+, 192.168.0.0/16+, 10.0.0.0/8+, 
    127.0.0.0/8+, 224.0.0.0/4+, 240.0.0.0/4+, 0.0.0.0/32-, 0.0.0.0/0{25,32}, 0.0.0.0/0{0,7} ];
}

//로컬 네트워크의 주소 범위 설정
function net_local()
{
  return net ~ [ 12.10.0.0/16+, 34.10.0.0/16+ ];
}

//BGP import 경로의 유효성 확인
function rt_import(int asn; int set peer_asns; prefix set peer_nets)
{
  if ! (net ~ peer_nets) then return false;
  if ! (bgp_path.last ~ peer_asns) then return false;
  if bgp_path.first != asn then return false;
  if bgp_path.len > 64 then return false;
  if bgp_next_hop != from then return false;
  return true;
}

//로컬 or martain 네트워크를 제외한 모든 경로 수용
function rt_import_all(int asn)
{
  if net_martian() || net_local() then return false;
  if bgp_path.first != asn then return false;
  if bgp_path.len > 64 then return false;
  if bgp_next_hop != from then return false;
  return true;
}

//경로 서버를 import 하기 위한 필터 구현
function rt_import_rs(int asn)
{
  if net_martian() || net_local() then return false;
  if bgp_path.len > 64 then return false;
  return true;
}
```

예시 2)
**일반적인 export 기능**
```
//BGP 라우팅 경로를 export할때 사용되는 조건
function rt_export()
{
  if proto = "static_bgp" then return true;
  if source != RTS_BGP then return false;
  if net_martian() then return false;
  if bgp_path.len > 64 then return false;
  # return bgp_next_hop ~ [ 100.1.1.1, 100.1.1.2, 200.1.1.1 ];
  return bgp_path.first ~ [ 345, 346 ];
}

//더 넓은 범위의 BGP 경로를 export하기 위한 조건
function rt_export_all()
{
  if proto = "static_bgp" then return true;
  if source != RTS_BGP then return false;
  if net_martian() then return false;
  if bgp_path.len > 64 then return false;
  return true;
}
```

예시 3) 
**이웃을 위한 특정 필터**
```
filter bgp_in_uplink_123
{
  if ! rt_import_all(123) then reject;
  accept;
}
filter bgp_out_uplink_123
{
  if ! rt_export() then reject;
  accept;
}
filter bgp_in_peer_234
{
  if ! rt_import(234, [ 234, 1234, 2345, 3456 ],
        [ 12.34.0.0/16, 23.34.0.0/16, 34.56.0.0/16 ])
  then reject;
  accept;
}
filter bgp_out_peer_234
{
  if ! rt_export() then reject;
  accept;
}
filter bgp_in_rs
{
  if ! rt_import_rs() then reject;
  accept;
}
filter bgp_out_rs
{
  if ! rt_export() then reject;
  accept;
}
filter bgp_in_client_345
{
  if ! rt_import(345, [ 345 ], [ 34.5.0.0/16 ]) then reject;
  accept;
}
filter bgp_out_client_345
{
  if ! rt_export_all() then reject;
  accept;
}
```
