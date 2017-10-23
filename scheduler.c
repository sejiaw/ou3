#include "scheduler.h"
#define nrofchars 100
#define nrofloops 5
#define nrofthreads 4
double averagecreate,averagecreate2,averageread,averageread2,averageremove,averageremove2;

pthread_mutex_t lock;

int main(void)
{
	double responstime,start,stop,removestop,removestart,removetime;
	start=calculate_time();
	pthread_t test1threads[nrofthreads];
	pthread_t test2threads[nrofthreads];
	pthread_mutex_init(&lock,NULL);
	for(int i=1; i<=nrofthreads; i++){
		int *arg=malloc(sizeof(int));
		*arg=i%2;
		int *arg2=malloc(sizeof(int));
		*arg2=i%2;
		pthread_create(&test1threads[i-1],NULL,test1,arg);
		pthread_create(&test2threads[i-1],NULL,test2,arg2);
	}
	for(int j=0; j< nrofthreads; j++){
		if(pthread_join(test1threads[j],NULL)){
			perror("error joining threads");
			exit(-1);
		}
	}
	for(int k=0; k< nrofthreads; k++){
		if(pthread_join(test2threads[k],NULL)){
			perror("error joining threads");
			exit(-1);
		}
	}

	//remove files

			
	removestart = calculate_time();
	remove_files("/home/thom/test/test2/test",30);
	removestop=calculate_time();
	removetime = (removestop-removestart);
	averageremove +=removetime;

	//remove 1 file from 10 different catalogues
	removestart = calculate_time();
	remove_files("/home/thom/asd/asd1/asd",3);
	remove_files("/home/thom/asd1/asd2/asd",3);
	remove_files("/home/thom/asd2/asd3/asd",3);
	remove_files("/home/thom/asd3/asd4/asd",3);
	remove_files("/home/thom/asd4/asd5/asd",3);
	remove_files("/home/thom/asd5/asd6/asd",3);
	remove_files("/home/thom/asd6/asd7/asd",3);
	remove_files("/home/thom/asd7/asd8/asd",3);
	remove_files("/home/thom/asd8/asd9/asd",3);
	remove_files("/home/thom/asd9/asd10/asd",3);
	removestop=calculate_time();
	removetime = (removestop-removestart);
	averageremove2 +=removetime;

		
	printf("\nTEST 1 : \n");
	printf("Average time to create 30 files in same catalogue: %f milliseconds \n", 
	averagecreate/5);
	printf("Average time to read 30 files in same catalogue: %f milliseconds \n", 
	averageread/5);
	printf("Time to remove 30 files in same catalogue: %f milliseconds \n", 
	averageremove);
	printf("\nTEST 2 : \n");
	printf("Average time to create 30 files in 10 different catalogues: %f milliseconds \n", 
	averagecreate2/5);
	printf("Average time to read 30 files in 10 different catalogues: %f milliseconds \n", 
	averageread2/5);
	printf("Time to remove 30 files in 10 different catalogues: %f milliseconds \n", 
	averageremove2);
	
	printf("\nTEST 3 : \n");
	test3(5);
	stop=calculate_time();
	responstime=(stop-start);
	
	printf("\nRespons time: %f milliseconds\n",responstime-5000);
	printf("\nTest complete\n");
	
	return 0;
}


void create_files(char path[], int amount)
{

	FILE *fp=NULL;
	for(int i=1; i<=amount; i++) 
	{
		char home[50];
		strcpy(home,path);
		char nr[2];
		sprintf(nr,"%d",i);
		fp = fopen(strcat(home,nr),"w");
		add_to_file(fp);

	}

	fclose(fp);
}

void add_to_file(FILE *fp)
{
	for(int j=0; j<nrofchars; j++)
	{

		fputs("a",fp);
	}



}

bool file_exists(char path[]){
	FILE *fp =NULL;
	if(fp=fopen(path,"r")){
		fclose(fp);
		return true;
	}
	return false;
	
}
double calculate_time()
{
	struct timeval timecheck;
	gettimeofday(&timecheck,NULL);
	return (double)timecheck.tv_sec * 1000 + (double)timecheck.tv_usec/1000;
}

void remove_files(char path[],int amount)
{
	for(int i=1; i<=amount; i++)
	{

		char home[50];
		char nr[2];
		strcpy(home,path);
		sprintf(nr,"%d",i);
		remove(strcat(home,nr));
		
		
	}
}

void *test1(void *argum)
{
	double start,stop,time,totaltimestart, 
	totaltimestop,totaltime;
	int arg=*((int*)argum);
	totaltimestart = calculate_time();
	for(int i=0; i<nrofloops; i++){
		if(arg==1){
			pthread_mutex_lock(&lock);
			start = calculate_time();
			//create
			create_files("/home/thom/test/test2/test",30);
			stop=calculate_time();
			time = (stop-start);
			averagecreate +=time;
			pthread_mutex_unlock(&lock);
		}else if(arg==0){
			pthread_mutex_lock(&lock);
			//read 
			start = calculate_time();	
			read_files("/home/thom/test/test2/test",30);
			stop=calculate_time();
			time = (stop-start);
			averageread +=time;
			pthread_mutex_unlock(&lock);
		}
	}
	totaltimestop = calculate_time();	
	totaltime=(totaltimestop-totaltimestart);
	free(argum);

}

void *test2(void *argum)
{
double start,stop,time,totaltimestart, 
	totaltimestop,totaltime;
	int arg=*((int*)argum);
	//test2
	//create 3 file in 10 different catalogues
	totaltimestart = calculate_time();
	for(int j=0; j<nrofloops; j++){
		if(arg==1){
			pthread_mutex_lock(&lock);
			start = calculate_time();
			create_files("/home/thom/asd/asd1/asd",3);
			create_files("/home/thom/asd1/asd2/asd",3);
			create_files("/home/thom/asd2/asd3/asd",3);
			create_files("/home/thom/asd3/asd4/asd",3);
			create_files("/home/thom/asd4/asd5/asd",3);
			create_files("/home/thom/asd5/asd6/asd",3);
			create_files("/home/thom/asd6/asd7/asd",3);
			create_files("/home/thom/asd7/asd8/asd",3);
			create_files("/home/thom/asd8/asd9/asd",3);
			create_files("/home/thom/asd9/asd10/asd",3);
			stop=calculate_time();
			time = (stop-start);
			averagecreate2 +=time;
			pthread_mutex_unlock(&lock);
		}else if(arg==0){
			pthread_mutex_lock(&lock);
			//read 1 file from 10 diffrent catalogues 
			start = calculate_time();
			read_files("/home/thom/asd/asd1/asd",3);
			read_files("/home/thom/asd1/asd2/asd",3);
			read_files("/home/thom/asd2/asd3/asd",3);
			read_files("/home/thom/asd3/asd4/asd",3);
			read_files("/home/thom/asd4/asd5/asd",3);
			read_files("/home/thom/asd5/asd6/asd",3);
			read_files("/home/thom/asd6/asd7/asd",3);
			read_files("/home/thom/asd7/asd8/asd",3);
			read_files("/home/thom/asd8/asd9/asd",3);
			read_files("/home/thom/asd9/asd10/asd",3);
			stop=calculate_time();
			time = (stop-start);
			averageread2 +=time;
			pthread_mutex_unlock(&lock);
		}
		
	}
	totaltimestop = calculate_time();	
	totaltime=(totaltimestop-totaltimestart);
	free(argum);

}
void *test3(int testime){
	double start,stop,timerstart,timerstop,timer;
	int z=0;
	start=calculate_time();
	while(1){
		char home[50] = "/home/thom/fortest3/fortest32/test";
		char nr[2] ="";
		sprintf(nr,"%d",z);
		create_files(strcat(home,nr),1);
		stop=calculate_time();
		if((stop-start) > (testime*1000))
		{	
			break;
		}

		z++;
		
	} 
	printf("Created %d files with %d characters in 5 seconds \n",z,nrofchars);
	printf("Removing %d files with %d characters in 5 seconds... \n",z,nrofchars);
	timerstart=calculate_time();
	for(int i=0; i<=z; i++){
		char home[50] = "/home/thom/fortest3/fortest32/test";
		char nrs[2] ="";
		sprintf(nrs,"%d",i);
		remove_files(strcat(home,nrs),1);
	}
	timerstop=calculate_time();
	timer=(timerstop-timerstart);
	printf("Time to remove %d files: %f milliseconds\n",z,timer);
	
}

void read_files(char path[], int amount) 
{

	FILE *fp=NULL;
	char reader[nrofchars];
	for(int i=1; i<= amount; i++)
	{
		char home[50];
		char nr[2];
		strcpy(home,path);
		sprintf(nr,"%d",i);
		
		fp = fopen(strcat(home,nr),"a");
		fgets(reader,nrofchars,fp);
		

	}
	fclose(fp);
}

