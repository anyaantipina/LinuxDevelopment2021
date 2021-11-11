# check SHA1 and HEX format
sha1sum rhasher.c | cut -d " " -f1 | awk '{print toupper($0)}' > template.txt
echo "SHA1 rhasher.c" | ./rhasher | head -n1 | tail -n1 | cut -d " " -f2 &>tmp ; cmp tmp template.txt

# check SHA1 and BASE64 format
sha1sum rhasher.c | cut -d " " -f1 | xxd -r -p | base64 > template.txt
echo "sha1 rhasher.c" | ./rhasher | head -n1 | tail -n1 | cut -d " " -f2 &>tmp ; cmp tmp template.txt

# check MD5 and HEX format
md5sum rhasher.c | cut -d " " -f1 | awk '{print toupper($0)}' > template.txt
echo "MD5 rhasher.c" | ./rhasher | head -n1 | tail -n1 | cut -d " " -f2 &>tmp ; cmp tmp template.txt

# check MD5 and BASE64 format
md5sum rhasher.c | cut -d " " -f1 | xxd -r -p | base64 > template.txt
echo "md5 rhasher.c" | ./rhasher | head -n1 | tail -n1 | cut -d " " -f2 &>tmp ; cmp tmp template.txt
