#include<stdio.h>
#include<stdlib.h>
struct Node{
    int data;
    struct Node *next;
};
struct Node* createNode(int data){
    struct Node *newnode = malloc(sizeof(struct Node));
    newnode->data = data;
    newnode->next =NULL;
    return newnode;
} 
void insertAtEnd(struct Node **head,int data){
    struct Node *newnode = createNode(data);
    
    if(*head==NULL){
        *head = newnode;
        return;
    }
    struct Node *temp = *head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=newnode;
    
}
void display(struct Node **head){
    struct Node *temp = *head;
    while(temp!=NULL){
        printf("%d ",temp->data);
        temp=temp->next;
    }
}
int main()
{
    struct Node *head=NULL;
    insertAtEnd(&head,10);
    insertAtEnd(&head,15);
    display(&head);
    return 0;
}