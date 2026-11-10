#ifndef SMPSHDR_H
#define SMPSHDR_H
#include <stdlib.h>
#include <stdio.h>
#include <swgrb.h>
#include <dirent.h>
#include <fcntl.h>
#include <smptypes.h>
#include <smperr.h>
//PUBLIC MACROS & PREDEFS


//GLOBAL EXTERN VARIABLES


//PUBLIC FUNCTIONS
//in (tools to read templated shader code)
rdbuf* smp_read_shdr();


//out (tools to write templated shader code)
int smp_write_shdr();


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
