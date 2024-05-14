**BGP-Anycast Tuner**:
   - 설명: BGP anycast 환경에서 라우팅 경로 최적화를 위한 도구.
   - 기능 특징: BGP 라우팅 경로 분석, anycast 대상 선택 최적화.
   - 장단점:
     - 장점: BGP anycast 네트워크의 성능을 향상시키는데 유용.
     - 단점: 설정 및 튜닝에 대한 이해가 필요.
# **설치 가이드**
1. `Dockerfile`이 있는 경로로 이동한다.

2. 다음 명령어로 Dockerfile로 Image를 Build한다.
```
docker build -t bgp-anycast-tuner .
```

3. 다음 명령어로 Build한 Image로 Container를 생성 및 실행한다.
```
docker run -p 12445:12445 bgp-anycast-tuner
```

4. Terminal에 출력된 주소인 `http://127.0.0.1:12445`로 접속하여 BGP-Anycast-Tuner를 확인한다.