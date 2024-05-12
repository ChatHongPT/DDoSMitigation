# Suricata Rule

~~~
alert http $HOME_NET any -> $EXTERNAL_NET any (msg:"HTTP GET Request Containing Rule in URI"; flow:established,to_server; http.method; content:"GET"; http.uri; content:"rule"; fast_pattern; classtype:bad-unknown; sid:123; rev:1;)

(액션) (프로토콜) (출발지 IP) (출발지 port) -> (목적지 IP) (목적지지 port) (option)

snort와 문법이 동일하다.
~~~

## (액션)
전체적인 작업을 명시하는 부분이다.

|액션명|의미|
|:----:|:----:|
|alert|경고를 생성|
|pass|패킷의 추가 검사를 중지|
|drop|패킷을 삭제하고 경고를 생성|
|reject|일치하는 패킷의 보낸 사람에게 RST/ICMP 불가 에러를 전송|
|rejectsrc|reject와 동일|
|rejectdst|일치하는 패킷의 수신자에게 RST/ICMP 오류 패킷을 전송|
|rejectboth|대화의 양쪽에 대해 RST/ICMP 오류 패킷을 전송|

## (프로토콜)
프로토콜 유형을 명시하는 부분이다.<br>
OSI 7계층 프로토콜을 모두 지원한다.

## (출발지 IP) (목적지 IP)
출발지와 목적지의 IP를 명시하는 부분이다. <br>
단일IP 뿐만 아니라 특정 조건의 IP나 다수의 IP도 가능하다.

|연산자|의미|
|:----:|:----:|
|../..|IP 범위(넷마스크)|
|!|예외|
|[...,...]|IP 그룹|

## (출발지 port) (목적지 port)
출발지와 목적지의 IP를 명시하는 부분이다. <br>
단일port 뿐만 아니라 특정 조건의 port나 다수의 port도 가능하다.

|연산자|의미|
|:----:|:----:|
|[:]|port 범위|
|!|예외|
|[...,...]|port 그룹|

## (옵션)
기타 상세한 옵션을 명시하는 부분이다.

~~~
문법

<키워드> : <설정>; --> 항상 끝에는 ";"을 붙여야한다.
<키워드>;
~~~

옵션 목록
|옵션|의미|예시|
|:----:|:----:|:----|
|msg|메시지|msg:"hello";|
|noalert|경고를 생성하지 않고 상태를 표시함|noalert;|
|sid|규칙 고유번호 부여|sid:123;|
|rev|버전 표시|rev:1;|

