#Makefile for Rivendell - Spinitron Update
#Suggested usage: git pull
#                 sudo make install
#
#Compile without installing: make all

INSTALLDIR=/opt/wmfo/rlm_spinitron
OWNER = root
MOD = 755
FILE = rlm_spinitron

.PHONY: all install uninstall

all: $(FILE).rlm

$(FILE).rlm: $(FILE).c
	@gcc -shared -o $@ $< -Wall -Wextra -Werror -fPIC

install: $(INSTALLDIR)/$(FILE).rlm

$(INSTALLDIR)/$(FILE).rlm: $(FILE).rlm
	@cp $< $@
	@chown $(OWNER) $@
	@chmod $(MOD) $@

uninstall:
	$(RM) $(INSTALLDIR)/$(FILE).rlm
