- **AS-Path Prepending**: Routing 경로를 설정하여 트래픽을 원하는 경로로 유도하는 방법, 트래픽이 집중되거나 여러 곳으로 분산 시킬 수 있음

- **BGP Communities (Community Strings)**: BGP Route에 정보를 Labeling하여 AS들이 Routing 정책을 제어할 수 있게 하는 방법, AS들은 이 정보를 바탕으로 특정 정책을 식별하고 적용할 수 있음

- **Path Poisoning**: Routing Loop를 생성하여 특정 AS로의 트래픽을 차단하는 방법, 이는 AS PATH에 다른 Carrier의 AS를 추가함

1. BGP를 사용하여 Anycast Routing 제어
2. 알려진 트래픽을 기반으로 액세스 분율 측정
3. DDoS 공격 대응을 위한 Playbook 작성
4. AS-Path prepending의 Anycast 제어 세분성 측정

BGP를 이용해 트래픽을 분산시키고 평상시 흐르는 트래픽을 기반으로 수상한 트래픽이 순식간에 급증하면 Anycast로 연동된 서버로 트래픽을 분산시켜 DDoS 공격을 대응함

한계: DDoS 공격을 완화하기 위해 Routing 경로를 유도하고 차단하는 것일 뿐 완벽하게 처리하지는 못함.