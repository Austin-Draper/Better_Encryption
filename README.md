# Better_Encryption
This is a program utilizing Qt and C++ to create a basic encryption.  
If you want to see the code for yourself, download the Better_Encryption folder and place it into your Qt projects folder.  
From there simply run Qt and open the project.  
The Better_Encryption_Release folder is there if you just want to run the project yourself without needing to open Qt.  
Download the Better_Encryption_Release folder and open it, then open the "release" folder, then run "Encryption.exe". 
##
## Running the Program
After running the program in Qt or using Encryption.exe, you are prompted with two buttons "Encrypt" and "Decrypt".  
First you will click "Encrypt".  
You are now prompted to navigate to a text file or word document to encrypt.    
I recommend creating a new text document and filling it with a few random sentences to test this program.  
Select the file you wish to encrypt and the program will take the contents of that file, encrypt them, and put them back into the same file.  
After a few seconds, check the file and verify it has been encrypted. Scroll down past all the numbers to see the actual encrypted message. 
Now click on the "Decrypt" button and decrypt the same file you just encrypted. 
Check the decrypted file and it should be back to normal. 
##
## TODO
1. The encryption time varies multiple seconds so it's hard to tell when the encryption is actually done. A "waiting" screen while encrypting followed by a "completed" screen when finished would mitigate this issue.

2. Decrypt fails if 2 scenarios occur. The first is if new line "\n" isn't the final character in decrypt vector, but measures have been taken to make this possibility nearly zero. The other scenario is if the first line of the file to be decrypted is 100% numbers without a single other character. In this scenario the encrypt will go through just fine, but if the first line that is encrypted ends up being only numbers then the program will crash. The odds of this occurring are very low unless the first line of the file only has 2 or 3 characters.

3. There are many ways to increase the strength of the encryption that were not taken in this program. This program was meant to be a learning experience getting used to programming in Qt. This project is relatively basic but does provide a good foundation to build up a stronger and more elaborate encryption program off of it.
