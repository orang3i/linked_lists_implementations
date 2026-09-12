#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
};


struct node* createNode(int data){
    struct node* newNode= (struct node*)malloc(sizeof(struct node));
    
    if(newNode==NULL){
        printf("Dynamic memory allocation failed!");
        exit(1);
    }
    
    newNode->next=NULL;
    newNode->data=data;

    return newNode;
}

struct node* insertStart(struct node* head,int data) {
    struct node* newNode = createNode(data);
    newNode->next=head; 
    //if head isnt null, new node points to old head and new node becomes new head
    //if head is null new node points to null and new node becomes new head
    return newNode;
}

struct node* insertEnd(struct node* head, int data){
    struct node* newNode = createNode(data);

    if(head==NULL){
        return newNode; //if head is null, new node becomes the new head
    }

    struct node* ptr=head;

    while(ptr->next!=NULL){
        ptr=ptr->next;
    }

    ptr->next=newNode;

    //if head isnt null new node is appended to the end and head remains same

    return head;
}

struct node* insertMiddle(struct node* head, int data, int pos){
    struct node* newNode = createNode(data);

    if(head==NULL || pos==1){
        newNode->next=head;
        return newNode; //if head is null or pos=1 new node becomes the new head
    }

    //pos is the position of new node

    struct node* ptr=head;

    while(pos!=2){

        if(ptr->next == NULL){
            printf("Position exceeds allowed range!");
            return head;
        }

        ptr=ptr->next;
        pos--;
    }

    newNode->next=ptr->next;
    ptr->next=newNode;


    //if head isnt null new node is inserted in its pos and head remains same
    return head;
}

struct node* deleteStart(struct node* head){
    if(head==NULL){
        printf("LL is empty");
        return head;
    }

    struct node* temp= head;
    head= temp->next;

    free(temp);

    return head;
}

struct node* deleteEnd(struct node* head){
    if(head==NULL){
        printf("LL is empty");
        return head;
    }

    if(head->next == NULL){ //if only one node is present
        free(head);
        return NULL;
    }

    struct node* ptr= head;
    struct node*prev;
    while(ptr->next!=NULL){
        prev=ptr;
        ptr=ptr->next;
    }

    //head->......->prev->ptr->null
    //will become
    //head->.....->prev->null

    prev->next=NULL;
    free(ptr);

    return head;
}

struct node* deleteMiddle(struct node* head,int pos){
    if(head == NULL){
        printf("LL is empty!");
        return head;
    }

    if(pos==1){ //if we are deleting first node
        struct node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    struct node* ptr=head;

    while(pos!=2){

        if(ptr->next==NULL){
            printf("pos outside allowed range!");
            return head;
        }

        ptr=ptr->next;
        pos--;
    }


    if(ptr->next==NULL){
        printf("pos outside allowed range!");
        return head;
    }

    struct node* temp=ptr->next;

    ptr->next=temp->next;

    free(temp);

    return head;
}