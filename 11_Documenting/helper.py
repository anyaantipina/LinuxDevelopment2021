import roman

for i in range(1, 101):
    print("if (!strcmp(roman_number, \"%s\")) return \"%d\";" % (roman.toRoman(i), i))