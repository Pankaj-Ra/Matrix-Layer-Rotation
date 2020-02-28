#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>


typedef struct single_link_list
{                    
    int num;
    struct single_link_list *next;
}SList;

SList* sl_create_node(void)
{
    return (malloc(sizeof(SList)));
}

int insert_last(SList **head, SList **tail,int info)
{

    SList *new = sl_create_node();   

    new->num = info;
    new->next = NULL;

    if ((*head)==NULL)
    {
        (*head) = (*tail) = new;
        return 0;
    }

    (*tail)->next = new;
    (*tail) = new;

    return 0;
}

int main() {

    int M, N, R;
    scanf("%d %d %d",&M,&N,&R);
    
    int **A = calloc(M,sizeof(int*));    
    for(int i = 0; i < M; i++){
        A[i] = calloc(N,sizeof(int));
    }
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){            
            scanf("%d",&A[i][j]);            
        }
    }
    int circle = (M<N)?M/2:N/2;
    SList **H = calloc(circle,sizeof(SList));
    SList **T = calloc(circle,sizeof(SList));
    //Creating a circular LinkList for each LvL
    for(int i = 0; i < circle; i++){
        //TopLeft to TopRight
        for(int j = i; j < N-i; j++){  
            insert_last(&H[i],&T[i], A[i][j]);            
        }
        //TopRight to bottomRight
        for(int j = i+1; j < M-i-1; j++){
            insert_last(&H[i],&T[i], A[j][N-i-1]);
        }
        //BottomRight to BottomLeft
        for(int j = N-i-1; j >= i; j--){
            insert_last(&H[i],&T[i], A[M-i-1][j]);
        }
        //LeftBottom to LeftTop
        for(int j = M-i-2; j > i; j--){
            insert_last(&H[i],&T[i], A[j][i]);
        }
        T[i]->next = H[i];
    }
    //Rotate each linkList by R
    for(int i = 0; i < circle; i++){
        //no. of nodes in each LvL
        int ci = 2*(M-2*i)+2*(N-(2*i +2));
        int r = R%ci;
        while(r--){
            H[i] = H[i]->next;
            T[i] = T[i]->next;
        }
    }  
    
    //populate A with rotated matrix same as above
    for(int i = 0; i < circle; i++){                
        for(int j = i; j < N-i; j++){              
            A[i][j] = H[i]->num;
            H[i] = H[i]->next;
        }
        for(int j = i+1; j < M-i-1; j++){            
            A[j][N-i-1] = H[i]->num;
            H[i] = H[i]->next;
        }
        for(int j = N-i-1; j >= i; j--){            
            A[M-i-1][j] = H[i]->num;
            H[i] = H[i]->next;
        }
        for(int j = M-i-2; j > i; j--){            
            A[j][i] = H[i]->num;
            H[i] = H[i]->next;
        }        
    }
    for(int i = 0; i < M; i++){
        for(int j = 0; j < N; j++){            
            printf("%d ",A[i][j]);            
        }
        printf("\n");
    }
    return 0;
}
