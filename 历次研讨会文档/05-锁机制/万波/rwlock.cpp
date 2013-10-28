#include <iostream>
#include <cstdlib>

#include <unistd.h>
#include <pthread.h>

using namespace std;

struct sharedData{
    pthread_rwlock_t rwlock;
    int product;
}sharedData = {PTHREAD_RWLOCK_INITIALIZER, 0};

void * produce(void *ptr)   //д��ʹ����
{
    for (int i = 0; i < 5; ++i)
    {
        pthread_rwlock_wrlock(&sharedData.rwlock);
        sharedData.product = i;
        pthread_rwlock_unlock(&sharedData.rwlock);

        sleep(1);
    }
}

void * consume1(void *ptr)  //����ʹ����
{
    for (int i = 0; i < 5;)
    {
        pthread_rwlock_rdlock(&sharedData.rwlock);
        cout<<"consume1:"<<sharedData.product<<endl;
        pthread_rwlock_unlock(&sharedData.rwlock);

        ++i;
        sleep(1);
    }
}

void * consume2(void *ptr) //����ʹ����
{
    for (int i = 0; i < 5;)
    {
        pthread_rwlock_rdlock(&sharedData.rwlock);
        cout<<"consume2:"<<sharedData.product<<endl;
        pthread_rwlock_unlock(&sharedData.rwlock);

        ++i;
        sleep(1);
    }
}

int main()
{
    pthread_t tid1, tid2, tid3;
    unsigned int flag = 0;

	/*���������̣߳��ֱ�
	*int pthread_create(pthread_t*restrict tidp, const pthread_attr_t *restrict_attr, void*(*start_rtn)(void*), void *restrict arg);
	*1.��tidpָ����ڴ浥Ԫ������Ϊ�´����̵߳��߳�ID
	*2.attr��������ָ�����ֲ�ͬ���߳�����
	*3.�´������̴߳�start_rtn�����ĵ�ַ��ʼ����
	*4.�ú���ֻ��һ������ָ�����arg�������Ҫ��start_rtn�������ݵĲ�����ֹһ����
	*��ô��Ҫ����Щ�����ŵ�һ���ṹ�У�Ȼ�������ṹ�ĵ�ַ��Ϊarg�Ĳ�������
	*/
    	pthread_create(&tid1, NULL, produce, NULL);
    	sleep(2);

    	pthread_create(&tid2, NULL, consume1, NULL);
    	pthread_create(&tid3, NULL, consume2, NULL);

    void *retVal;

	/*
	*�������ķ�ʽ�ȴ�threadָ�����߳̽���
	*thread: �̱߳�ʶ�������߳�ID����ʶΨһ�̡߳�
	*retval: �û������ָ�룬�����洢���ȴ��̵߳ķ���ֵ
	*����ֵ��0����ɹ���ʧ�ܣ����ص����Ǵ���š�
	*/
    pthread_join(tid1, &retVal);
    pthread_join(tid2, &retVal);
    pthread_join(tid3, &retVal);

    return 0;
}