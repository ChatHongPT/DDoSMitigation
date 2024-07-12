# XDP (eXpress Data Path)
XDP란 eBPF 안에 포함된 프로그램 타입중의 하나로, 전통적인 Packet Data를 처리하는 것에서 벗어나 특별한 방법으로 접근하는 방식이라고 보면 된다.<br>
Packet Data를 처리함에 있어서 운영체제의 방식은 다양한 기능을 제공하지만, 그만큼 처리 과정의 효율성과 같은 부분을 재고할 여지가 있다.<br>
이에 따라 kernel bypass를 구현한 기능(DPDK와 같은 toolkit)이 구현된 바도 있지만, 다양한 모듈을 제공받는 방식에서 벗어나 다이나믹하게 특정 하드웨어 장치와 연결하는 방식은 그만큼 포기해야하는 기능도 있다는 점이다.<br>
이러한 단점을 극복하면서 효율적인 Data 처리 방식을 고안한 것이 XDP 라고 보면 된다.<br>

## 처리 방식
XDP 프로그램은 네트워크 디바이스 드라이버에서 제공하는 XDP Hook에 의해 동작할 수 있다. <br>
Hook에 부착된 XDP 프로그램은 특정 이벤트에 대해실행된다. <br>
XDP가 특정 이벤트에 대해 실행된다고 했을때의 핵심은 바로 kernel이 해당 Frame data를 처리하기 전의 과정이라고 생각하면 된다. <br>
전송된 Frame data는 물리 네트워크 장치를 타고 디바이스 드라이버를 통해 커널로 전달되며, 커널은 해당 패킷을 기존의 Network Stack을 통해 처리한다. <br>
그러나 XDP 프로그램이 동작하면 디바이스 드라이버 단에서 해당 Frame data의 처리를 직접적으로 수행할 수 있다. <br><br>
![image](https://github.com/DDoSMitigation/main/assets/45961274/1744f1a4-ac57-47a4-9e44-7bba179f4f5c)
