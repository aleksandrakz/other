artistPairs by Aleksandra Zakrzewska
October 15, 2014
A function to print any artist names that appear together in at least 50 lines of a given input

To run:
Call ./artistPairs <FILENAME in the terminal



Algorithm Description:

I process the input by reading in characters and saving them into a string (called artist) if they are not a comma, newline or EOF. When one of these appears, the string is put into an array of of all the names in that line, called line. In order to manage memory, I make the assumption that the artist name will have no more than 30 characters. This may lead to some names being cut off, but it is very unlikely that two artists have the same first 30 characters, so the names will still be distinguishable and recognizable. This shortcut allows me not to have to process the input twice — once to find the length of a name and once to input it— or to have to realloc storage multiple times to account for different sizes. At the end of the line (at a newline or EOF), I pause processing, and input all the pairs of names into a tree.
I use a tree to make search and insertion faster. As we want to keep a count of all the inserted pairs, we have have to find each artist name before inserting it. Using a binary tree structure makes the runtime of this operation decrease from O(N) to O(logN).
The insertion of pairs is done with a double for loop. In order to avoid duplicates being inserted into the tree, only pairs where the first name is < the second name are inserted. The tree they are being inserted into is a binary search tree with a sub binary search tree nested at each node. So name A is inserted in the the main tree, and then name B is inserted into the subtree nested at A. In this way, if B ever appeared with A in a line, B is in A’s subtree. A is not in B’s subtree because A<B. During insertion into the subtree, if the Count associated with B (which is incremented every time A and B appear together) reaches 50, the pair is printed. 
After all the name pairs from a line are inserted, the next line is read in and processed.
Once all the lines have been read in, I free all the storage by destroying the trees and freeing all of their elements.
The binary search trees perform rotations to balance if an insertion causes them to be unbalanced (height of one child > 1 + height of other child), so that insertion always takes log(N) time, where N is the number of nodes in the tree.

Runtime: 
Input processing runs in O(N), where N is the length of each line, because each character must be copied
Finding the pairs runs in O(N^2), where N is the number of artists in a line, because of the double for loop needed to pair each name with every other name in its line
Inserting into the tree takes O(log(N)) time, where N is the number of elements in the tree, because the tree is always height balanced. This is done twice for each pair insertion.
So, if:
s= number of artists in a line (max = 50)
u = total distinct names of artists
n = number of lines
The total runtime is :(s^2 * log(u)) * n)


Space Complexity: 
Each tree uses O(N) to store the N different possible artist names.
Assuming that all of the names appear in a list with every other name, the max elements in sub trees would be an average of N/2 elements rooted at each node of the main tree. This makes the upper bound of the storage used by the trees together be O((N^2) /2).   


Tested on: 
OS X 10.9.5 (13F34) (gcc version: (clang-600.0.51)) 
(Configured with: --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
Apple LLVM version 6.0 (clang-600.0.51) (based on LLVM 3.5svn)
Target: x86_64-apple-darwin13.4.0
Thread model: posix))

Linux version 3.10.0-123.8.1.el7.x86_64 (mockbuild@x86-025.build.eng.bos.redhat.com) (gcc version 4.8.2 20140120 (Red Hat 4.8.2-16)
)
Linux version 3.2.0-27-generic (buildd@allspice) (gcc version 4.6.3 (Ubuntu/Linaro 4.6.3-1ubuntu5)

