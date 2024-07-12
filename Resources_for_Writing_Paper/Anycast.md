# Anycast

Anycast란?
거리 상으로 
인접한 노드와 통신하는 것을 말한다.

![Pasted image 20240508180333](https://github.com/DDoSMitigation/main/assets/45961274/49e331a2-5f07-4f2f-9c7d-4c0e78fdad27)

| 방식 | Unicast | Multicast | Broadcast | Anycast |
| ----- | ----- | ----- | ----- | ----- |
| 대상 | 특정 단일 | 특정 다수 | 불특정 다수 | 인접한 노드 |
| 규모 | 1대 1 | 1대 다 | 1대 다 | 1대 1 |
| 사용 | 특정 대상 하나에게 통신 하려는 경우 사용 | 특정 대상들에게 통신 하려는 경우 사용 | 특정 노드를 찾거나 모든 클라이언트 대상으로 통신할 때 사용 | DDoS 공격 예방 책으로 트래픽을 분산 시키거나 각 다른 국가간 서비스 제공 시 속도 차이를 줄이기 위해 사용 |

다른 통신 방식의 차이점
