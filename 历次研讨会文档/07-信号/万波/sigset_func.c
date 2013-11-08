#include<signal.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

static void my_op(int);
int main()
{
	sigset_t new_mask,old_mask,pending_mask;
	struct sigaction act;
	
	printf("process start\n");
	
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	act.sa_handler=my_op;
	if(sigaction(SIGQUIT,&act,NULL)<0)    //��װ�ź�
		printf("install signal SIGQUIT error\n");

	sigemptyset(&new_mask);	  //����ź�
	sigaddset(&new_mask,SIGQUIT);   //����ź�
	if(!sigprocmask(SIG_BLOCK, &new_mask,&old_mask))  //������ӵ��ź�
		printf("block signal SIGQUIT\n");

	sleep(10);	
	printf("now begin to get pending mask and unblock SIGQUIT\n");
	if(sigpending(&pending_mask)<0)   //�õ�������ź� man sigpending
		printf("get pending mask error\n");  
	if(sigismember(&pending_mask,SIGQUIT))  //�ж��Ƿ��д��źű�����
		printf("signal SIGQUIT is pending\n");

	if(sigprocmask(SIG_SETMASK,&old_mask,NULL)<0)   //ʹ�����źŲ�������
		printf("unblock signal error\n");
	printf("signal unblocked\n");

	sleep(10);
}
static void my_op(int signum)
{
	printf("receive signal %d \n",signum);  //��ӡ���̺�
}



SIGHUP     ��ֹ����     �ն���·�Ҷ�
SIGINT     ��ֹ����     �жϽ���
SIGQUIT   ����CORE�ļ���ֹ���̣���������core�ļ�
SIGILL   ����CORE�ļ�       �Ƿ�ָ��
SIGTRAP   ����CORE�ļ�       ��������
SIGBUS   ����CORE�ļ�       ���ߴ���
SIGSEGV   ����CORE�ļ�       �ηǷ�����
SIGFPE   ����CORE�ļ�       �����쳣
SIGIOT   ����CORE�ļ�       ִ��I/O����
SIGKILL   ��ֹ����     ɱ������
SIGPIPE   ��ֹ����     ��һ��û�ж����̵Ĺܵ�д����
SIGALARM   ��ֹ����     ��ʱ����ʱ
SIGTERM   ��ֹ����     �����ֹ�ź�
SIGSTOP   ֹͣ����     ���ն�����ֹͣ�ź�
SIGTSTP   ֹͣ����     �ն�����ֹͣ�ź�
SIGCONT   �����ź�     ����ִ��һ��ֹͣ�Ľ���
SIGURG   �����ź�     I/O�����ź�
SIGIO     �����ź�     �������Ͽ��Խ���I/O
SIGCHLD   �����ź�     ���ӽ���ֹͣ���˳�ʱ֪ͨ������
SIGTTOU   ֹͣ����     ��̨����д�ն�
SIGTTIN   ֹͣ����     ��̨���̶��ն�
SIGXGPU   ��ֹ����     CPUʱ�޳�ʱ
SIGXFSZ   ��ֹ����     �ļ����ȹ���
SIGWINCH   �����ź�     ���ڴ�С�����仯
SIGPROF   ��ֹ����     ͳ�Ʒֲ�ͼ�ü�ʱ����ʱ
SIGUSR1   ��ֹ����     �û������ź�1
SIGUSR2   ��ֹ����     �û������ź�2
SIGVTALRM ��ֹ����     �����ʱ����ʱ