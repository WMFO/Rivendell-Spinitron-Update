/*
 *  rlm_spinitron.c
 *  Log songs playing in Rivendell to Spinitron
 *
 *  Module by Eric Berg, Benjamin Yu (C) Copyright 2009.
 *  Enhancements by Max Goldstein    (C) Copyright 2012.
 *  For more copyright and legal information, see TERMS and COPYING.
 *
 *  For documentation, see the README. For compilation, see the Makefile.
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <syslog.h>

#include "rlm.h"
#include "credentials.h" // defines const char*s USERNAME, PASSWORD, STATION

#define LOG_CART_NUM 1 // Boolean: should log cart numbers in notes field?
#define NOTE_LEN 20

#define BUFFER_SIZE 512
#define LARGE_BUFFER BUFFER_SIZE*4
char old_title[BUFFER_SIZE]; //Global to persist between callbacks

void rlm_spinitron_RLMStart(void *ptr, const char *arg)
{
    (void) arg; //Silence compiler warning
    RLMLog(ptr,LOG_INFO,"Rivendell-Spinitron Update will start logging now.");
    strcpy(old_title, "A string that will never be the title of a song.");
}

void rlm_spinitron_RLMFree(void *ptr)
{
    RLMLog(ptr,LOG_INFO, "Rivendell-Spinitron Update will stop logging now.");
}

void url_encode (char *src, int len) {
    int soffset = 0;
    int doffset = 0;
    char dst[len];
    memset(dst, '\0', len);
    char a = src[soffset++];
    while (doffset < len && a != '\0'){
        if ((a >= '0' && a <= '9') ||
            (a >= 'A' && a <= 'Z') ||
            (a >= 'a' && a <= 'z')) {
           dst[doffset++] = a;
        }else if (a == ' '){
           dst[doffset++] = '+';
        }else{
            if (doffset +4 < len){
                snprintf(&dst[doffset], 4, "%%%02X", a);
                doffset += 3;
            }else{
                dst[doffset] = '\0';
                break;
            }
        }
       a = src[soffset++];
    }
    dst[len-1] = '\0';
    strncpy(src, dst, len);
}

void rlm_spinitron_RLMPadDataSent(void *ptr,const struct rlm_svc *svc,
                const struct rlm_log *log,
                const struct rlm_pad *now,
                const struct rlm_pad *next)
{
    (void) svc;
    (void) next;

    char title[BUFFER_SIZE];
    char artist[BUFFER_SIZE];
    char album[BUFFER_SIZE];
    int chars_needed;
    openlog("Rivendell-Spinitron", LOG_PID, LOG_USER);
    #ifdef AXIA_CHECK_ENABLED
        char axiabuf[LARGE_BUFFER];
	chars_needed = snprintf(axiabuf, LARGE_BUFFER,
	"curl -s -u %s:%s --connect-timeout 2 %s | grep \"name=%s\" | grep -c %s > /dev/null",
        NODE_USERNAME, NODE_PASSWORD, NODE_URL, NODE_CHANNEL, NODE_STUDIO_PGM_CHANNEL);
    	if (chars_needed >= LARGE_BUFFER){
            RLMLog(ptr, LOG_ERR, "Insufficient buffer size to check axia routing.");
    	} else {
	    if (system(axiabuf) == 0) {
		syslog(LOG_DEBUG,"Node Indicates Configured Source Active, Continue.");
		RLMLog(ptr, LOG_INFO, "Node Indicates Configured Source Active, Continue.");
	    } else {
		syslog(LOG_DEBUG, "Node Indicates Configured Source Inactive, Stop.");
		RLMLog(ptr, LOG_INFO, "Node Indicates Configured Source Inactive, Stop.");
		return;
	    }
	}
    #endif
    strncpy (title,  now->rlm_title,  BUFFER_SIZE);
    strncpy (artist, now->rlm_artist, BUFFER_SIZE);
    strncpy (album,  now->rlm_album,  BUFFER_SIZE);
    title [BUFFER_SIZE-1] = '\0';
    artist[BUFFER_SIZE-1] = '\0';
    album [BUFFER_SIZE-1] = '\0';
    url_encode(title,  BUFFER_SIZE);
    url_encode(artist, BUFFER_SIZE);
    url_encode(album,  BUFFER_SIZE);

    int pm = log->log_onair ? 2 : 1;
    char notes[NOTE_LEN];
    if (LOG_CART_NUM){
        snprintf(notes, NOTE_LEN, "(cart %u)", now->rlm_cartnum);
        notes[NOTE_LEN -1] = '\0';
    }else{
        notes[0]='\0';
    }

    if (! *title){
        syslog(LOG_WARNING, "No title. Dropping.");
        RLMLog(ptr, LOG_WARNING, "No title. Dropping.");
        return;
    }
    if (!(strncmp(old_title, title, BUFFER_SIZE))) {
        syslog(LOG_WARNING, "Same title. Dropping.");
        RLMLog(ptr, LOG_WARNING, "Same title. Dropping.");
        return;
    }
    strncpy(old_title, title, BUFFER_SIZE);

    char sendToSpinitron[LARGE_BUFFER];
    chars_needed = snprintf(sendToSpinitron, LARGE_BUFFER,
    "curl -s --connect-timeout 2 https://spinitron.com/member/logthis.php -d \"un=%s&pw=%s&sn=%s&aw=%s&dn=%s&se=%s&pm=%i&df=Rivendell&st=%s\"",
        USERNAME, PASSWORD, title, artist, album, notes, pm, STATION);
    if (chars_needed >= LARGE_BUFFER){
	syslog(LOG_ERR,"Insufficient buffer size to send to Spinitron.");
        RLMLog(ptr, LOG_ERR, "Insufficient buffer size to send to Spinitron.");
    }else{
        int retval = system(sendToSpinitron);
        if (retval == -1 || retval == 127){
            syslog(LOG_ERR, "Unable to send to Spinitron. Something is wrong with the shell.");
            RLMLog(ptr, LOG_ERR, "Unable to send to Spinitron. Something is wrong with the shell.");
        } else if (retval) {
            syslog(LOG_ERR, "Unable to send to Spinitron. Something is wrong with curl.");
            RLMLog(ptr, LOG_ERR, "Unable to send to Spinitron. Something is wrong with curl.");
        }
    }
    syslog(LOG_INFO, "%s", sendToSpinitron);
    RLMLog(ptr, LOG_INFO, sendToSpinitron);
}

void rlm_spinitron_RLMTimerExpired(void *ptr, int timernum)
{
    (void) ptr;
    (void) timernum;
}
