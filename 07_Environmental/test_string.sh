# check SHA1 and HEX format
echo -n "string" | sha1sum | cut -d " " -f1 | awk '{print toupper($0)}' > template.txt
echo "SHA1 \"string\"" | ./rhasher | head -n1 | tail -n1 | cut -d " " -f2 &>tmp ; cmp tmp template.txt

# check SHA1 and BASE64 format
echo -n "string" | sha1sum | cut -d " " -f1 | xxd -r -p | base64 > template.txt
echo "sha1 \"string\"" | ./rhasher | head -n1 | tail -n1 | cut -d " " -f2 &>tmp ; cmp tmp template.txt

# check MD5 and HEX format
echo -n "string" | md5sum | cut -d " " -f1 | awk '{print toupper($0)}' > template.txt
echo "MD5 \"string\"" | ./rhasher | head -n1 | tail -n1 | cut -d " " -f2 &>tmp ; cmp tmp template.txt

# check MD5 and BASE64 format
echo -n "string" | md5sum | cut -d " " -f1 | xxd -r -p | base64 > template.txt
echo "md5 \"string\"" | ./rhasher | head -n1 | tail -n1 | cut -d " " -f2 &>tmp ; cmp tmp template.txt
