#include "distdtw.h"

//DYNAMIC PROGRAMMING

double dtwdp(double **A,double **B,int test_pos,int train_pos,int size,double c){
	double **p;
	int z,t;
	double temp,temp1,temp2,temp3;
	p=malloc(size*sizeof(double*));
	if(p==NULL){
		printf("Memory problem\n");
		return -2.0;
	}
	for(z=0;z<size;z++){
		p[z]=malloc(size*sizeof(double));
		if(p[z]==NULL){
			printf("Memory problem\n");
			return -2.0;
		}
	}
	p[0][0]=(A[train_pos][1]-B[test_pos][1])*(A[train_pos][1]-B[test_pos][1]);
	for(t=1;t<size;t++){
		if(t>c){
			p[0][t]=1.0/0.0;
		}
		else{
			p[0][t]=(A[train_pos][1]-B[test_pos][t+1])*(A[train_pos][1]-B[test_pos][t+1])+p[0][t-1];
		}
	}
	for(z=1;z<size;z++){
		if(z>c){
			p[z][0]=1.0/0.0;
		}
		else{
			p[z][0]=(A[train_pos][z+1]-B[test_pos][1])*(A[train_pos][z+1]-B[test_pos][1])+p[z-1][0];
		}
	}
	for(z=1;z<size;z++){
		for(t=1;t<size;t++){
			temp=(A[train_pos][z+1]-B[test_pos][t+1])*(A[train_pos][z+1]-B[test_pos][t+1]);
			temp1=p[z-1][t];
			temp2=p[z][t-1];
			temp3=p[z-1][t-1];
			if(temp1<temp2){
				if(temp1<temp3){
					if((z-t>0 && z-t>c) || (z-t<0 && t-z>c)){
						p[z][t]=1.0/0.0;
					}
					else{
						p[z][t]=temp+temp1;
					}
				}
				else{
					if((z-t>0 && z-t>c) || (z-t<0 && t-z>c)){
						p[z][t]=1.0/0.0;
					}
					else{
						p[z][t]=temp+temp3;
					}
				}
			}
			else{
				if(temp2<temp3){
					if((z-t>0 && z-t>c) || (z-t<0 && t-z>c)){
						p[z][t]=1.0/0.0;
					}
					else{
						p[z][t]=temp+temp2;
					}
				}
				else{
					if((z-t>0 && z-t>c) || (z-t<0 && t-z>c)){
						p[z][t]=1.0/0.0;
					}
					else{
						p[z][t]=temp+temp3;
					}
				}
			}
		}
	}
	double value=p[size-1][size-1];
	for(z=0;z<size;z++){
		free(p[z]);
	}
	free(p);
	return value;
}

//RECURSION

double dtwrec(double **A,double **B,int test_pos,int train_pos,int i,int j,double c){
	double temp,temp1,temp2,temp3;
	if(i==1 && j==1){
		return (A[train_pos][1]-B[test_pos][1])*(A[train_pos][1]-B[test_pos][1]);
	}
	else if(j==1){
		if(j>c){
			return 1.0/0.0 + dtwrec(A,B,test_pos,train_pos,i-1,1,c);
		}
		else{
			return (A[train_pos][i]-B[test_pos][1])*(A[train_pos][i]-B[test_pos][1])+dtwrec(A,B,test_pos,train_pos,i-1,1,c);
		}
	}
	else if(i==1){
		if(i>c){
			return 1.0/0.0 + dtwrec(A,B,test_pos,train_pos,1,j-1,c);
		}
		else{
			return (A[train_pos][1]-B[test_pos][j])*(A[train_pos][1]-B[test_pos][j])+dtwrec(A,B,test_pos,train_pos,1,j-1,c);
		}
	}
	else{
		temp=(A[train_pos][i]-B[test_pos][j])*(A[train_pos][i]-B[test_pos][j]);
		temp1=dtwrec(A,B,test_pos,train_pos,i-1,j,c);
		temp2=dtwrec(A,B,test_pos,train_pos,i,j-1,c);
		temp3=dtwrec(A,B,test_pos,train_pos,i-1,j-1,c);
		if(temp1<temp2){
			if(temp1<temp3){
				if((i-j>0 && i-j>c) || (i-j<0 && j-i>c)){
					return 1.0/0.0 +dtwrec(A,B,test_pos,train_pos,i-1,j,c);
				}
				else{
					return temp+dtwrec(A,B,test_pos,train_pos,i-1,j,c);
				}
			}
			else{
				if((i-j>0 && i-j>c) || (i-j<0 && j-i>c)){
					return 1.0/0.0 + dtwrec(A,B,test_pos,train_pos,i-1,j,c);
				}
				else{
					return temp+dtwrec(A,B,test_pos,train_pos,i-1,j-1,c);
				}
			}
		}
		else{
			if(temp2<temp3){
				if((i-j>0 && i-j>c) || (i-j<0 && j-i>c)){
					return 1.0/0.0 +dtwrec(A,B,test_pos,train_pos,i,j-1,c);
				}
				else{
					return temp+dtwrec(A,B,test_pos,train_pos,i,j-1,c);
				}
			}
			else{
				if((i-j>0 && i-j>c) || (i-j<0 && j-i>c)){
					return 1.0/0.0 + dtwrec(A,B,test_pos,train_pos,i,j-1,c);
				}
				else{
					return temp+dtwrec(A,B,test_pos,train_pos,i-1,j-1,c);
				}
			}
		}
	}
}

//WRAPPER

double wrapper(double **A,double **B,int test_pos, int train_pos,int i,double c){
	#ifdef REC
	return dtwrec(A,B,test_pos,train_pos,i-1,i-1,c);
	#else
	return dtwdp(A,B,test_pos,train_pos,i,c);
	#endif
}
