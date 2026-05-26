#!/bin/sh

echo "Hello"

F=$1
echo "Create file with name $F"
echo "Hello world!" > $F 
ls -il $F*
echo "Press enter to continue"
read 

echo "Add x rights to user for $F"
chmod u+x $F 
ls -il $F*
echo "Press enter to continue"
read 

LF=$F"link"
echo "Create hard link to file with name $LF"
ln $F $LF 
ls -il $F*
echo "Press enter to continue"
read 

echo "Remove r rights from groups and others for $LF"
chmod g-r,o-r $LF 
ls -il $F*
echo "Press enter to continue"
read 

echo "Remove original file name $F"
rm $F
ls -il $F*
echo "Press enter to continue"
read 

echo "Remove hard link to file $LF"
rm $LF
ls -il $F*

echo "Bye"
