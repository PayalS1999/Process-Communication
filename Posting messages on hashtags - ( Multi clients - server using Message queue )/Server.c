#include "Cli_Serv.h"

int main(int agrc, char *argv[])
{
  	mqd_t cli[5],req;
 	struct mq_attr attr;
	struct message m;
	size_t len=100;
  	unsigned int prio=1;
  	int i,client_subscription[5]={0},ht[5][5],ht_size[5]={0}, t=20; /*ht size contains no. of clients in the particular hashtag*/

	req = mq_open( argv[1], O_RDONLY | O_CREAT | O_EXCL, FILE_MODE, NULL);
    if(req < 0){
      printf("Queue not created \n");
      exit(0);
    }

	for(i=0;i<5;i++) {
	cli[i] = mq_open(argv[i+2], O_WRONLY | O_CREAT | O_EXCL, FILE_MODE, NULL);
	if(cli[i] < 0){
      printf("Queue not created \n");
      exit(0);
    }
	}

	while(t >= 0)
	{
		printf("\n\nActive Hashtags:\n\n 1. #MOVIE\n 2. #SONG\n 3. #CRICKET\n4. #DANCE\n5. #VIDEO_GAME");

		len = mq_receive(req, (char *)&m, sizeof(m), &prio);

		if(m.request==1 && client_subscription[m.client]<=3)
		{
			ht[m.hashtag_num ][ht_size[m.hashtag_num]]=m.client; /* ht contains hashtags and corresponding client subscription table*/
			ht_size[m.hashtag_num]++;
			client_subscription[m.client]++;
		}
		else if(m.request == 2)
		{
			printf("posted  HASHTAG%d\n:",m.hashtag_num+1);
			puts(m.msg);
			printf("\n by client num %d",m.client);
			for(i=0;i<ht_size[m.hashtag_num];i++)
				mq_send(cli[ ht[ m.hashtag_num ][ i ]], &m.msg, len, prio);
		}
        t--;
	}	

	
}


