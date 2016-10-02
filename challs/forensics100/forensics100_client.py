import socket, struct

t = ("127.0.0.1", "4005")
o = ['flag', 'dbug']
L = 192

def key():
    with open('forensics100.jpg', 'rb') as f:
        f.seek(0x1337)
        _ = f.read(64)
    return _

def main():
    try: 
        k = key()
        s = socket.create_connection(t)
        l = struct.pack('I', len(k) + len(bytes(o[0])))
        c = bytes(''.join(_ for _ in [l, k, o[0]]))
        s.sendall(c)
        r = s.recv(L, socket.MSG_WAITALL)
        print r
    except Exception, e:
        print(e)
        exit(1)

main()

