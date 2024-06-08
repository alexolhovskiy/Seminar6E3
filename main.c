#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int num;
    struct node*left,*right,*parent;
}node;


int findMed(int*arr, int size){
    int m_num=0;
    for(int i=0;i<size;i++){
        m_num=0;
        for(int j=0;j<size;j++){
            if(arr[i]>=arr[j]){
                m_num++;
            }
        }
        if(m_num==size/2+1){
            //printf("Median: %d\n",arr[i]);
            return arr[i];
        }
    }
    return 0;
}


node* makeTree(int*arr,int size,node*root){
    int half=size/2,n=0;
    int*half_arr_larger=(int*)malloc(sizeof(int)*(size-half));
    int*half_arr_lower=(int*)malloc(sizeof(int)*half);

    for(int i=0;i<size;i++){
        if(arr[i]>root->num){
            half_arr_larger[n]=arr[i];
            n++;
            //printf("%d ",arr[i]);
        }
    }

    node*el_larger=(node*)malloc(sizeof(node));
    el_larger->num=findMed(half_arr_larger,n);
    //printf(" Median %d\n",el_larger->num);
    el_larger->left=NULL;
    el_larger->right=NULL;
    if(n>1){
        el_larger=makeTree(half_arr_larger,n,el_larger);
    }
    el_larger->parent=root;
    root->right=el_larger;

    n=0;
    for(int i=0;i<size;i++){
        if(arr[i]<root->num){
            half_arr_lower[n]=arr[i];
            n++;
            //printf("%d ",arr[i]);
        }
    }

    node*el_lower=(node*)malloc(sizeof(node));
    el_lower->num=findMed(half_arr_lower,n);
    //printf(" Median %d\n",el_lower->num);
    el_lower->left=NULL;
    el_lower->right=NULL;
    if(n>1){
        el_lower=makeTree(half_arr_lower,n,el_lower);
    }
    el_lower->parent=root;
    root->left=el_lower;


    return root;
}


int treeTraversal(node*root){
    int res=0;
    if(root!=NULL){
        res=root->num;
        if(root->left!=NULL){
           res+=treeTraversal(root->left);
        }
        if(root->right!=NULL){
           res+=treeTraversal(root->right);
        }
    }
    return res;
}


int main()
{
    printf("Hello world!\n");

    int arr[]={1,3,5,6,7,10,13,15,18};
    //int arr[]={11,3,23,6,7,17,10,13,15,18};
    //printf("%d\n",findMed(arr,sizeof(arr)/sizeof(int)));

    node*root=(node*)malloc(sizeof(node));
    root->num=10;//findMed(arr,sizeof(arr)/sizeof(int));
    root->left=NULL;
    root->right=NULL;
    root->parent=NULL;
    root=makeTree(arr,sizeof(arr)/sizeof(int),root);


    printf("Sum=%d\n",treeTraversal(root));

    return 0;
}
