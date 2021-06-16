from OpenSSL.crypto import load_privatekey, FILETYPE_PEM, sign, load_publickey, verify, X509
from Crypto.Hash import SHA256 as SHA
from Crypto.Cipher import AES
from OpenSSL import crypto
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QMessageBox
import sys
pkey = crypto.PKey()
pkey.generate_key(crypto.TYPE_RSA, 1024) # RSA 형식의 키 생성
# 공개키, 개인키 생성
#with open("public.pem", 'ab+') as f:
#    f.write(crypto.dump_publickey(crypto.FILETYPE_PEM, pkey))
#with open("private.pem", 'ab+') as f:
#    f.write(crypto.dump_privatekey(crypto.FILETYPE_PEM, pkey))
# 공개키, 개인키 읽어오기
with open("private.pem", 'rb+') as f:
    priv_key = crypto.load_privatekey(crypto.FILETYPE_PEM, f.read())
with open("public.pem", 'rb+') as f:
    pub_key = crypto.load_publickey(crypto.FILETYPE_PEM, f.read())
# 데이터 해시화
content = '_message' # 가져와야 하는것
_hash = SHA.new(content.encode('utf-8')).digest() # 데이터 해시화


#개인키로 전자서명
_sig = sign(priv_key, _hash, 'sha256') # 개인키로 해시화 되어 있는 데이터의 전자서명 생성
print(_sig)
x509 = X509() # 인증서를 사용할 수 있도록 하는 메서드 제공
x509.set_pubkey(pub_key)
# 비교 대상
cc2 = '_message'
t_hash = SHA.new(cc2.encode('utf-8')).digest()
# 사용법: verify(x509, 전자서명, 비교할 해시, 'sha256')
try:
    verify(x509,_sig,t_hash,'sha256')
    app = QtWidgets.QApplication(sys.argv)
    QMessageBox.information(None, 'Success!', u"변조되지않았습니다.", QMessageBox.Ok)
    sys.exit(1)
except:
    app = QtWidgets.QApplication(sys.argv)
    QMessageBox.critical(None, 'Error!', u"변조되었습니다.", QMessageBox.Ok)
    sys.exit(1)



