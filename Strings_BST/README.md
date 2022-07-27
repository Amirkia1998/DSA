
# Storing Strings in BST

In this assignment, we are required to design and code 
the algorithm that lists the files in which a given word occurs, 
using a binary search tree.
## Description
An example tree is as shown below.
Access to the binary search 
tree is provided through words. At each node, 
along with the word, there are also the names of
the files in which this word occurs.   

[![img1.jpg](https://i.postimg.cc/tCZ2BcQ9/img1.jpg)](https://postimg.cc/XpWfJQYP)
## Process
Perform the following operations on the Binary Search Tree:   
- **Adding** a new file: For each word found in a given file:
    - If the word is not in the binary tree, 
        add the word to the binary search tree in a way 
        that does not break the sequential access, and keep the information of which file it is in the structure of the node of this word.
    - If the word is in the binary tree, 
        check if the name of this file is in the 
        corresponding node, if not, add the filename.
- File **Deletion**: When the file name to be deleted is given, 
  the status of the words in this file in the 
  binary search tree should also be updated. For
  all words in this file:
    - If the word occurs only in this file, delete the word from the 
      binary search tree so as not to break the sequential access.
    - If there are other files where the word occurs, 
      just delete the name of the file from this node
- Word **Search**: Search the binary search tree for a given word 
  and print the information in which files it occurs.
## Requirements
- Any Text Editor (VSCode, XCode, DevC++)
- GCC Compiler   

## How to Run
Run the commands below on the Path where the File is saved.

 on Linux: 
```bash
gcc Strings_BST.c -o Strings_BST.exe
./Strings_BST
```
on Windows:

```bash
gcc Strings_BST.c -o Strings_BST.exe
Strings_BST.exe
```
on Mac:

```bash
gcc -Wall -o Strings_BST Strings_BST.c
./Strings_BST
```

## Contact 
You can reach me at
amirkia.rafiei@gmail.com
## Authors

- [@Amirkia1998](https://github.com/Amirkia1998)

