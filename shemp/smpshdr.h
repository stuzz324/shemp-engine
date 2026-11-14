#ifndef SMPSHDR_H
#define SMPSHDR_H
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <regex.h>
#include <swgrb.h>
#include <smptypes.h>
#include <smperr.h>
#include <assert.h>
#include <stdbool.h>
#include <linux/limits.h>
#include <sys/time.h>
//PUBLIC MACROS & PREDEFS


//GLOBAL EXTERN VARIABLES


//TYPE DEFINITIONS
typedef struct smp_pmatches {
    //array of pmatches (each to be passed to regexec())
    regmatch_t** arr;
    //length of the pmatch array
    size_t arr_len;
    //length of the pmatch array arrays
    size_t se_len;
} smp_pmatches_t;

typedef struct smp_sources {
    char** src_arr;
    int* len_arr;
    size_t len;
} smp_sources_t;

//PUBLIC FUNCTIONS
//in (tools to read templated shader code)
rdbuf* smp_read_shdr(const char* trgt);
void smp_get_shdr_files(int mode, smp_pmatches_t** matches);
//out (tools to write templated shader code)
int smp_write_shdr();


//TEST
int smp_test_shdr();
void smp_proto_get_test();
void smp_test_sources();

//FILE STRUCTURE
/* The structure of the data folder:
 *  /data
 *    |-/shaders
 *    |     |-/shdr_code_[MATERIAL].vs
 *    |     |-...
 *    |-...
 */


//INSTALL PROPOSITION
/* Designing the file structure that will be adhered to
 * conjures a vital question: design an installer? The
 * answer: yes, but later. Just create the file directories
 * manually for now. (Neccessity is a mother and all that)
 */

#endif
