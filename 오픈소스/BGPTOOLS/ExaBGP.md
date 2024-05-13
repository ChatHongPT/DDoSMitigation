참고 사이트 - https://github.com/Exa-Networks/exabgp
1. ExaBGP는 /32 (32비트 사용하는 서브넷 마스크) 서비스 IP를 마이그레이션하는 데이터 간 장애 조치 솔루션을 제공
2. 네트워크 공격을 완화하고 네트워크 수준 필터(blackhole/flowspec)를 중앙에서 배포
3. 네트워크 정보 수집(BGP-LS or Add-Path가 있는 BGP 사용)

**설치방법**

```
> git clone https://github.com/Exa-Networks/exabgp exabgp-git

> cd exabgp-git
> sudo apt install bikeshed
> release binary /usr/local/sbin/exabgp
> /usr/local/sbin/exabgp --version
```

**설치방법 2**(위에 방법이 안될시)

```
sudo python3 -m venv path/to/venv
source path/to/venv/bin/activate
pip3 install exabgp
git clone https://github.com/Exa-Networks/exabgp.git
cd exabgp
python setup.py install
```

**도커**

```
> git clone https://github.com/Exa-Networks/exabgp exabgp-git

> cd exabgp-git
> docker build -t exabgp ./
> docker run -p 179:1790 --mount type=bind,source=`pwd`/etc/exabgp,target=/etc/exabgp -it exabgp -v /etc/exabgp/parse-simple-v4.conf
```

**설정방법**
```
cd /path/to/exabgp
nano conf.ini
```

```
neighbor <ip주소> {
    router-id <ip주소>;
    local-address <ip주소>;
    local-as <AS번호>;
    peer-as <AS번호>;
}
```

**실행방법** 
```
exabgp /path/to/conf.ini
```

**경로 추가/제거를 위한 스크립트**

```
#!/usr/bin/env python3
from sys import stdout
from time import sleep

messages = [
    'announce route 100.10.0.0/24 next-hop self',
    'announce route 200.20.0.0/24 next-hop self',
]

for message in messages:
    stdout.write(message + '\n')
    stdout.flush()
    sleep(1)

while True:
    sleep(1)

```

**ExaBGP 실행**
-> conf.ini 파일을 업데이트하여 ExaBGP 시작 시 Python 스크립트를 실행하도록 설정
```
process announce-routes {
    run /path/to/python3 /path/to/example.py;
    encoder json;
}
```
