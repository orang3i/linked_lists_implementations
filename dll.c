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

void displayBoth(struct node* head){

    if(head==NULL){
        printf("LL is empty\n");
        return;
    }

    struct node* ptr= head;

    printf("Forward: ");

    while(ptr->next != NULL){
        printf("%d<->",ptr->data);
        ptr=ptr->next;
    }

    printf("%d<->NULL\n",ptr->data);

    printf("Reverse: ");

    while(ptr!=NULL){
        printf("%d<->",ptr->data);
        ptr=ptr->prev;
    }

    printf("NULL\n");
}



int main(){

    printf("MENU:\n");
    printf("1.Initialize DLL\n");
    printf("2.Insert Start\n");
    printf("3.Insert End\n");
    printf("4.Insert Middle\n");
    printf("5.Delete Start\n");
    printf("6.Delete End\n");
    printf("7.Delete Middle\n");
    printf("8.Search Element\n");
    printf("9.Reverse List\n");
    printf("10.Display List\n");
    printf("11.Concat Lists\n");
    printf("12.Count Nodes\n");
    printf("13.Forward and Reverse Display\n");
    printf("14.Free List\n");
    printf("15.Exit\n");

    struct node* head = NULL;

    int data;
    int pos;

    while(1){

        int choice;

        printf("\nEnter your choice: ");
        scanf("%d",&choice);

        switch(choice){

            case 1:
                printf("Enter data for first element: ");
                scanf("%d",&data);

                head = createNode(data);
                break;

            case 2:
                printf("Enter data to insert at start: ");
                scanf("%d",&data);

                head = insertStart(head,data);
                break;

            case 3:
                printf("Enter data to insert at end: ");
                scanf("%d",&data);

                head = insertEnd(head,data);
                break;

            case 4:
                printf("Enter pos: ");
                scanf("%d",&pos);

                printf("Enter data to insert: ");
                scanf("%d",&data);

                head = insertMiddle(head,data,pos);
                break;

            case 5:
                head = deleteStart(head);
                break;

            case 6:
                head = deleteEnd(head);
                break;

            case 7:
                printf("Enter pos: ");
                scanf("%d",&pos);

                head = deleteMiddle(head,pos);
                break;

            case 8:{
                printf("Enter element to search: ");
                scanf("%d",&data);

                int index = searchElement(head,data);

                if(index == -1){
                    printf("Element not found\n");
                }
                else{
                    printf("Element found at position %d\n",index);
                }

                break;
            }

            case 9:
                head = reverseList(head);
                printf("List reversed\n");
                break;

            case 10:
                printf("DLL: ");
                displayList(head);
                break;

            case 11:{
                struct node* head2 = NULL;
                int n;

                printf("Enter number of elements in second list: ");
                scanf("%d",&n);

                for(int i=0;i<n;i++){
                    printf("Enter data: ");
                    scanf("%d",&data);

                    head2 = insertEnd(head2,data);
                }

                head = concantLists(head,head2);

                printf("Lists concatenated\n");
                break;
            }

            case 12:
                printf("Count: %d\n",countNodes(head));
                break;

            case 13:
                displayBoth(head);
                break;

            case 14:
                head = freeNodes(head);
                printf("List freed\n");
                break;

            case 15:
                head = freeNodes(head);
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}