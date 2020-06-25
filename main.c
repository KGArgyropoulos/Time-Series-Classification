#include "distdtw.h"

int main(int argc,char *argv[]){
	//limit c
	double c;
	if(argc==1){
		c=1.0/0.0;
	}
	else{
		c=atof(argv[1]);
	}
	//training set
	int training_capacity,training_size,i,j;
	scanf("%d",&training_capacity);
	scanf("%d",&training_size);
	double a,**A;
	A=(double **)malloc(training_capacity*sizeof(double*));
	if(A==NULL){
		printf("Memory problem\n");
		return -1;
	}
	for(j=0;j<training_capacity;j++){
		A[j]=(double *)malloc((training_size+1)*sizeof(double));
		if(A[j]==NULL){
			printf("Memory problem\n");
			return -1;
		}
	}
	for(j=0;j<training_capacity;j++){
		for(i=0;i<=training_size;i++){
			scanf("%lf",&a);
			A[j][i]=a;
		}
	}
	//test set
	int test_capacity,test_size;
	scanf("%d",&test_capacity);
	scanf("%d",&test_size);
	//check for size
	if(test_size!=training_size){
		printf("Bad input:Test size isn't equal to training size\n");
		return -3;
	}
	
	double b,**B;
	B=(double **)malloc(test_capacity*sizeof(double*));
	if(B==NULL){
		printf("Memory problem\n");
		return -1;
	}
	for(j=0;j<test_capacity;j++){
		B[j]=(double *)malloc((test_size+1)*sizeof(double));
		if(B[j]==NULL){
			printf("Memory problem\n");
			return -1;
		}
	}
	for(j=0;j<test_capacity;j++){
		for(i=0;i<=test_size;i++){
			scanf("%lf",&b);
			B[j][i]=b;
		}
	}
	//calculation of minimum distance
 	int s=0;
	int err=0;
	double min_dtw;
	for(j=0;j<test_capacity;j++){
		double *temp;
		temp=(double *)malloc(training_capacity*sizeof(double));		
		for(i=0;i<training_capacity;i++){
			temp[i]=wrapper(A,B,j,i,test_size,c);
		}
		int row=0;
		min_dtw=temp[0];
		for(i=1;i<training_capacity;i++){
			if(temp[i]<min_dtw){
				min_dtw=temp[i];
				row=i;
			}
		}
		if(A[row][0]!=B[j][0]){
			err++;
		}
		printf("Series %d (class %d) is nearest (distance %f) to series %d (class %d)\n",j+1,(int)B[j][0],min_dtw,row+1,(int)A[row][0]);
		s++;
		free(temp);
	}
	printf("Error rate:%f\n",(double)err/(double)s);
	
	for(i=0;i<training_capacity;i++){
		free(A[i]);
	}
	free(A);
	for(j=0;j<test_capacity;j++){
		free(B[j]);
	}
	free(B);
	return 0;
}
