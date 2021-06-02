import hashlib #해시 함수
import secrets #CSPRNG
import sys


passwd = input('enter password :')

with open("salt.txt", 'rt',encoding = 'utf-8') as f:
    salt = f.readline()

salt = salt.strip()

passwd +=salt

encoded_string = passwd.encode()
KEK = hashlib.shake_128(encoded_string).hexdigest(8)
print(salt)
print(KEK.upper())