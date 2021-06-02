import hashlib #해시 함수
import secrets #CSPRNG
import sys

passwd = input('enter password :')
salt = secrets.token_hex(8)
CEK = secrets.token_hex(8)
passwd += salt.upper()

encoded_string = passwd.encode()
KEK = hashlib.shake_128(encoded_string).hexdigest(8)

#print(KEK+" "+session_key )
with open("KEK.txt", 'wt',encoding = 'utf-8') as f:
    f.write(KEK.upper())

with open("CEK.txt", 'wt',encoding = 'utf-8') as f:
    f.write(CEK.upper())

with open("salt.txt", 'wt',encoding = 'utf-8') as f:
    f.write(salt.upper())