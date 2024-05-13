**실습환경**

- OS : Ubuntu 18.04(Python을 사용하기 때문에 다른 환경에서도 잘 동작할 것임)
- Python 3.7
- Tensorflow 1.15 version

소스 다운로드 및 라이브러리 설치

**1. Source Download**

- Git으로 소스를 다운로드 하고 폴더를 이동한다.

![image](https://github.com/DDoSMitigation/main/assets/129854575/50c315f6-d661-436d-8eca-741d128f335e)

**2. Create the venv environment and install the library**

- venv를 만들고 pip를 업데이트
  
![image](https://github.com/DDoSMitigation/main/assets/129854575/94c25395-b4e0-4c78-85ae-87a2c1925713)

- GPT-2 github에서 tensorflow 1.12 version을 지향하였으나, 실제로 1.12 version을 설치하게되면 에러가 발생
- 그러므로 1.15 version을 설치하고 나머지 필요한 라이브러리를 설치함
  
![image](https://github.com/DDoSMitigation/main/assets/129854575/973dba6d-f4fb-4375-9c73-7fd5ace2c870)

**3. Download Models**

모델을 다운로드하는 스크립트를 실행, 파일을 다운로드 받는데 시간이 오래 걸릴 수 있어서 테스트에 사용할 모델만 선택해서 받아도됨.
![image](https://github.com/DDoSMitigation/main/assets/129854575/a4ef8284-5f13-4529-9bdc-9979605283a4)

**4. RUN**

아래 명령어를 사용하여 interactive sample을 실행시키게 되면 직접 문장을 넣어 보면서 AI로 작문한 결과를 확인 가능
![image](https://github.com/DDoSMitigation/main/assets/129854575/8dae1847-4aa0-464e-ad27-a9c845904e17)


