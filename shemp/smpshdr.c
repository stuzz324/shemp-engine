#include "smpshdr.h"

int smps_errno = 0;

//not needed exactly
// typedef struct smp_bufobj {
//     GLenum trgt;
//     GLuint id;
// } smp_bufobj_t;

//PRIVATE FUNCTIONS
int smp_load_shdr(uint* shdr_id, int mode, smp_sources_t* sources) {
    switch (mode) {
        case SMP_SHLVRT:
            //*shdr_id = glCreateShader(GL_VERTEX_SHADER);
            break;
        case SMP_SHLFRG:
            //*shdr_id = glCreateShader(GL_FRAGMENT_SHADER);
            break;
        default:
            shdr_id = NULL; //makes arg of &uint uninitialized?
            return -1;
    }

    if (sources->len == 0) return -1;

    //glShaderSource(*shdr_id, sources->len, sources->src_arr, sources->len_arr);

    return 0;
}


//PUBLIC FUNCTIONS
rdbuf* smp_read_shdr(const char* trgt) {
    int fd;
    //open
    if (trgt == NULL) {
        if ((fd = open("./data/shaders", O_RDONLY)) == -1) {
            perror("smp_read_shdr()::open()");
            smps_errno |= SMP_ESHDRD;
            return NULL;
        }
    } else {
        if ((fd = open(trgt, O_RDONLY)) == -1) {
            perror("smp_read_shdr()::open()");
            smps_errno |= SMP_ESHDRD;
            return NULL;
        }
    }

    //create rdbuf, passing fd
    rdbuf* rb = create_rdbuf(fd);
    //read
    if (read(fd, rb->str, rb->len) == -1) {
        perror("smp_read_shdr()::read()");
        smps_errno |= SMP_ESHDRD;
        return NULL;
    }

    return rb;
}

int smp_write_shdr() {

    return 0;
}

size_t get_se_cnt(const char* rgx_str) {
    size_t se_cnt = 0;
    size_t rs_len = strlen(rgx_str);
    bool f_open = 0;

    for (size_t idx = 0; idx < rs_len; idx++) {
        if (rgx_str[idx] == '(' || rgx_str[idx] == ')') {
            //CHECK THE '!idx'
            if (!idx & (rgx_str[idx-1] == '\\')) {
                continue;
            } else {
                //after verifying char isn't a literal '(' or ')'
                if (!f_open && rgx_str[idx] == '(') f_open = true;
                //close parentheses detected
                else if (f_open && rgx_str[idx] == ')') {
                    se_cnt++;
                    f_open = false;
                }
            }
        }
    }

    return se_cnt + ((1 < se_cnt) ? 1 : 0);
}

int smp_test_shdr() {
    printf("================SMP_TEST_SHDR================\n");
    regex_t rgx;
    DIR* dir;
    char trgt_dir[PATH_MAX];
    getcwd(trgt_dir, PATH_MAX);
    strcat(trgt_dir, "/data/shaders");
    printf("dir = opendir(%s)\n", trgt_dir);
    dir = opendir(trgt_dir);
    struct dirent* entry;
    const char* test_trgt = "^test_shdr_[0-9]{1,2}\\.vs$";
    rdbuf* shdr_buf;

    //TODO: implement error catching here
    regcomp(&rgx, test_trgt, REG_EXTENDED);
    while ((entry = readdir(dir)) != NULL) {
        printf("entry->d_name: %s\n", entry->d_name);
        if (regexec(&rgx, entry->d_name, 0, NULL, 0) == REG_NOMATCH) continue;
        printf("MATCHED\n");

        char* shdr_path = calloc(sizeof(trgt_dir) + 1 + sizeof(entry->d_name) + 1, 1);

        //strcat(strcat(trgt_dir, "/"), entry->d_name);
        strcat(strcat(strcat(shdr_path, trgt_dir), "/"), entry->d_name);
        printf("%s\n", trgt_dir);
        shdr_buf = smp_read_shdr(shdr_path);
        break;
    }
    printf("shdr_buf:\n\n%s\n", shdr_buf->str);
    printf("FREEING...\n");
    regfree(&rgx);
    free(shdr_buf);
    printf("DONE\n");
    printf("=============================================\n");
    return 0;
}

static regex_t rgx;
//FILTERS
int smp_filter(const struct dirent* entry) {
    if (regexec(&rgx, entry->d_name, 0, NULL, 0) == REG_NOMATCH) {
        return 0;
    }
    return 1;
}

int smp_filter_noreldir(const struct dirent* entry) {
    if (
        memcmp(entry->d_name, ".", strlen(entry->d_name)) == 0 ||
        memcmp(entry->d_name, "..", strlen(entry->d_name)) == 0
    ) return 0;
    return 1;
}

size_t smp_scandir(const char* shdr_path, struct dirent*** namelist) {
    size_t nl_len;
    if ((nl_len = scandir(shdr_path, namelist, &smp_filter_noreldir, &alphasort)) == -1) {
        perror("smp_get_shdr_dirs()::scandir()");
        return -1;
    }
    //printf("nl_len: %ld\n", nl_len);
    //returns namelist length
    return nl_len;
}

//RETURN NULL IF 'arr_len' = 0
smp_pmatches_t* smp_create_pmatches(size_t arr_len, size_t se_len) {
    //printf("smp_create_pmatches() called...\n");
    smp_pmatches_t* matches = malloc(sizeof(smp_pmatches_t));
    if (arr_len == 0) matches->arr = NULL;
    else matches->arr = malloc(8 * arr_len);
    matches->arr_len = arr_len;
    matches->se_len = se_len;

    for (size_t arr_idx = 0; arr_idx < matches->arr_len; arr_idx++) {
        matches->arr[arr_idx] = malloc(sizeof(regmatch_t) * se_len);
    }

    return matches;
}

void smp_free(smp_pmatches_t* matches) {
    if (matches->arr_len == 0) return;
    for (size_t arr_idx = 0; arr_idx < matches->arr_len; arr_idx++) {
        //printf("[%ld] Freeing {%p}...\n", arr_idx, matches->arr[arr_idx]);
        free(matches->arr[arr_idx]);
        //printf("[%ld] Done!\n", arr_idx);
    }
}

smp_sources_t* smp_create_sources(size_t len) {
    smp_sources_t* sources;

    sources = malloc(sizeof(smp_sources_t));
    sources->len = len;
    sources->src_arr = malloc(8*sources->len);
    sources->len_arr = malloc(sizeof(int)*sources->len);

    return sources;
}

//sets the new length of the smp_sources_t object passed to it
void smp_resize_sources(smp_sources_t** sources, size_t n) {
    //update len
    (*sources)->len = n;
    //resize len_arr
    (*sources)->len_arr = reallocarray((*sources)->len_arr, (*sources)->len, sizeof(int));
    //resize src_arr
    (*sources)->src_arr = reallocarray((*sources)->src_arr, (*sources)->len, 8);
}

//overwrite an existing element with new_element at idx in (*sources)->src_arr or resize array and set new_element at idx
void smp_set_sources(smp_sources_t** sources, size_t idx, const char* new_element) {
    if (new_element == NULL) return; //update in future (change return type if needed)
    //if it goes out of bounds of the src_arr, resize to idx
    if ((*sources)->len < idx) smp_resize_sources(sources, idx);
    (*sources)->len_arr[idx] = strlen(new_element);
    (*sources)->src_arr[idx] = (char*) new_element;
}

void smp_print_sources(smp_sources_t* sources) {
    if (sources == NULL) {
        printf("Print failed: sources is NULL!\n");
        return;
    }
    printf("{%p} sources(len: %ld):\n", sources, sources->len);
    for (size_t src_idx = 0; src_idx < sources->len; src_idx++) {
        printf("\t%s | %d\n", sources->src_arr[src_idx], sources->len_arr[src_idx]);
    }
}

/*IMPORTANT WHEN ACCESSING LENGTH-ARRAY: add 1 to the int via expression! Each element in len_arr is the string's LENGTH,
 *                                       not including null-terminator.
 */
void smp_add_sources(smp_sources_t** sources, size_t n, const char* new_sources[n]) {
    size_t offset = (*sources)->len;
    smp_resize_sources(sources, (*sources)->len + n);
    //smp_print_sources(*sources);
    printf("passed smp_resize_sources()\n");
    printf("entering loop...\n");
    for (size_t ns_idx = offset; ns_idx < (*sources)->len; ns_idx++) {
        smp_set_sources(sources, ns_idx, new_sources[ns_idx - offset]);
        //get str lengths of each element from new_sources
        (*sources)->len_arr[ns_idx] = strlen(new_sources[ns_idx - offset]);
        //allocate and initialize the new char arrays for str_arr with corresponding len_arr element (add 1 for null-terminator)
        (*sources)->src_arr[ns_idx] = calloc((*sources)->len_arr[ns_idx]+1, 1);
        //copy string from new_sources element into str_arr element
        (*sources)->src_arr[ns_idx] = (char*) new_sources[ns_idx - offset];
    }
    printf("exiting loop\n");
}

#define GET_CALL_TIME_1(func, p0, t0, t1)\
    gettimeofday(&t0, NULL);\
    func(p0);\
    gettimeofday(&t1, NULL);\
    printf("func called in %g seconds\n", t1.tv_sec - t0.tv_sec + 1E-6 * (t1.tv_usec - t0.tv_usec));\
\

#define GET_CALL_TIME_2(func, p0, p1, t0, t1)\
    gettimeofday(&t0, NULL);\
    func(p0, p1);\
    gettimeofday(&t1, NULL);\
    printf("func called in %g seconds\n", t1.tv_sec - t0.tv_sec + 1E-6 * (t1.tv_usec - t0.tv_usec));\
\

#define GET_CALL_TIME_3(func, p0, p1, p2, t0, t1)\
    gettimeofday(&t0, NULL);\
    func(p0, p1, p2);\
    gettimeofday(&t1, NULL);\
    printf("func called in %.2g seconds\n", t1.tv_sec - t0.tv_sec + 1E-6 * (t1.tv_usec - t0.tv_usec));\
\

#define GET_CALL_TIME_1R(var, func, p0, t0, t1)\
    gettimeofday(&t0, NULL);\
    var = func(p0);\
    gettimeofday(&t1, NULL);\
    printf("func called in %g seconds\n", t1.tv_sec - t0.tv_sec + 1E-6 * (t1.tv_usec - t0.tv_usec));\
\

#define GET_CALL_TIME_2R(var, func, p0, p1, t0, t1)\
    gettimeofday(&t0, NULL);\
    var = func(p0, p1);\
    gettimeofday(&t1, NULL);\
    printf("func called in %g seconds\n", t1.tv_sec - t0.tv_sec + 1E-6 * (t1.tv_usec - t0.tv_usec));\
\

#define GET_CALL_TIME_3R(var, func, p0, p1, p2, t0, t1)\
    gettimeofday(&t0, NULL);\
    var = func(p0, p1, p2);\
    gettimeofday(&t1, NULL);\
    printf("func called in %.2g seconds\n", t1.tv_sec - t0.tv_sec + 1E-6 * (t1.tv_usec - t0.tv_usec));\
\

void smp_test_sources() {
    char* arr1[] = {
        "one",
        "two",
        "three",
        "four"
    };
    char* arr2[] = {
        "five",
        "six",
        "seven",
        "eight"
    };

    smp_sources_t* sources;
    struct timeval t0, t1;
    sources = smp_create_sources(4);
    //GET_CALL_TIME_1R(sources, smp_create_sources, 4, t0, t1);

    for (size_t i = 0; i < sources->len; i++) {
        smp_set_sources(&sources, i, (const char*) arr1[i]);
    }

    printf("{%p} len: %ld\n", sources, sources->len);
    for (int i = 0; i < 4; i++) {
        printf("\tsrc_arr[%d]: %s | len_arr[%d]: %d\n", i, sources->src_arr[i], i, sources->len_arr[i]);
    }

    //resize
    //smp_add_sources(&sources, 4, (const char**) arr2);
    //GET_CALL_TIME_3(smp_add_sources, &sources, 4, (const char**) arr2, t0, t1);

    gettimeofday(&t0, NULL);
    smp_add_sources(&sources, 4, (const char**) arr2);
    gettimeofday(&t1, NULL);
    printf("func called in %.2g seconds\n", t1.tv_sec - t0.tv_sec + 1E-6 * (t1.tv_usec - t0.tv_usec));

    printf("{%p} len: %ld\n", sources, sources->len);
    for (int i = 0; i < 8; i++) {
        printf("\tsrc_arr[%d]: %s | len_arr[%d]: %d\n", i, sources->src_arr[i], i, sources->len_arr[i]);
    }

    free(sources);
    sources = NULL;

    //should catch NULL pointer
    smp_print_sources(sources);
}

void smp_print_pmatches(smp_pmatches_t* matches) {
    printf("================SMP_PRINT_PMATCHES================\n");
    if (matches->arr_len != 0) {
        for(size_t arr_idx = 0; arr_idx < matches->arr_len; arr_idx++) {
            for (size_t pm_idx = 0; pm_idx < matches->se_len; pm_idx++) {
                printf("[%ld][%ld] {%p} rm_so: %d | rm_eo: %d\n", arr_idx, pm_idx, matches->arr[arr_idx], matches->arr[arr_idx][pm_idx].rm_so, matches->arr[arr_idx][pm_idx].rm_eo);
            }
            printf("________________________________________\n");
        }
    } else printf("ATTENTION: arr is empty; nothing to print\n");
    printf("==================================================\n");
}

void smp_mprint_pmatches(smp_pmatches_t* matches) {
    printf("================SMP_MPRINT_PMATCHES================\n");
    printf("matches: %p\narr: %p\narr_len: %ld\nse_len: %ld\n", matches, &matches, matches->arr_len, matches->se_len);
    printf("==================================================\n");
}

void smp_nlprint_pmatches(smp_pmatches_t* matches, struct dirent** namelist) {
    printf("================SMP_NLPRINT_PMATCHES================\n");
    if (matches->arr_len != 0) {
        for(size_t arr_idx = 0; arr_idx < matches->arr_len; arr_idx++) {
            for (size_t pm_idx = 0; pm_idx < matches->se_len; pm_idx++) {
                printf("[%ld][%ld] rm_so: %d | rm_eo: %d", arr_idx, pm_idx, matches->arr[arr_idx][pm_idx].rm_so, matches->arr[arr_idx][pm_idx].rm_eo);
                if (matches->arr[arr_idx][pm_idx].rm_so != -1 && matches->arr[arr_idx][pm_idx].rm_eo != -1) {
                    printf(" | snippet: ");
                    for (size_t foo = matches->arr[arr_idx][pm_idx].rm_so; foo < matches->arr[arr_idx][pm_idx].rm_eo; foo++) {
                        printf("%c", namelist[arr_idx]->d_name[foo]);
                    }
                    printf("\n");
                } else printf("\n");
            }
            printf("________________________________________\n");
        }
    } else printf("ATTENTION: arr is empty; nothing to print\n");
    printf("====================================================\n");
}

//get the shader files with options for each member of the
//  rendering pipeline
void smp_get_shdr_files(int mode, smp_pmatches_t** matches) {
    //printf("smp_proto_get() called...\n");
    struct dirent** namelist;
    const char* shdr_path = "./data/shaders";
    char* rgx_str;

    switch (mode) {
        case SMP_SHGVRT:
            rgx_str = "^(vert)_(.*)_([0-9]{1,2})\\.vs$";
            break;
        case SMP_SHGFRG:
            rgx_str = "^(frag)_(.*)_([0-9]{1,2})\\.vs$";
            break;
        case SMP_SHGALL:
            rgx_str = "^(vert|frag)_(.*)_([0-9]{1,2})\\.vs$";
            break;
    }
    //printf("rgx_str: %s\n", rgx_str);
    regcomp(&rgx, rgx_str, REG_EXTENDED);
    size_t ret, ret_se;
    //if (matches == NULL) free(matches);
    (*matches) = smp_create_pmatches((ret = smp_scandir(shdr_path, &namelist)), (ret_se = get_se_cnt(rgx_str)));
    if (&(*matches)->arr_len == NULL) printf("arr_len is NULL!\n");
    //printf("ret: %ld\n", ret);
    //printf("ret_se: %ld\n", ret_se);

    for (size_t arr_idx = 0; arr_idx < (*matches)->arr_len; arr_idx++) {
        if (
            regexec(&rgx, namelist[arr_idx]->d_name, (*matches)->se_len, (*matches)->arr[arr_idx], 0) == REG_NOMATCH
        ) {
            for (size_t se_idx = 0; se_idx < (*matches)->se_len; se_idx++) {
                (*matches)->arr[arr_idx][se_idx].rm_so = -1;
                (*matches)->arr[arr_idx][se_idx].rm_eo = -1;
            }
        }
    }
    //printf("INTERNAL PRINT\n");
    //smp_nlprint_pmatches((*matches), namelist);

    // printf("\t========\n\tNAMELIST\n\t========\n");
    // for (size_t nl_idx = 0; nl_idx < ret; nl_idx++) {
    //     printf("\t[%ld] %s\n", nl_idx, namelist[nl_idx]->d_name);
    // }

    regfree(&rgx);
}

/*
    pm_arr is an array of pmatches:

        pmatch is an array of:
            regmatch_t:
                --regoff_t rm_so
                --regoff_t rm_eo
        make pmatch the length of the namelist!
    pm_arr[] =
        pmatch[] =
            regmatch_t
            regmatch_t
            ...
        ...




 */
