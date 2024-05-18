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

일반 옵션 목록
|옵션|의미|사용법|
|:----:|:----:|:----|
|msg|메시지|msg:"hello";|
|noalert|경고를 생성하지 않고 상태를 표시함|noalert;|
|sid|규칙 고유번호 부여|sid:123;|
|rev|버전 표시 (수정 시 버전이 올라감)|rev:1;|
|metadata|key와 value 값이 한 쌍으로 주어진 데이터|metadata: key value, key value;|
|target|공격의 대상이되는 요소를 지정함|target:[ip 주소];|
|clastype|이벤트의 분류를 지정함 (classification.conf에 타입명이 있으며 직접 정의하거나 수정할 수 있다.|classtype:분류 이름;|
|priority|규칙 우선순위 지정 (범위 : 1 ~ 10)|priority:1;|
|reference|규칙으로 인해 탐지된 이벤트에 대한 추가 정보 제공 (reference.config에 타입명이 있으며 직접 정의하거나 수정정할 수 있다.) |reference:type,reference|

자세한 옵션 목록 : https://docs.suricata.io/en/latest/rules/meta.html
<br><br><br>



데이터 검사 옵션 목록
|옵션|의미|사용법|
|:----:|:----:|:----|
|content|특정 내용 검사|content:값|
|offset|검사 시작 위치 지정|offset:값|
|depth|offset을 시작으로 검사할 데이터의 최대 길이 지정|depth:값|
|byte_test|페이로드 내의 특정 위치에서 정수값을 추출하고, 그 값에 대해 비교 연산을 수|byte_test:<num_bytes>, <operator>, <value>, <offset>|
|pcre|정규표현식을 사용하여 패킷 데이터를 검사|pcre:정규표현식|
|file.name|파일명 검사|file.name; 데이터 검사 옵션|

<br><br><br>



IP 옵션 목록
|옵션|의미|사용법|
|:----:|:----:|:----:|
|ttl|time to live값 지정|ttl:<number>;|
|ipopts|IP헤더에 포함된 옵션 검사|ipopts:<name>;|
|sameip|출발지와 목적지 IP가 같은 경우(Land Attack)|sameip;|
|ip_proto|해당 패킷에 포함되어있는 프로토콜 검사|ip_proto:<프로토콜 이름>;|
|geoip|IP의 국가 확인|gepip:<src|dst|both|any>,국가1,국가2,국가3;|
|id|해당 id 검사|id:<number>;|
|ipv4.hdr|ipv4 헤더 전체에 대한 상세 사항|ipv4.hdr; 데이터 검사 옵션|
|ipv6.hdr|ipv6 헤더 전체에 대한 상세 사항|ipv6.hdr; 데이터 검사 옵션|

<br><br><br>



TCP 옵션 목록
|옵션|의미|사용법|
|:----:|:----:|:----:|
|tcp.flags|플래그 지정|tcp.flags:<flag><flag2><flag3> <--- 플래그명의 첫 철자를 대문자로 이어서 입력하면 된다.|
|seq|시퀀스번호 지정|seq:<number>|
|ack|ack번호 지정|ack:<number>|
|window|window크기 지정|window:<number>|
|tcp.hdr|tcp 헤더 전체에 대한 상세 사항|tcp.hdr; 데이터 검사 옵션|
|tcp.mss|최대 세그먼트 크기 지정|tcp.mss [< 또는 > 또는 생략 가능] 값|

<br><br><br>



UDP 옵션 
|옵션|의미|사용법|
|:----:|:----:|:----:|
|udp.hdr|udp 헤더 전체에 대한 상세 사항|udp.hdr; 데이터 검사 옵션|

<br><br><br>



HTTP 옵션
|옵션|의미|사용법|
|:----:|:----:|:----:|
|http.accept|HTTP 요청헤더의 Accept필드 검사|http.accept; 데이터 검사 옵션|
|http.accept_enc|HTTP 요청헤더의 Accept_Encoding필드 검사|http.accept_enc; 데이터 검사 옵션|
|http.accept_lang|HTTP 요청헤더의 Accept_Language필드 검사|http.accept_lang; 데이터 검사 옵션|
|http.host|HTTP 요청헤더의 host필드 검사 (정규화)|http.host; 데이터 검사 옵션|
|http.host_raw|HTTP 요청헤더의 host필드 검사 (비정규화|http.host_raw; 데이터 검사 옵션|
|http.method|HTTP 요청헤더에 사용되는 메서드 검사|http.method; 데이터 검사 옵션|
|http.referer|HTTP 요청헤더의 referer필드 검사|http.referer; 데이터 검사 옵션|
|http.request_body|HTTP 요청 본문 검사|http.request_body; 데이터 검사 옵션|
|http.request_line|HTTP 요청행 전체 검사|http.request_line; 데이터 검사 옵션|
|http.uri|HTTP 요청헤더의 URI 검사 (정규화)|http.uri; 데이터 검사 옵션|
|http.uri_raw|HTTP 요청헤더의 URI 검사 (비정규화)|http.uri_raw; 데이터 검사 옵션|
|http.user_agent|HTTP 요청헤더의 User-Agent필드 검사|http.user_agent; 데이터 검사 옵션|
|urilen|정규화된 요청 URI의 길이|urilen:값|
|http.location|HTTP 응답헤더의 location필드 검사|http.location; 데이터 검사 옵션|
|http.response_body|HTTP 응답 본문 검사|http.response_body; 데이터 검사 옵션|
|http.response_line|HTTP 응답행 전체 검사|http.response_line; 데이터 검사 옵션|
|http.server|HTTP 응답헤더의 Server필드 검사|http.server; 데이터 검사 옵션|
|http.stat_code|HTTP 상태 코드 검사|http.stat_code; 데이터 검사 옵션|
|http.stat_msg|HTTP 상태 메시지 검사|http.stat_msg; 데이터 검사 옵션|
|http.connection|HTTP 요청/응답헤더의 Connection필드 검사|http.connection; 데이터 검사 옵션|
|http.content_len|HTTP 요청/응답헤더의 Content_Length필드 검사|http.content_len; 데이터 검사 옵션|
|http.content_type|HTTP 요청/응답헤더의 Content_Type필드 검사|http.content_type; 데이터 검사 옵션|
|http.cookie|HTTP 요청/응답헤더의 Cookie필드 검사|http.cookie; 데이터 검사 옵션|
|http.hdr|http 헤더 전체에 대한 상세 사항|http.hdr; 데이터 검사 옵션|
|http.header_names|http 헤더 이름 검사 (주로 헤더 순서 검사에 사용)|http.hdr; 데이터 검사 옵션|
