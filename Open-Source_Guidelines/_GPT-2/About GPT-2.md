# GPT-2

GPT-2는 input 값과 수행되어야할 Task 정보까지를 입력으로 받아 학습된다.

![image](https://github.com/DDoSMitigation/main/assets/129854575/3ee99a1d-aaab-4e30-ba01-6ca2c6927416)


"How are you?"라는 문장에서 "translate to Korean"이라는 문장까지 함께 Input으로 주어 학습을 진행한다. 

이때 "translate to Korean"는 하나의 토큰으로 주어진다. (이때부터 슬슬 프롬프트가 주어진다.)

또 다른 테스크로 Q&A 역할을 하는 모델을 만들기 위해 아래 그림처럼 Question과 Answer이라는 스페셜한 token을 사용하여 학습한다.

![image](https://github.com/DDoSMitigation/main/assets/129854575/335b3cba-8942-4247-81a2-1f58f1f0a66c)


GPT1과 GPT2의 차이

- GPT1과 GPT2는 모두 Transformer의 디코더 아키텍처를 기반으로 한다.

- GPT-2는 GPT-1보다 더 많은 decoder 블록을 쌓아 올렸으며 GPT-1보다 학습되는 파라메터수가 10배 이상이며, 학습에 사용된 데이터셋도 훨씬 크며 이 때문에 더욱 자연스러운 텍스트 생성이 가능하다.

|  | GPT-1 | GPT-2 |
| --- | --- | --- |
| parameters | 117 millions | 1.5 billions |
| layers | 12 | 48 |
| States dimension | 768 | 1600 |
| Context token size | 512 | 1024 |
| Batch size | 64 | 512 |
| etc |  | Layer normalization moved to the input of each sub block Layer normalization added after the final self attention block |
