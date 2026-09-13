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
        printf("Dynamic memory allocation failed!\n");
        exit(1);
    }
    
    newNode->next=NULL;
    newNode->data=data;

    return newNode;
}

struct node* insertStart(struct node* tail,int data) {
    struct node* newNode = createNode(data);
    
    if(tail == NULL){
        newNode->next=newNode;
        return newNode;
    }

    //in cll tail->next is head, 
    newNode->next=tail->next;
    tail->next=newNode; //newNode becomes head

    return tail; //tail remains same
}

struct node* insertEnd(struct node* tail, int data){
    struct node* newNode = createNode(data);

    if(tail==NULL){
        newNode->next=newNode;
        return newNode;
    }

    newNode->next=tail->next;
    tail->next=newNode;

    return newNode; //newNode becomes tail
}

struct node* insertMiddle(struct node* tail,int data,int pos){
    struct node* newNode = createNode(data);

    if(tail==NULL){
        newNode->next=newNode;
        return newNode;
    }


    if(pos==1){
        newNode->next=tail->next;
        tail->next=newNode;
        return tail;
    }

    struct node* ptr=tail->next; //ptr = head

    while(pos!=2){
        if(ptr->next == tail->next){
            printf("Position exceeds allowed range!\n");
            free(newNode);
            return tail;
        }

        ptr=ptr->next;
        pos--;
    }

    newNode->next=ptr->next;
    ptr->next=newNode;

    if(ptr==tail){
        return newNode;
    }

    return tail;
}

struct node* deleteStart(struct node* tail){
    if(tail==NULL){
        printf("LL is empty\n");
        return tail;
    }

    if(tail->next==tail){ //only one node present
        free(tail);
        return NULL;
    }

    struct node* temp=tail->next;
    tail->next=temp->next;
    free(temp);

    return tail;
}

struct node* deleteEnd(struct node* tail){
    if(tail == NULL){
        printf("LL is empty\n");
        return tail;
    }

    if(tail->next == tail){
        free(tail);
        return NULL;
    }

    struct node* ptr=tail->next;

    while(ptr->next!=tail){
        ptr=ptr->next;
    }

    ptr->next=tail->next;

    free(tail);

    return ptr;
}

struct node* deleteMiddle(struct node* tail,int pos){
    if(tail == NULL){
        printf("LL is empty\n");
        return tail;
    }

    if(tail->next == tail && pos == 1){ //if only one node present
        free(tail);
        return NULL;
    }

    if(pos==1){
        struct node* temp = tail->next;
        tail->next=temp->next;
        free(temp);
        return tail;
    }

    struct node* ptr= tail->next;

    while(pos!=2){
        if(ptr->next==tail->next){
            printf("pos outside allowed range!\n");
            return tail;
        }

        ptr=ptr->next;
        pos--;
    }

    if(ptr->next==tail->next){
        printf("pos outside allowed range!\n");
        return tail;
    }

    struct node* temp = ptr->next;
    ptr->next=temp->next;
    
    if(temp==tail){
        free(temp);
        return ptr;
    }
    
    free(temp);
    return tail;
}

int searchElement(struct node* tail,int target){
    if(tail==NULL){
        printf("LL is empty!\n");
        return -1;
    }

    struct node* ptr = tail->next;
    int pos =1;
    
    do{
        if(ptr->data==target){
            return pos;
        }
        ptr=ptr->next;
        pos++;
    }while(ptr!=tail->next);

    //do while because test condition equal to initial

    return -1;
}

struct node* reverseList(struct node* tail){
    if(tail==NULL){
        printf("LL is empty\n");
        return tail;
    }

    if(tail->next==tail){ //only one node present
        return tail;
    }

    struct node* head=tail->next;
    struct node* prev = tail;
    struct node* cur = head;
    struct node* nextNode;

    do{
        nextNode=cur->next;
        cur->next=prev;

        prev=cur;
        cur = nextNode;
    }while(cur!=head);

    return head;
}


void displayList(struct node* tail){

    if(tail == NULL){
        printf("LL is empty\n");
        return;
    }

    struct node* ptr = tail->next;   // head

    do{
        printf("%d->", ptr->data);
        ptr = ptr->next;

    }while(ptr != tail->next);

    printf("(HEAD)\n");
}

struct node* concatLists(struct node* tail1, struct node* tail2){

    if(tail1 == NULL){
        return tail2;
    }

    if(tail2 == NULL){
        return tail1;
    }

    struct node* head1 = tail1->next;
    struct node* head2 = tail2->next;

    tail1->next = head2;
    tail2->next = head1;

    return tail2;
}

int countNodes(struct node* tail){
    
    if(tail==NULL){
        return 0;
    }
    
    int c=0;

    struct node* ptr=tail->next;

    do{
        ptr=ptr->next;
        c++;
    }while(ptr!=tail->next);

    return c;
}

struct node* freeNodes(struct node* tail){

    if(tail == NULL){
        return NULL;
    }

    struct node* head = tail->next; //tail ptr also gets freed so we have to store head to check while cond'n
    struct node* ptr = head;
    struct node* temp;

    do{
        temp = ptr;
        ptr = ptr->next;
        free(temp);

    }while(ptr != head);

    return NULL;
}

int main(){

    struct node* tail = NULL;

    int choice;
    int data;
    int pos;

    while(1){

        printf("\nMENU:\n");
        printf("1. Initialize CLL\n");
        printf("2. Insert Start\n");
        printf("3. Insert End\n");
        printf("4. Insert Middle\n");
        printf("5. Delete Start\n");
        printf("6. Delete End\n");
        printf("7. Delete Middle\n");
        printf("8. Search Element\n");
        printf("9. Reverse List\n");
        printf("10. Display List\n");
        printf("11. Concatenate Lists\n");
        printf("12. Count Nodes\n");
        printf("13. Free List\n");
        printf("14. Exit\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice){

            case 1:
                printf("Enter data for first node: ");
                scanf("%d",&data);

                tail = createNode(data);
                tail->next = tail;
                break;

            case 2:
                printf("Enter data: ");
                scanf("%d",&data);

                tail = insertStart(tail,data);
                break;

            case 3:
                printf("Enter data: ");
                scanf("%d",&data);

                tail = insertEnd(tail,data);
                break;

            case 4:
                printf("Enter position: ");
                scanf("%d",&pos);

                printf("Enter data: ");
                scanf("%d",&data);

                tail = insertMiddle(tail,data,pos);
                break;

            case 5:
                tail = deleteStart(tail);
                break;

            case 6:
                tail = deleteEnd(tail);
                break;

            case 7:
                printf("Enter position: ");
                scanf("%d",&pos);

                tail = deleteMiddle(tail,pos);
                break;

            case 8:{
                printf("Enter element to search: ");
                scanf("%d",&data);

                int index = searchElement(tail,data);

                if(index == -1){
                    printf("Element not found\n");
                }
                else{
                    printf("Element found at position %d\n",index);
                }

                break;
            }

            case 9:
                tail = reverseList(tail);
                printf("List reversed\n");
                break;

            case 10:
                printf("CLL: ");
                displayList(tail);
                break;

            case 11:{
                struct node* tail2 = NULL;
                int n;

                printf("Enter number of nodes in second list: ");
                scanf("%d",&n);

                for(int i=0;i<n;i++){
                    printf("Enter data: ");
                    scanf("%d",&data);

                    tail2 = insertEnd(tail2,data);
                }

                tail = concatLists(tail,tail2);

                printf("Lists concatenated\n");
                break;
            }

            case 12:
                printf("Count: %d\n",countNodes(tail));
                break;

            case 13:
                tail = freeNodes(tail);
                printf("List freed\n");
                break;

            case 14:
                tail = freeNodes(tail);
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}