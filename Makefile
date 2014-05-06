#Makefile for Rivendell - Spinitron Update
#Suggested usage: git pull
#                 sudo make install
#
#Compile without installing: make all

BASE=/opt/wmfo
INSTALLDIR=rlm_spinitron
OWNER = root
MOD = 755
FILE = rlm_spinitron
CREDS = credentials.h
CREDSMOD = 600

SCRIPTDIR=macro_sh

.PHONY: all install uninstall

all: $(FILE).rlm $(CREDS)
	@chown $(OWNER) $(CREDS)
	@chmod $(CREDSMOD) $(CREDS)

$(FILE).rlm: $(FILE).c
	@gcc -shared -o $@ $< -Wall -Wextra -Werror -fPIC
	@chown $(OWNER) $@
	@chmod $(MOD) $@

install: $(BASE)/$(INSTALLDIR)/$(FILE).rlm
	@chmod $(MOD) $(SCRIPTDIR)/* 
	@mkdir -p $(BASE)/$(SCRIPTDIR)
	@cp $(SCRIPTDIR)/* $(BASE)/$(SCRIPTDIR)

$(BASE)/$(INSTALLDIR)/$(FILE).rlm: $(FILE).rlm
	@mkdir -p $(BASE)/$(INSTALLDIR)
	@if [ -f $@ ] ; \
	then \
		cp $@ $@.bak ; \
	fi;
	@cp $< $@
	@chown $(OWNER) $@
	@chmod $(MOD) $@

uninstall:
	@$(RM) $(BASE)/$(INSTALLDIR)/$(FILE).rlm
	@if [ -f $(BASE)/$(INSTALLDIR)/$(FILE).rlm.bak ] ; \
	then \
		cp $(BASE)/$(INSTALLDIR)/$(FILE).rlm.bak $(BASE)/$(INSTALLDIR)/$(FILE).rlm ; \
		$(RM) $(BASE)/$(INSTALLDIR)/$(FILE).rlm.bak ; \
	fi;
