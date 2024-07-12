# 지도환 - Understanding the Behaviors of BGP-based DDoS Protection Services
소개  
BGP 기반 DDoS 보호 서비스(DPS)의 동작에 대한 이해에 관한 연구를 제시

주요 기여  
1. BGP 업데이트 메시지를 분석하여 DDoS 이벤트를 식별하는 머신러닝 기반 방법. 이는 BGP 데이터에서 특징을 추출하고 이상 징후를 탐지하며 DDoS 공격을 재해와 같은 다른 이벤트와 구별할 수 있도록 분류기를 훈련하는 것을 포함한다.
	![Pasted image 20240508193845.png](./Understanding%20the%20Behaviors%20of%20BGP-based%20DDoS%20Protection%20Services/Pasted%20image%2020240508193845.png)
	![Pasted image 20240508193934.png](./Understanding%20the%20Behaviors%20of%20BGP-based%20DDoS%20Protection%20Services/Pasted%20image%2020240508193934.png)
  
2. BGP 기반 DPS 제공자가 BGP를 활용하여 디도스 공격을 일단 검출하면 이를 완화하는 방법에 대한 분석이다. 여기에는 피해 프리픽스에 대해 DPS 제공자가 채택한 특정 BGP 정책을 자동으로 추출하는 알고리즘이 포함된다.
	![Pasted image 20240508194303.png](./Understanding%20the%20Behaviors%20of%20BGP-based%20DDoS%20Protection%20Services/Pasted%20image%2020240508194303.png)
  
3. DDoS 탐지 접근법과 완화 정책 분석을 결합한 시스템 구현 2016년 Dyn 공격과 같은 실제 DDoS 공격 사례에 대해 평가한다.
	![Pasted image 20240508194157.png](./Understanding%20the%20Behaviors%20of%20BGP-based%20DDoS%20Protection%20Services/Pasted%20image%2020240508194157.png)

결론  
BGP 데이터로부터 DDoS 공격을 탐지하고 DPS 제공자가 BGP 메커니즘을 활용하여 식별되면 그러한 공격을 완화하는 방법을 이해하기 위한 데이터 기반 접근법을 제안