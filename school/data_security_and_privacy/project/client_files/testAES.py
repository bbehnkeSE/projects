from encrypt import AESEncrypt
from Crypto.Random import get_random_bytes

key = get_random_bytes(32)
aesObject = AESEncrypt(key)

with open("gui.py", 'rb') as file:
    binData = file.read()

    encryptedFile = aesObject.encrypt(binData)

print(f'encrypted: {encryptedFile}')
print(f'decrypted: {aesObject.decrypt(encryptedFile)}')