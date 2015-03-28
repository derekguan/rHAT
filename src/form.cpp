
#include "form.h"
#include "desc.h"

#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>

#define RH_SEED_LEN 8
#define WAITING_LEN 203



char *const short_options = "w:m:k:a:b:q:r:h";
struct option long_options[] = {
    { "window-hits",     1,   NULL,    'w'   },
    { "candidates",     1,   NULL,    'm' },
    { "kmer-size",     1,   NULL,    'k'   },
    { "match",     1,   NULL,    'a'   },
    { "mismatch",		1,NULL,	'b'},
    //{ "auto_load", 0, NULL, 'a'},
    {"gap-open", 1,  NULL, 'q'},
    {"gap-extension", 1,  NULL,'r'},
    //{"gapextended", 1,  NULL,'e'},
    //{"match",   1,  NULL,'c'},
    {"help",    0,  NULL,'h'},
    { 0,     0,   0,    0   }
};

Form::Form(opts *opt)
{

    opt->len_sed = 13;
    opt->canN = 5;
    opt->hit_limit = 1000;
    //opt->usecigar = true;
    opt->rh_seed_len = RH_SEED_LEN;
    opt->waitingLen = WAITING_LEN;
    opt->thread = 1000;
    opt->len_limit = 100000;
    opt->gapopen = 2;
    opt->gapextend = 1;
    opt->mismatch = 5;
    opt->match = 1;

    //opt->autoload = false;

}

int Form::usage()
{

    fprintf(stderr, "\n"); 
    fprintf(stderr, "Program:   rHAT-aligner\n"); 
    fprintf(stderr, "Version:   %s\n", PACKAGE_VERSION); 
    fprintf(stderr, "Contact:   %s\n\n", CONTACT); 
    fprintf(stderr, "Usage:     rHAT-aligner [Options] <HashIndexDir> <ReadFile> <Reference>\n\n"); 
    fprintf(stderr, "<HashIndexDir>         The directory storing RHT index\n");
    fprintf(stderr, "<ReadFile>             Reads file, in FASTQ/FASTA format\n");
    fprintf(stderr, "<Reference>            Sequence of reference genome, in FASTA format\n\n");

    fprintf(stderr, "Options:   -w, --window-hits      <int>           the max allowed number of windows hitting by a k-mer [1000]\n"); 
    fprintf(stderr, "           -m, --candidates       <int>           the number of candidates for extension [5]\n"); 
    fprintf(stderr, "           -k, --kmer-size        <int>           the size of the k-mers for generating short token matches [13]\n"); 
   	fprintf(stderr, "           -a, --match            <int>           score of match for the alignments in extension phase [1]\n");
   	fprintf(stderr, "           -b, --mismatch         <int>           mismatch penalty for the alignments in extension phase [5]\n");
   	fprintf(stderr, "           -q, --gap-open         <int>           gap open penalty for the alignments in extension phase [2]\n");
   	fprintf(stderr, "           -r, --gap-extension    <int>           gap extension penalty for the alignments in extension phase [1]\n");
   	fprintf(stderr, "           -h, --help                             help\n");
    fprintf(stderr, "\n"); 
    return 0;
}

int Form::opt_parse(int argc, char *argv[], opts* opt)
{
	int c; 
    int option_index=0;
    if (argc == 1) return usage();
    while((c = getopt_long(argc, argv, short_options, long_options, &option_index))>=0){
        switch(c){
            case 'm':
                opt->canN = atoi(optarg);
                break;
            case 'h':
                return usage();
                break;
            case 'w':
                opt->hit_limit = atoi(optarg);
                break;
            case 'k':
                opt->len_sed = atoi(optarg);
                break;
            case 'q':
                opt->gapopen = atoi(optarg);
                break;
            case 'r':
                opt->gapextend = atoi(optarg);
                break;
            case 'a':
                opt->match = atoi(optarg);
                break;
            case 'b':
                opt->mismatch = atoi(optarg);
                break;
            default:
                fprintf(stderr,"not proper parameters\n");
                return usage();
              
        }
    
    }
    if(optind + 3 != argc){
        fprintf(stderr, "[opt_parse]: index directory, read file and reference file can't be omited!\n"); 
        return 0; 
    }
    opt->argv = argv;
    opt->argc = argc;
 	strncpy(opt->hashdir, argv[optind++],sizeof(opt->hashdir));
 	strncpy(opt->readpath,argv[optind++],sizeof(opt->readpath));
 	strncpy(opt->refpath,argv[optind++],sizeof(opt->refpath));

    return 1;  

}
