#include "Cli_Serv.h"


int main(int agrc, char *argv[])
{
	mqd_t serv,req;
 	struct mq_attr attr;
	struct message m;
	size_t len=100;
  	unsigned int prio=1;
	int t=10;

	m.client=atoi(argv[1]);

	serv = mq_open( argv[2], O_RDONLY | O_CREAT, FILE_MODE, NULL);
	req= mq_open(argv[3], O_WRONLY | O_CREAT, FILE_MODE, NULL);

	while(t--)
	{
		printf("Press: \n 1 to MONITOR\n2 to POST\n3 to GET_NOTIFICATIONS");
		scanf("%d",&m.request);

		switch(m.request)
		{
		 case 1:
			scanf("%d",&m.hashtag_num);
			mq_send(req, &m, len, prio);
			break;
		case 2:
			scanf("%d",&m.hashtag_num);
			fgets(m.msg,100,stdin);
			mq_send(req, &m, len, prio);
			break;
		case 3:
			while(len !=0)
			len=mq_receive(serv,m.msg,attr.mq_msgsize, &prio);
			break;
		}
	}

}
