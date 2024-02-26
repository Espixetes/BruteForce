
# BruteForce

 The program implements file decryption using the  [OpenSSL](https://github.com/openssl/openssl/tree/OpenSSL_1_0_2-stable) 
 
 First, the program reads the text from the file .Then the number of passwords is counted **AmountPassword()**. The passwords are then evenly distributed among the threads, and the function **BruteForce()** is run. After that, passwords are created in the **PassPack()**.Passwords are written to a file.The text is decrypted and the decrypted text is written to the file.

### **The program uses libraries from [OpenSSL](https://github.com/openssl/openssl/tree/OpenSSL_1_0_2-stable)**
    + openssl/evp.h
    + openssl/aes.h
    + openssl/sha.h

### **Files**
+ main - *Starting point*
+ BruteForceSetting - *Getting Settings*
+ cryptography - *Working with keys and text decryption*
+ fileHandling - *Working with Files*
+ BruteForceEngine - *creating keys, causing keys to be written to a file, causing the text to be decrypted with these keys*