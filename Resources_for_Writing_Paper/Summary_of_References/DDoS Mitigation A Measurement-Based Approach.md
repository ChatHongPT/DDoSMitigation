소개
- 현대 사회는 인터넷 통신에 크게 의존하고 있지만, DDoS 공격 등의 위협에 노출되어 있음
- DDoS 문제에 대한 상황 인식을 높이고, 효과적인 방어 대책 마련이 필요함

주요 기여
1. DDoS 공격 특성화
![Pasted image 20240508212733.png](./DDoS%20Mitigation%20A%20Measurement-Based%20Approach/Pasted%20image%2020240508212733.png)
- 2년 동안 약 2,100만 건의 공격 관측, 활성 /24 네트워크의 1/3 이상이 공격 대상
- 관찰된 웹사이트의 64%가 공격 대상이었음

3. 완화 솔루션의 채택 및 운영 현황 파악  
![Pasted image 20240509135221.png](./DDoS%20Mitigation%20A%20Measurement-Based%20Approach/Pasted%20image%2020240509135221.png)
- 클라우드 기반 보호 서비스 사용이 1.5년간 1.24배 증가

![Pasted image 20240509142754.png](./DDoS%20Mitigation%20A%20Measurement-Based%20Approach/Pasted%20image%2020240509142754.png)
- BGP Blackholing의 84.2%가 10분 이내에 자동 활성화되는 등 대체로 자동화된 대응
![Pasted image 20240509143058.png](./DDoS%20Mitigation%20A%20Measurement-Based%20Approach/Pasted%20image%2020240509143058.png)
- 보통 하루 내에 자동 비활성화 되지만, 3.9%는 그 이상이 걸려, 부작용(자체 DoS)이 존재

4. 완화 솔루션의 숨겨진 위험요소 조사
- 40.5%의 웹사이트에서 DNS 구성 오류로 직접 서버에 접근하는 방법으로 보호 서비스 우회 가능
- 843개 웹사이트가 실제 공격 받은 사실 발견

다양한 데이터 소스 활용
![Pasted image 20240508195522.png](./DDoS%20Mitigation%20A%20Measurement-Based%20Approach/Pasted%20image%2020240508195522.png)
- UCSD 네트워크 망원경, AmpPot 허니팟으로 공격 데이터 수집
- OpenINTEL DNS 측정 데이터로 웹사이트-IP 매핑 및 완화 솔루션 사용 유추
- BGP 라우팅 데이터로 Blackholing 이벤트 추적

결론 
- 대규모 데이터 분석을 통해 DDoS 실태와 완화 솔루션 운영 현실 구체화
- 인터넷 보안 강화 및 DDoS 문제 인식 제고에 기여
- 네트워크 운영자, 연구자, 정책입안자에게 유용한 정보 제공