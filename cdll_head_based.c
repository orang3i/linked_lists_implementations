#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
    struct node* prev;
};

struct node* createNode(int data){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    if(newNode == NULL){
        printf("Dynamic memory allocation failed!\n");
        exit(1);
    }

    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}


/* INSERT AT START */

struct node* insertStart(struct node* head, int data){
    struct node* newNode = createNode(data);

    if(head == NULL){
        newNode->next = newNode;
        newNode->prev = newNode;
        return newNode;
    }

    struct node* tail = head->prev;

    newNode->next = head;       //new node -> old head
    newNode->prev = tail;       //tail <- new node

    tail->next = newNode;       //tail -> new head
    head->prev = newNode;       //old head <- new head

    return newNode;             //newNode becomes head
}


/* INSERT AT END */

struct node* insertEnd(struct node* head, int data){
    struct node* newNode = createNode(data);

    if(head == NULL){
        newNode->next = newNode;
        newNode->prev = newNode;
        return newNode;
    }

    struct node* tail = head->prev;

    newNode->next = head;       //new tail -> head
    newNode->prev = tail;       //old tail <- new tail

    tail->next = newNode;       //old tail -> new tail
    head->prev = newNode;       //head <- new tail

    return head;                //head unchanged
}


/* INSERT AT POSITION */

struct node* insertMiddle(struct node* head, int data, int pos){
    struct node* newNode = createNode(data);

    if(head == NULL){
        newNode->next = newNode;
        newNode->prev = newNode;
        return newNode;
    }

    if(pos == 1){
        struct node* tail = head->prev;

        newNode->next = head;
        newNode->prev = tail;

        tail->next = newNode;
        head->prev = newNode;

        return newNode;
    }

    struct node* ptr = head;

    while(pos != 2){

        if(ptr->next == head){
            printf("Position exceeds allowed range!\n");
            free(newNode);
            return head;
        }

        ptr = ptr->next;
        pos--;
    }

    newNode->next = ptr->next;       //new -> next
    newNode->prev = ptr;             //prev <- new

    ptr->next->prev = newNode;       //next <- new
    ptr->next = newNode;             //prev -> new

    return head;
}


/* DELETE START */

struct node* deleteStart(struct node* head){

    if(head == NULL){
        printf("LL is empty\n");
        return head;
    }

    if(head->next == head){          //only one node
        free(head);
        return NULL;
    }

    struct node* tail = head->prev;
    struct node* temp = head;

    head = head->next;               //next node becomes head

    tail->next = head;               //tail -> new head
    head->prev = tail;               //new head <- tail

    free(temp);

    return head;
}


/* DELETE END */

struct node* deleteEnd(struct node* head){

    if(head == NULL){
        printf("LL is empty\n");
        return head;
    }

    if(head->next == head){
        free(head);
        return NULL;
    }

    struct node* tail = head->prev;
    struct node* newTail = tail->prev;

    newTail->next = head;            //new tail -> head
    head->prev = newTail;            //head <- new tail

    free(tail);

    return head;
}


/* DELETE AT POSITION */

struct node* deleteMiddle(struct node* head, int pos){

    if(head == NULL){
        printf("LL is empty\n");
        return head;
    }

    if(head->next == head && pos == 1){   //only one node
        free(head);
        return NULL;
    }

    if(pos == 1){
        struct node* tail = head->prev;
        struct node* temp = head;

        head = head->next;

        tail->next = head;
        head->prev = tail;

        free(temp);

        return head;
    }

    struct node* ptr = head;

    while(pos != 2){

        if(ptr->next == head){
            printf("pos outside allowed range!\n");
            return head;
        }

        ptr = ptr->next;
        pos--;
    }

    if(ptr->next == head){
        printf("pos outside allowed range!\n");
        return head;
    }

    struct node* temp = ptr->next;

    ptr->next = temp->next;          //previous -> next
    temp->next->prev = ptr;          //previous <- next

    free(temp);

    return head;
}


/* SEARCH */

int searchElement(struct node* head, int target){

    if(head == NULL){
        printf("LL is empty!\n");
        return -1;
    }

    struct node* ptr = head;
    int pos = 1;

    do{
        if(ptr->data == target){
            return pos;
        }

        ptr = ptr->next;
        pos++;

    }while(ptr != head);

    return -1;
}


/* REVERSE */

struct node* reverseList(struct node* head){

    if(head == NULL){
        printf("LL is empty\n");
        return head;
    }

    if(head->next == head){
        return head;
    }

    struct node* oldTail = head->prev;
    struct node* ptr = head;
    struct node* temp;

    do{
        temp = ptr->next;

        ptr->next = ptr->prev;       //swap next
        ptr->prev = temp;            //swap prev

        ptr = temp;

    }while(ptr != head);

    return oldTail;                  //old tail becomes new head
}


/* DISPLAY */

void displayList(struct node* head){

    if(head == NULL){
        printf("LL is empty\n");
        return;
    }

    struct node* ptr = head;

    do{
        printf("%d<->", ptr->data);
        ptr = ptr->next;

    }while(ptr != head);

    printf("(HEAD)\n");
}


/* DISPLAY FORWARD AND REVERSE */

void displayBoth(struct node* head){

    if(head == NULL){
        printf("LL is empty\n");
        return;
    }

    struct node* ptr = head;

    printf("Forward: ");

    do{
        printf("%d<->", ptr->data);
        ptr = ptr->next;

    }while(ptr != head);

    printf("(HEAD)\n");


    ptr = head->prev;                 //tail

    printf("Reverse: ");

    struct node* tail = ptr;

    do{
        printf("%d<->", ptr->data);
        ptr = ptr->prev;

    }while(ptr != tail);

    printf("(TAIL)\n");
}


/* CONCATENATE TWO DCLLs */

struct node* concatLists(struct node* head1, struct node* head2){

    if(head1 == NULL){
        return head2;
    }

    if(head2 == NULL){
        return head1;
    }

    struct node* tail1 = head1->prev;
    struct node* tail2 = head2->prev;

    tail1->next = head2;             //tail1 -> head2
    head2->prev = tail1;             //tail1 <- head2

    tail2->next = head1;             //tail2 -> head1
    head1->prev = tail2;             //tail2 <- head1

    return head1;
}


/* COUNT NODES */

int countNodes(struct node* head){

    if(head == NULL){
        return 0;
    }

    int c = 0;
    struct node* ptr = head;

    do{
        c++;
        ptr = ptr->next;

    }while(ptr != head);

    return c;
}


/* FREE ALL NODES */

struct node* freeNodes(struct node* head){

    if(head == NULL){
        return NULL;
    }

    struct node* ptr = head->next;
    struct node* temp;

    while(ptr != head){
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }

    free(head);

    return NULL;
}


/* MAIN */

int main(){

    printf("\nMENU:\n");
    printf("1. Initialize DCLL\n");
    printf("2. Insert Start\n");
    printf("3. Insert End\n");
    printf("4. Insert Middle\n");
    printf("5. Delete Start\n");
    printf("6. Delete End\n");
    printf("7. Delete Middle\n");
    printf("8. Search Element\n");
    printf("9. Reverse List\n");
    printf("10. Display List\n");
    printf("11. Display Forward and Reverse\n");
    printf("12. Concatenate Lists\n");
    printf("13. Count Nodes\n");
    printf("14. Free List\n");
    printf("15. Exit\n");

    struct node* head = NULL;

    int choice;
    int data;
    int pos;

    while(1){

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice){

            case 1:
                printf("Enter data for first node: ");
                scanf("%d", &data);

                head = createNode(data);
                head->next = head;
                head->prev = head;
                break;

            case 2:
                printf("Enter data: ");
                scanf("%d", &data);

                head = insertStart(head, data);
                break;

            case 3:
                printf("Enter data: ");
                scanf("%d", &data);

                head = insertEnd(head, data);
                break;

            case 4:
                printf("Enter position: ");
                scanf("%d", &pos);

                printf("Enter data: ");
                scanf("%d", &data);

                head = insertMiddle(head, data, pos);
                break;

            case 5:
                head = deleteStart(head);
                break;

            case 6:
                head = deleteEnd(head);
                break;

            case 7:
                printf("Enter position: ");
                scanf("%d", &pos);

                head = deleteMiddle(head, pos);
                break;

            case 8:{
                printf("Enter element to search: ");
                scanf("%d", &data);

                int index = searchElement(head, data);

                if(index == -1){
                    printf("Element not found\n");
                }
                else{
                    printf("Element found at position %d\n", index);
                }

                break;
            }

            case 9:
                head = reverseList(head);
                printf("List reversed\n");
                break;

            case 10:
                printf("DCLL: ");
                displayList(head);
                break;

            case 11:
                displayBoth(head);
                break;

            case 12:{
                struct node* head2 = NULL;
                int n;

                printf("Enter number of nodes in second list: ");
                scanf("%d", &n);

                for(int i = 0; i < n; i++){
                    printf("Enter data: ");
                    scanf("%d", &data);

                    head2 = insertEnd(head2, data);
                }

                head = concatLists(head, head2);

                printf("Lists concatenated\n");
                break;
            }

            case 13:
                printf("Count: %d\n", countNodes(head));
                break;

            case 14:
                head = freeNodes(head);
                printf("List freed\n");
                break;

            case 15:
                head = freeNodes(head);
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}