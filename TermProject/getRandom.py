import hashlib #해시 함수
import sys
import time
import random
from datetime import datetime
import math

class HashRandom:
    def __init__(self,size,seed):#size == 출력할 16진수형 난수의 길이
        self.size=size/2
        self.seed = int(seed)
    def getRand(self):#16진수 형태의 정수형 난수 생성
        seed_str = str(self.seed)
        seed_enc = seed_str.encode()
        random_hash = hashlib.shake_128(seed_enc).hexdigest(int(self.size)) #16자리 해시값 생성
        self.seed = self.seed + 1
        #rand_max = int("FF",16)
        #random_num = (int(random_hash,16) / (rand_max + 1)) # 0~1 사이 소수로 변환
        #random_num = ((random_num)*(((self.max +1)-self.min))+self.min)
        #random_num = (int(random_hash,16)%(((self.max +1)-self.min))+self.min)
        return str(random_hash)

nonce = HashRandom(8,time.time())


with open("nonce.txt", 'wt',encoding = 'utf-8') as f:
    f.write(nonce.getRand().upper())

rnd = HashRandom(16,time.time_ns())
salt = rnd.getRand().upper()
with open("salt.txt",'wt',encoding='utf-8') as f:
    f.write(salt)

passwd = input('enter password :')
passwd +=salt

CEK = rnd.getRand().upper()

passwd = passwd.encode()
KEK = hashlib.shake_128(passwd).hexdigest(8)


with open("KEK.txt", 'wt',encoding = 'utf-8') as f:
    f.write(KEK.upper())

with open("CEK.txt", 'wt',encoding = 'utf-8') as f:
    f.write(CEK)

#난수의 균일성 검증
#for i in range(0,256):
#    num_array.append(0)

#for i in range(0,50000):
#    array.append(rnd.getRandDec())
#for i in range(0,1000000):
#    for x in range(0,256):
#        if array[i] == x:
#            num_array[x]=num_array[x]+1

#with open("out.txt", 'wt',encoding = 'utf-8') as f:
    #for i in range(0,256):
        #f.write(str(i)+":"+str(num_array[i])+"\n")
    #for i in range(0,50000):
     #   f.write(str(array[i])+"\n")
