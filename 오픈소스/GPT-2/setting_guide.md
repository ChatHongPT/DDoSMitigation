**실습환경**

- Python 3.5
- Tensorflow 1.13.1 version

# prerequesite : I have docker installed on my machine 

$ docker pull python:3.5
$ docker run -it python:3.5 bash

# at this point, you should be in a docker python3.5 environment 

$ git clone https://github.com/openai/gpt-2.git && cd gpt-2

$ pip install -r requirements.txt 

$ python3 download_model.py 124M

$ python3 download_model.py 355M

$ python3 download_model.py 774M

$ python3 download_model.py 1558M

$ pip install tensorflow==1.13.1 # not 1.12 since it no longer works

# and finally we can execute the script 

$ python3 src/interactive_conditional_samples.py --top_k 40
