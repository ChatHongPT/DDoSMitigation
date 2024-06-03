# 기본 이미지 설정
FROM tensorflow/tensorflow:1.12.0-gpu-py3

# 작업 디렉토리 설정
WORKDIR /gpt-2

# 필요한 패키지 설치
RUN apt-get update && apt-get install -y \
    git

# Git 클론 및 작업 디렉토리 이동
RUN git clone https://github.com/openai/gpt-2.git && cd gpt-2

# 추가 패키지 설치
RUN pip3 install -r requirements.txt

# 모델 데이터 다운로드
RUN python3 download_model.py 124M
RUN python3 download_model.py 355M
RUN python3 download_model.py 774M
RUN python3 download_model.py 1558M

# 환경 변수 설정
ENV PYTHONIOENCODING=UTF-8

# 컨테이너 실행 시 실행될 명령 설정
CMD ["bash"]
