#ifndef TRISTAN_GLOBALS
# define TRISTAN_GLOBALS

#define MAX_PKG_NUM		10000 // max len->"[coreutils, libc6, tcpd, apache2 ... ]"
#define AV_CONF_FILE		"available.txt"
#define LOCAL_CONF_FILE		"glibc-2.4.2"
#define MAX_DEP_NUM		10000 // max len->"[coreutils, libc6, tcpd, apache2 ... ]"
							  // numero maximo de grupos como "coreutils (=> 12.3)"

/* Defines for max length of the conf lines to read */
#define MAX_LINE_LEN		2048
#define MAX_PKG_LEN		1024 // max len->"coreutils"
#define MAX_VER_LEN		30
#define MAX_OP_LEN		3
#define MAX_DEP_LEN		100
#define MAX_DEP_GROUP_LEN	6000 //(suma de los 3 anteriores) // max len->"coreutils (=> 12.3)"
#define MAX_COMPR_LEN		100
#define MAX_SECTION_LEN		100
#define MAX_REQUIRE_LEN		1024
#define MAX_URL_LEN		8192
#define MAX_MDSUM_LINE		1024
#define MAX_DSCR_LEN		1024

#endif
