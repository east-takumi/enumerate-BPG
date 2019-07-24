class info{
    public static final int N = 0;
    public static int[] S = new int[2*N];
    public static long num = 0;
    public static int[][] G = new int[N][N];
    public static int p1, p2, p3, p4, p5;
    public static int not_output = 0;
}

class enumerate{
    public int enumerate(int parent, int n) {
        int i, c;
        c=check(n);

        if(c==-1){
            return 0;
        }
        if(c==0){
            not_output++;

        }

        if(c!=0){
            num++;
        // reference(n,parent);
        }

        parent=(int)num;
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
}


public class bipartite {
    public static final int N = 4;
    public static int[] S = new int[2*N];
    public static long num = 0;
    public static int[][] G = new int[N][N];
    public static int p1, p2, p3, p4, p5;
    public static int not_output = 0;

    
    public static int initialize(int n){
        int i;
        for(i=0; i<n; i++){
            S[i]=1;
        }
        for(i=n; i<2*n; i++){
            S[i]=0;
        }
        return 0;
    }

    public static void reverse(int[] Si, int[] Sj, int n){
        int i;
        for(i=0 ; i<2*n ; i++){
            if(Si[2*n-i-1]==1) Sj[i]=0;
            else Sj[i]=1;
        }
    }

    public static void reverse_on_perm(int[] Si,int n){
        int[] Q = new int[N];
        int[] P = new int[N];
        int i;

        Seq2Perm(Q,n);
        for(i=0 ; i<n ; i++) P[Q[i]]=i;
        Perm2Seq(P,Si,n);
    }

    public static void Seq2Perm(int[] Q,int n){
        int i;
        int[] queue = new int[N];
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
      }

    public static void Perm2Seq(int[] P,int[] Si,int n){
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
      }

    public static int is_canonical(int[] Si, int[] Sj, int n){
        for(int i=0; i<n; i++){
            if(Sj[i]!=Si[i]){
                if(Si[i]==0) return -1;
                else return 0;
            }
        }
        return 1;
    }

    public static int check(int n){
        int i, sum=0, c1, c2, c3, c4;
        int[] Q = new int[N];
        int[] S0 = new int[2*N];
        int[] S1 = new int[2*N];
        int[] S2 = new int[2*N];
        int[] S3 = new int[2*N];

        for(i=0; i<2*n; i++) S0[i]=S[i];

        // negative?
        for(i=0; i<2*n-1; i++){
            if(S[i]==1) sum+=1;
            else sum-=1;
            if(sum<0) return -1;
        }

        reverse(S0, S1, n);
        reverse_on_perm(S2, n);
        reverse(S2, S3, n);

        c1=is_canonical(S0,S1,n);
        if(c1==-1) return -1;
        c2=is_canonical(S0,S2,n);
        if(c2==-1) return 0;
        c3=is_canonical(S0,S3,n);
        if(c3==-1) return 0;

        Seq2Perm(Q,n);

        c4=is_canonical(S2,S3,n);
        if(c4==-1) c4=0;
        if(c1==c2 && c1==c3){
            p1++;
            // for(i=0 ; i<n ; i++) System.out.printf("%d ",Q[i]);
            // System.out.printf("\n");
            return 1;
        }
        if(c1 == c4){
            p2++;
            // for(i=0 ; i<n ; i++) fprintf(fp2,"%d ",Q[i]);
            // fprintf(fp2,"\n");
            return 1;
        }

        if(c1 != c2){
            p3++;
            // for(i=0 ; i<n ; i++) fprintf(fp3,"%d ",Q[i]);
            // fprintf(fp3,"\n");
            return 1;
        }
        if(c1 != c3){
            p4++;
            // for(i=0 ; i<n ; i++) fprintf(fp4,"%d ",Q[i]);
            // fprintf(fp4,"\n");
            return 1;
        }
        return 1;
    }

    public static int enumerate(int parent, int n){
        int i, c;
        c=check(n);

        if(c==-1){
            return 0;
        }
        if(c==0){
            not_output++;

        }

        if(c!=0){
            num++;
        // reference(n,parent);
        }

        parent=(int)num;
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
        // return 1;
    }

    public static void main(String[] args) {
        // ability a = new ability();
            int i;
            for(i=3; i <= N; i++){
                num = 0;
                initialize(i);
                enumrate(0,i);
            }
    
            System.out.print(i+" ");
            System.out.print(num+" ");
            System.out.print(p1+" ");
            System.out.print(p2+" ");
            System.out.print(p3+" ");
            System.out.print(p4+" ");
            System.out.println(p5+" ");
    }
    
}




// public class DLL {
//     Node head; // head of list
//     /* Doubly Linked list Node*/
//     class Node {
//         int data;
//         Node prev;
//         Node next;
//         // Constructor to create a new node
//         // next and prev is by default initialized as null
//         Node(int d) { data = d; }
//     }
// }