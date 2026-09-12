#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
    struct node* prev;
};

struct node* createNode(int data){
    struct node* newNode= (struct node*)malloc(sizeof(struct node));
    
    if(newNode==NULL){
        printf("Dynamic memory allocation failed!\n");
        exit(1);
    }
    
    newNode->next=NULL;
    newNode->prev=NULL;
    newNode->data=data;

    return newNode;
}

struct node* insertStart(struct node* head,int data) {
    struct node* newNode = createNode(data);

    if(head!=NULL){
        head->prev=newNode; //only if head isnt null set its prev to new Node
    }
    newNode->next=head; 
    //prev of newNode is already null
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
    newNode->prev=ptr;

    //if head isnt null new node is appended to the end and head remains same

    return head;
}

struct node* insertMiddle(struct node* head, int data, int pos){
    struct node* newNode = createNode(data);


    if(head==NULL){
        return newNode;
    }

    if(pos==1){
        newNode->next=head;
        head->prev=newNode;
        return newNode; //if head is null or pos=1 new node becomes the new head
    }

    //pos is the position of new node

    struct node* ptr=head;

    while(pos!=2){

        if(ptr->next == NULL){
            printf("Position exceeds allowed range!\n");
            free(newNode);
            return head;
        }

        ptr=ptr->next;
        pos--;
    }

    if(ptr->next!=NULL){
        ptr->next->prev=newNode;
    }
    newNode->next=ptr->next;
    newNode->prev=ptr;
    ptr->next=newNode;


    //if head isnt null new node is inserted in its pos and head remains same
    return head;
}

struct node* deleteStart(struct node* head){
    if(head==NULL){
        printf("LL is empty\n");
        return head;
    }

    struct node* temp= head;
    head= temp->next;

    if(head!=NULL){
        head->prev=NULL;
    }

    free(temp);

    return head;
}

//no change needed for dll
struct node* deleteEnd(struct node* head){
    if(head==NULL){
        printf("LL is empty\n");
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
        printf("LL is empty!\n");
        return head;
    }

    if(pos==1){ //if we are deleting first node
        struct node* temp = head;
        head = head->next;

        if(head!=NULL){
            head->prev=NULL;
        }
        
        free(temp);
        return head;
    }

    struct node* ptr=head;

    while(pos!=2){

        if(ptr->next==NULL){
            printf("pos outside allowed range!\n");
            return head;
        }

        ptr=ptr->next;
        pos--;
    }


    if(ptr->next==NULL){
        printf("pos outside allowed range!\n");
        return head;
    }

    struct node* temp=ptr->next;

    ptr->next=temp->next;

    if(temp->next!=NULL){
        temp->next->prev=ptr;
    }
    

    free(temp);

    return head;
}


//works with no changes 
int searchElement(struct node* head,int target){
    if(head==NULL){
        printf("LL is empty!\n");
        return -1;
    }

    struct node* ptr = head;
    int pos =1;
    while(ptr!=NULL){
        if(ptr->data==target){
            return pos;
        }
        ptr=ptr->next;
        pos++;
    }

    return -1;
}


struct node* reverseList(struct node* head){
    
    if(head==NULL){
        printf("List is empty\n");
        return head;
    }
    
    struct node* curNode = head;
    struct node* prevNode= NULL;
    struct node* nextNode=NULL;

    while(curNode){
        nextNode=curNode->next;
        curNode->next=prevNode;
        curNode->prev=nextNode; //only this line added
        prevNode=curNode;
        curNode=nextNode;
    }

    return prevNode;
}

void displayList(struct node* head){

    if(head==NULL){
        printf("LL is empty\n");
        return;
    }

    struct node* ptr=head;

    while(ptr!=NULL){
        printf("%d<->",ptr->data);
        ptr=ptr->next;
    }

    printf("NULL \n");
}


struct node* concantLists(struct node* head1,struct node* head2){
    if(head1==NULL){
        return head2;
    }

    if(head2==NULL){
        return head1;
    }

    struct node* ptr1=head1;
    
    while(ptr1->next!=NULL){
        ptr1 = ptr1->next;
    }

    ptr1->next=head2;//connects entire sll2 to end of sll1
    head2->prev=ptr1;

    return head1;
}


//no change needed
int countNodes(struct node* head){
    int c=0;
    struct node* ptr = head;

    while(ptr!=NULL){
        ptr=ptr->next;
        c++;
    }

    return c;
}

//no change needed
struct node* freeNodes(struct node* head){
    
    if(head==NULL){
        return head;
    }
    
    struct node* ptr=head;
    struct node* temp=NULL;
    while(ptr!=NULL){
        temp = ptr;
        ptr=ptr->next;
        free(temp);
    }

    return NULL;
    
}

//Forward and Reverse Display of DLL​