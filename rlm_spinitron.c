/*
 *  rlm_spinitron.c
 *
 *  Module by Eric Berg, Ben Yu (C) Copyright 2009.
 *  For more copyright and legal information, see TERMS and COPYING.
 *
 *  For documentation, see README.md
 *
 *  For compilation, see the Makefile.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>

#include "rlm.h"
#include "credentials.h" // declares strings USERNAME, PASSWORD, STATION

char old_title[2500];

void rlm_spinitron_RLMStart(void *ptr, const char *arg)
{
    RLMLog(ptr,LOG_WARNING, "Hello! rlm_spinitron_RLMStart has run!");
	strcpy(old_title, "BLAHAHAHAHAHAHAHAH");
	return;
}

void rlm_spinitron_RLMFree(void *ptr)
{
    RLMLog(ptr,LOG_WARNING, "Hello! rlm_spinitron_RLMFree has run!");
	return;
}


void replace_char (char *s, char find, char replace) {
	while (*s != 0) {
		if (*s == find)
			*s = replace;
		s++;
	}
}

void rlm_spinitron_RLMPadDataSent(void *ptr,const struct rlm_svc *svc,
				const struct rlm_log *log,
				const struct rlm_pad *now,
				const struct rlm_pad *next)
{
    RLMLog(ptr, LOG_WARNING, "Data send start!");
	const int BUFFER_SIZE = 2500;
	char title[BUFFER_SIZE];
	char artist[BUFFER_SIZE];
	char album[BUFFER_SIZE];
	strcpy (title, (char *) now->rlm_title);
	strcpy (artist, (char *) now->rlm_artist);
	strcpy (album, (char *) now->rlm_album);
	char find = ' ';
	char replace = '+';
	int pm = 1;
	if (log->log_onair == '1')
		pm = 2;
	replace_char(title, find, replace);
	replace_char(artist, find, replace);
	replace_char(album, find, replace);
	
	if (strlen(title) == 0) {
		return;
	}
	if (!(strcmp(old_title, title))) {
		RLMLog(ptr, LOG_WARNING, "Same title. Dropping.");
		return;
	}
	strcpy(old_title, title);
	char sendToSpinitron[BUFFER_SIZE];
	int n;
	//char user[BUFFER_SIZE];
	//char pass[BUFFER_SIZE];
	n = sprintf(sendToSpinitron,
	"curl https://spinitron.com/member/logthis.php -d \"un=%s&pw=%s&sn=%s&aw=%s&dn=%s&pm=%i&df=Rivendell&st=%s\"",
		USERNAME, PASSWORD, title, artist, album, pm, STATION);
	RLMLog(ptr,LOG_WARNING, sendToSpinitron);
	system(sendToSpinitron);
	RLMLog(ptr, LOG_WARNING, "Data send complete");
}

void rlm_spinitron_RLMTimerExpired(void *ptr, int timernum)
{


}
