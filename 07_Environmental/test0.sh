echo "command not found" > template.txt
echo asd | ./rhasher 2>tmp | &>/dev/null ; cmp tmp template.txt

echo "digest calculation error" > template.txt
echo "sha1 q" | ./rhasher 2>tmp | &>/dev/null ; cmp tmp template.txt