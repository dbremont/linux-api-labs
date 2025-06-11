from scapy.all import rdpcap

# Read the PCAP file
packets = rdpcap('capture.pcap')

# Loop through the packets
for packet in packets:
    # Print packet summary
    print(packet.summary())

    # You can access specific fields, e.g., IP layer
    if packet.haslayer('IP'):
        ip_src = packet['IP'].src
        ip_dst = packet['IP'].dst
        print(f'Source IP: {ip_src}, Destination IP: {ip_dst}')