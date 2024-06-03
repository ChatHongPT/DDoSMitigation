# 우분투 최신 이미지 사용
FROM ubuntu:latest

# 작업 디렉토리를 설정
WORKDIR /app

# 컨테이너로 파일 및 폴더를 복사
COPY bgp-anycast-tuner.py /app/
COPY assets /app/assets
COPY dataset /app/dataset

# apt 업데이트
RUN apt update

## tzdata 설치 및 time-zone 설정
RUN ln -sf /usr/share/zoneinfo/Asia/Seoul /etc/localtime && apt install tzdata

# python, pip 설치
RUN apt install -y python3 python3-pip

# "This environment is externally managed" 오류 제거
RUN python3 -m pip config set global.break-system-packages true

# python 모듈 설치
RUN pip install pandas numpy plotly ipython dash dash-core-components dash-html-components dash-colorscales dash-bootstrap-components

EXPOSE 12445

CMD ["python3", "bgp-anycast-tuner.py"]