# Password_Generator
Simple password generator constructed in C.

This is a password generator that can generate a random and secure password fast and easy. In this program you are able to specify how do you want the password to be (lower letters, symbols, upperletters and numbers).

i will be adding more features to the program later since it is a practice project that im building just to get more skilled with the c language.

Any help or contributions to the project will be welcome :).


---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

sunday 01, 10, 2023

I added to features:
-Generate custom amount of passwords at the same time
-Save those passwords in a txt file.

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

wednesday 04, 10, 2023

Changes:
-Now you use the program from the command line using arguments. I added a documentation just executing the program or with passwd-gen.exe -h

---------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

saturday 27, 04, 2024

Changues:
- Fixed several issues:
  - The passwords matrix its initializated estatically and generates a compilation error (fixed)
  - The pass_type list filled with null values causes any function reading the variable to stop his execution everytime it gets to a "/0x00" (null) byte (fixed, filling the pass_type variable with int "1")
 
*Now everything works as intended and this is probably the last commit i'll do to this repository, hope you enjoy it*
