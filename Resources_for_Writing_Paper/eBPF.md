# eBPF (Extended Berkeley Packet Filter)
eBPF란? 다양한 명령어 체계, 실행 환경을 리눅스 커널에서 제공하는 시스템이다.<br>
커널 단에 프로그래머가 원하는 프로그램을 적용할 수 있게 하자는 것이 기본적인 목적이다.<br>

## eBPF 실행 과정
1. 개발자가 고수준 프로그래밍 언어를 통해 코드를 구성한다.<br>
2. LLVM/clang 을 통해 프로그램을 커널에서 작동할 코드를 생성한다. [user space] 에서의 동작에 있어서 핵심은 컴파일이라고 보면 된다.<br>
3. 적용할 코드를 실제로 커널 단에 삽입하고 실행하는 과정에서는 ELF eBPF loader가 관여하는데, 컴파일을 통해 생성된 eBPF ELF 파일에 내재된 일련의 메타 데이터가 제공해주는 정보를 토대로 동작한다.<br>
4. [kernel space] 에서는 위 [user space] 로부터 받은 BPF 코드르 실제로 동작을 요구할 커널 요소에 적용하기 위한 일련의 검증, 컴파일 과정을 실시한다.
   커널 공간에 삽입할 코드에 대한 검증은 'Verifier'가 담당하며 관련 알고리즘은 엄격한 기준을 갖고 있다는 점이 특징이다.<br>
5. 이후 'JIT compiler'를 통해 kernel 단에서 작동할 수 있는 기계어로 변환후 실제로 eBPF 프로그램을 원하는 커널 Hook에 본격적으로 부착할 수 있게된다.<br><br>

![image](https://github.com/DDoSMitigation/main/assets/45961274/232b32ef-f13a-42c4-9f8b-a51991921105)
