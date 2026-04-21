import socket
import time

def flood():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

    print("Generating traffic spike...")

    for _ in range(50000):
        sock.sendto(b'hello', ("127.0.0.1", 9999))

    print("Done")

if __name__ == "__main__":
    flood()