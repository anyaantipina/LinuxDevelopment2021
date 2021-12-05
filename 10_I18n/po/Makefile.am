pkgdata_DATA = ru_RU.UTF-8/LC_MESSAGES/guess_the_number.mo
ru_RU.UTF-8/LC_MESSAGES/guess_the_number.mo: ru.po
	mkdir -p `dirname $@`
	msgfmt $< -o $@

ru.po:	messages.pot
	msgmerge -U $@ $<

messages.pot:	guess_the_number.pot ../src/guess_the_number.c
	xgettext -k_ -c ../src/guess_the_number.c -o messages.new.pot
	cp guess_the_number.pot messages.pot
	msgmerge -U messages.pot messages.new.pot