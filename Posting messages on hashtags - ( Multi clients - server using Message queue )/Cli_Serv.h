#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <mqueue.h>

#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

#define HASHTAG1 "#MOVIE"
#define HASHTAG2 "#SONG"
#define HASHTAG3 "#CRICKET"
#define HASHTAG4 "#DANCE"
#define HASHTAG5 "#VIDEO_GAME"

struct message
{
	char msg[100];
	int client,request,hashtag_num;

};
