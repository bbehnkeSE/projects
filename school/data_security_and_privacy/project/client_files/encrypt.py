import hashlib
import os
from Crypto        import Random
from Crypto.Random import get_random_bytes
from Crypto.Cipher import AES
from base64        import b64encode, b64decode

import string
import random


class AESEncrypt(object):
    def __init__(self, key):
        self.blockSize = AES.block_size
        self.key = hashlib.sha256(key).digest()

    def pad(self, plainBytes):
        padBytesNum = self.blockSize - len(plainBytes) % self.blockSize
        asciiStr = chr(padBytesNum)
        padBytes = padBytesNum * asciiStr.encode()
        result = plainBytes + padBytes

        return result

    @staticmethod
    def unpad(plainBytes):
        lastChar = plainBytes[len(plainBytes) - 1:]
        padBytes = ord(lastChar)

        return plainBytes[:-padBytes]

    def encrypt(self, plainBytes):
        plainBytes = self.pad(plainBytes)
        iv = Random.new().read(self.blockSize)
        cipher = AES.new(self.key, AES.MODE_CBC, iv)
        cipherBytes = cipher.encrypt(plainBytes)

        return b64encode(iv + cipherBytes).decode('utf-8')

    def decrypt(self, cipherText):
        cipherText = b64decode(cipherText)
        iv = cipherText[:self.blockSize]
        cipher = AES.new(self.key, AES.MODE_CBC, iv)
        plainBytes = cipher.decrypt(cipherText[self.blockSize:])

        return self.unpad(plainBytes)


def generateSecretKey(username):
    os.chdir(f'secret_keys/{username}')

    with open('key.txt', 'wb') as file:
        file.write(get_random_bytes(32))



def generateUsercode(username):
    homedir = os.getcwd()

    try:
        os.mkdir('./secret_keys/', 0o777)
    except:
        print('directory \'secret_keys\' already exists')
    try:
        os.mkdir(f'./secret_keys/{username}', 0o777)
    except:
        print(f'directory \'{username}\' already exists')

    generateSecretKey(username)
    with open('key.txt', 'rb') as file:
        key = file.read()
        
    os.chdir(homedir)

    usercode = string.ascii_lowercase + string.ascii_uppercase + string.ascii_letters + string.digits + string.punctuation
    usercode = ''.join(random.choice(usercode) for i in range(len(usercode)))

    for _ in range(random.randint(1, 3)):
        usercode += ''.join(random.choice(usercode) for i in range(len(usercode)))

    aesObj = AESEncrypt(key)
    encryptedUsercode = aesObj.encrypt(usercode.encode())

    return encryptedUsercode, usercode
