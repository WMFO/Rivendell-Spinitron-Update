#ifndef RIVENDELL_SPINITRON_CREDENTIALS
#define RIVENDELL_SPINITRON_CREDENTIALS
const char* USERNAME = "myAwesomeUsername";
const char* PASSWORD = "mySup3rS3cr3tPassw0rd";
const char* STATION  = "wxyz";
#endif

//to disable, undefine AXIA_CHECK_ENABLED
#define AXIA_CHECK_ENABLED
#ifdef AXIA_CHECK_ENABLED
const char* NODE_URL = "http://192.168.1.1/cgi-bin/cgi_dsts";
const char* NODE_USERNAME = "user";
const char* NODE_PASSWORD = "password";
const char* NODE_CHANNEL= "R007_RURL";
const char* NODE_STUDIO_PGM_CHANNEL = "10500";
#endif

#endif

