#include<stdio.h>

#define N 16

int S[2*N];
long num=0;
int G[N][N];
int p1,p2,p3,p4,p5;
int not_output=0;
FILE *fp1,*fp2,*fp3,*fp4,*fp5;

//Initialize of Sequence
int initialize(int n)
{
  int i;
  for(i=0 ; i<n ; i++){
    S[i]=1;
  }
  for(i=n ; i<2*n ; i++){
    S[i]=0;
  }
  return 0;
}


//Initialize of Graph
int initializeG(int n)
{
  int i,j;
  for(i=0 ; i<n ; i++){
    for(j=0 ; j<n ; j++){
      G[i][j]=0;
    }
  }
  return 0;
}

//Sequence to graph
int Seq2Graph(int n)
{
  int left=0,right=0;
  int i,j;
  int S2[2*N];
  int num_x=0;

  for(i=0 ; i<2*n ; i++)
    if(S[i]==1 && S[i+1]==1) num_x++;
  
  initializeG(n);
  for(i=0 ; i<2*n ; i++){
    if(S[i]==0 && S[i-1]==1){
      S2[i]=-num_x;
      S2[i-1]=-num_x;
      num_x++;
    }
    else S2[i]=S[i];
  }
  /*
  for(i=0 ; i<2*n ; i++)
    printf("%d ",S2[i]);
  printf("\n");
  */
  //left=num_x;
  //right=num_x;
  for(i=0 ; i<2*n ; i++){
    if(S2[i]==1) left++;
    else if(S2[i]==0) right++;
    else{
      //right -> left  adjacent
      for(j=right ; j<left ; j++){
	G[-S2[i]][j]=1;
	G[j][-S2[i]]=1;
      }
      i++;
    }
  }
  return 1;
}



//See Sequence and Graph
int reference(int n,int parent)
{
  int i,j;
  printf("parent number: %d\n",parent);
  printf("graph number : %d\n",num);
  for(i=0 ; i<2*n ; i++) printf("%d ",S[i]);
  printf("\n");

  Seq2Graph(n);
  for(i=0 ; i<n ; i++){
    printf("%d -> ",i);
    for(j=0 ; j<n ; j++){
      if(G[i][j]==1) printf("%d,",j);
    }
    printf("\n");
  }

  printf("\n\n");
  return 0;
}



int Seq2Perm(int *Q,int n)
{
  int i;
  int queue[N];
  int head,tail;
  head=tail=0;
  int num=0;
  int q=0;

  for(i=0 ; i<2*n ; i++){
    if(S[i]==1){
      queue[head]=num;
      num++;head++;
    }
    //Vertex y
    else if(S[i-1]==1){
      head--;
      Q[q]=queue[head];
      q++;
    }
    //Vertex x
    else{
      Q[q]=queue[tail];
      tail++;
      q++;
    }
  }

  return 0;
}

int Perm2Seq(int *P,int *Si,int n)
{
  int i,j;
  int k=0,v=0;

  for(i=0 ; i<n ; i++){
    if(P[i]>i){
      for(j=v ; j<=P[i] ; j++){
	Si[k]=1; k++;
      }
      Si[k]=0; k++;
      v=P[i]+1;
    }
    else{
      Si[k]=0; k++;
    }
  }

  return 0;
}


// Check canonical
int is_canonical(int *Si,int *Sj,int n)
{
  int i;

  for(i=0 ; i<n ; i++){
    //canonical?
    if(Sj[i]!=Si[i]){
      if(Si[i]==0) return -1;
      else return 0;
    }
  }
  return 1;
}


int reverse(int *Si, int *Sj, int n)
{
  int i;
  for(i=0 ; i<2*n ; i++){
    if(Si[2*n-i-1]==1) Sj[i]=0;
    else Sj[i]=1;
  }
  return 0;
}


int reverse_on_perm(int *Si,int n)
{
  int P[N],Q[N];
  int i;

  Seq2Perm(Q,n);

  /*
  printf("Q= ");
  for(i=0 ; i<n ; i++){
    printf("%d ",Q[i]);
  }
  printf("\n");
  */
  for(i=0 ; i<n ; i++) P[Q[i]]=i;
  /*
  printf("P= ");
  for(i=0 ; i<n ; i++) printf("%d ",P[i]);
  printf("\n");
  */
  Perm2Seq(P,Si,n);
  /*
  printf("S= ");
  for(i=0 ; i<2*n ; i++) printf("%d ",S[i]);
  printf("\n");

  printf("S2= ");
  for(i=0 ; i<2*n ; i++) printf("%d ",Si[i]);
  printf("\n");
  */
  return 0;
}



//Check canonical and non-negative
int check(int n)
{
  int i,sum=0,c1,c2,c3,c4;
  int Q[N];
  int S0[2*N],S1[2*N],S2[2*N],S3[2*N];
  /*
    S0=S, S1 is reverse of S0
    S2 is reverse on permutation of S0
    S3 is reverse of S2
   */
  for(i=0 ; i<2*n ; i++) S0[i]=S[i];
    
  for(i=1 ; i<2*n-1 ; i++){
    //non-negative?
    if(S[i]==1) sum++;
    else sum--;
    if(sum<0) return -1;
  }

  reverse(S0,S1,n);
  reverse_on_perm(S2,n);
  reverse(S2,S3,n);
  
  c1=is_canonical(S0,S1,n);
  if(c1==-1) return -1;
  c2=is_canonical(S0,S2,n);
  if(c2==-1) return 0;
  c3=is_canonical(S0,S3,n);
  if(c3==-1) return 0;

  Seq2Perm(Q,n);

  c4=is_canonical(S2,S3,n);
  if(c4==-1) c4=0;
  if(c1 && c2 && c3){
    p1++;
    for(i=0 ; i<n ; i++) fprintf(fp1,"%d ",Q[i]);
    fprintf(fp1,"\n");
    return 1;
  }
  if(c1 && c4){
    p2++;
    for(i=0 ; i<n ; i++) fprintf(fp2,"%d ",Q[i]);
    fprintf(fp2,"\n");
    return 1;
  }

  if(!c1 && c2){
    p3++;
    for(i=0 ; i<n ; i++) fprintf(fp3,"%d ",Q[i]);
    fprintf(fp3,"\n");
    return 1;
  }
  if(!c1 && c3){
    p4++;
    for(i=0 ; i<n ; i++) fprintf(fp4,"%d ",Q[i]);
    fprintf(fp4,"\n");
    return 1;
  }
  /*
  p5++;
  for(i=0 ; i<2*n ; i++) fprintf(fp5,"%d ",S[i]);
  fprintf(fp5,"\n");
  */
  return 1;
}


//Enumerate Sequence
int enumerate(int parent,int n)
{
  int i,c;
  c=check(n);
  if(c==-1){
    //printf("Not non-negative\n");
    return 0;
  }
  if(c==0){
    not_output++;
    //printf("Not output the sequence\n");
    //for(i=0 ; i<2*n ; i++) printf("%d ",S[i]);
  }

  if(c!=0){
    num++;
    //reference(n,parent);
  }
  
  parent=num;
  for(i=0 ; i<2*n-1 ; i++){
    if(S[i]==1 && S[i+1]==0){
      S[i]=0;S[i+1]=1;
      enumerate(parent,n);
      S[i]=1;S[i+1]=0;
      break;
    }
  }
  for(i=0 ; i<2*n-2 ; i++){
    if(S[i]==0 && S[i+1]==1){
      if(S[i+2]==0){
	S[i+1]=0;S[i+2]=1;
	enumerate(parent,n);
	S[i+1]=1;S[i+2]=0;
      }
      break;
    }
  }
  return 1;
}


int main()
{
  int i;
  FILE *fp;

  fp=fopen("NumberBPG","w");
  fp1=fopen("pattern1","w");
  fp2=fopen("pattern2","w");
  fp3=fopen("pattern3","w");
  fp4=fopen("pattern4","w");
  fp5=fopen("pattern5","w");

  //fprintf(fp,"Number of\n");
  fprintf(fp,"Vertex\tGraph\tP1\tP2\tP3\tP4\tP5\n");
  printf("Vertex\tGraph\tP1\tP2\tP3\tP4\tP5\n");
  for(i=3 ; i<=N ; i++){
    fprintf(fp1,"Number of Vertices: %d\n",i);
    fprintf(fp2,"Number of Vertices: %d\n",i);
    fprintf(fp3,"Number of Vertices: %d\n",i);
    fprintf(fp4,"Number of Vertices: %d\n",i);
    fprintf(fp5,"Number of Vertices: %d\n",i);

    num=0;
    //not_output=0;
    p1=p2=p3=p4=p5=0;
    //Initialize
    initialize(i);
    enumerate(0,i);
    //printf("number of vertices: %d\n",i);
    //printf("number of graphs: %d\n",num);
    //printf("number of symmetry: %d\n",symmetry);
    fprintf(fp,"%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i,num,p1,p2,p3,p4,p5);
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%d\n",i,num,p1,p2,p3,p4,p5);
  }
  return 0;
}
