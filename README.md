recovery
========

recovers images from damage storage card.

recovery.c is a program that scans a file, preferably a damaged sd card or any storage that has photos, and searches the medium for jepg files by looking for a 4 byte identifier that signifies the start of a jpeg file. Once it finds the identifier, the program begins writing the initial four bytes as well as the trailing bits to a new file until it runs into a another set of identifing bytes, In which case it saves and closes the current file and opens and begins writing to a new file.

This program stops running when the program reaches the end of the file. This is only useful in the case that photos only exist on the specified medium and the photos are jpeg images.

This program was built for an online curriculm.
