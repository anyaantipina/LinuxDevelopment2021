# НЕТ СОВПАДЕНИЯ
# echo убирает только лишние слешы, sed не находит match, выводит ту же строку
echo ',jhav\s\\bsldhj' > template.txt
echo ",jhav\\s\\\bsldhj" | sed -E 's/sd/substitution/' | cmp template.txt
# esub убирает лишние слешы и диагностирует, что не нашел замену
echo 'regexec failed! regerror=1, No match' > template.txt
./esub 'sd' 'substitution' ',jhav\\s\\\bsldhj' | cmp template.txt

# ОШИБКА В ПАТТЕРНЕ
# echo убирает только лишние слешы, sed выводит ошибку в паттерне
echo "sed: -e expression #1, char 19: unterminated \`s' command" > template.txt
echo ",jhav\\s\\\bsldhj" | sed -E 's/[sd/substitution/' 2>tmp.txt; cmp tmp.txt template.txt
# esub убирает лишние слешы и диагностирует ошибку в паттерне
echo 'regcomp failed! regerror=7, Unmatched [, [^, [:, [., or [=' > template.txt
./esub '[sd' 'substitution' ',jhav\\s\\\bsldhj' | cmp template.txt

# ПАТТЕРН С КАРМАНАМИ И ПУСТОЙ ПОДСТАНОВКОЙ
# echo убирает только лишние слешы, sed заменяет match на пустую строку
echo ",jhav\\\sd\\\bsdldhj" | sed -E 's/([a-z])*([a-z])([a-z])//' > template.txt
# esub убирает лишние слешы, воспринимает карманы, как в расширенных рег-выр и заменяет матч на пустую строку
./esub '([a-z])*([a-z])([a-z])' '' ',jhav\\\sd\\\bsdldhj' | cmp template.txt

# ПАТТЕРН С КАРМАНАМИ И ИХ ПОДСТАНОВКОЙ
# echo убирает только лишние слешы, sed заменяет match на подстановку с карманом
echo ",jhav\\\sd\\\bsdldhj" | sed -E 's/([a-z])*([a-z])([a-z])/==\2\0==/' > template.txt
# esub убирает лишние слешы, воспринимает карманы, как в расширенных рег-выр и заменяет матч на пустую строку
./esub '([a-z])*([a-z])([a-z])' '==\2\0==' ',jhav\\\sd\\\bsdldhj' | cmp template.txt

# ПАТТЕРН С НЕСУЩЕСТВУЮЩИМИ КАРМАНАМИ
# echo убирает только лишние слешы, sed заменяет match на подстановку с карманом
echo "sed: -e expression #1, char 32: invalid reference \4 on \`s' command's RHS" > template.txt
echo ",jhav\\\sd\\\bsdldhj" | sed -E 's/([a-z])*([a-z])([a-z])/==\4==/' 2>tmp.txt; cmp tmp.txt template.txt
# esub убирает лишние слешы, воспринимает карманы, как в расширенных рег-выр и заменяет матч на пустую строку
echo "invalid reference \4" > template.txt
./esub '([a-z])*([a-z])([a-z])' '==\4==' ',jhav\\\sd\\\bsdldhj' | cmp template.txt