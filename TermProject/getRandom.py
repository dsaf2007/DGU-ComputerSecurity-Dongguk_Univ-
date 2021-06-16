import hashlib #해시 함수
import sys
import time
import random
from datetime import datetime
import time
import math

class HashRandom:
    def __init__(self,min,max,seed):
        self.min = min
        self.max = max
        self.seed = int(seed)
    def getRandDec(self):#10진수 형태의 정수형 난수 생성
        seed_str = str(self.seed)
        seed_enc = seed_str.encode()
        random_hash = hashlib.shake_128(seed_enc).hexdigest(1) #16자리 해시값 생성
        self.seed = self.seed + 1
        rand_max = int("FF",16)
        random_num = (int(random_hash,16) / (rand_max + 1)) # 0~1 사이 소수로 변환
        #random_num = ((random_num)*(((self.max +1)-self.min))+self.min)
        #random_num = (int(random_hash,16)%(((self.max +1)-self.min))+self.min)
        return int(random_hash,16)

rnd = HashRandom(0,255,time.time())

array = []
num_array =[]

for i in range(0,256):
    num_array.append(0)

for i in range(0,50000):
    array.append(rnd.getRandDec())

#for i in range(0,1000000):
#    for x in range(0,256):
#        if array[i] == x:
#            num_array[x]=num_array[x]+1

with open("out.txt", 'wt',encoding = 'utf-8') as f:
    #for i in range(0,256):
        #f.write(str(i)+":"+str(num_array[i])+"\n")
    for i in range(0,50000):
        f.write(str(array[i])+"\n")
