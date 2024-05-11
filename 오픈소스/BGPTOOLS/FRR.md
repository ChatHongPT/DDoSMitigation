**설치방법**
```
curl -s https://deb.frrouting.org/frr/keys.gpg | sudo tee /usr/share/keyrings/frrouting.gpg > /dev/null

FRRVER="frr-stable"
echo deb '[signed-by=/usr/share/keyrings/frrouting.gpg]' [https://deb.frrouting.org/frr](https://deb.frrouting.org/frr) \
     $(lsb_release -s -c) $FRRVER | sudo tee -a /etc/apt/sources.list.d/frr.list
     
sudo apt update && sudo apt install frr frr-pythontools
```

BGP 설정방법
```
cd /etc/frr/daemons
sudo vi daemons (bgpd=no를 yes 로 변경)
```
![](img/FRR.png)

sudo vtysh

