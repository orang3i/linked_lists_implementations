#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node* next;
};

struct node* createNode(int data){
    struct node* newNode = (struct node*)malloc(sizeof(struct node));

    if(newNode == NULL){
        printf("Dynamic memory allocation failed!\n");
        exit(1);
    }

    newNode->data = data;
    newNode->next = NULL;

    return newNode;
}


/* INSERT AT START */

struct node* insertStart(struct node* head, int data){
    struct node* newNode = createNode(data);

    if(head == NULL){
        newNode->next = newNode;
        return newNode;
    }

    struct node* ptr = head;

    //find last node
    while(ptr->next != head){
        ptr = ptr->next;
    }

    newNode->next = head;    //new node points to old head
    ptr->next = newNode;     //last node points to new head

    return newNode;          //newNode becomes head
}


/* INSERT AT END */

struct node* insertEnd(struct node* head, int data){
    struct node* newNode = createNode(data);

    if(head == NULL){
        newNode->next = newNode;
        return newNode;
    }

    struct node* ptr = head;

    //find last node
    while(ptr->next != head){
        ptr = ptr->next;
    }

    ptr->next = newNode;     //old last -> new node
    newNode->next = head;    //new last -> head

    return head;             //head unchanged
}


/* INSERT AT POSITION */

struct node* insertMiddle(struct node* head, int data, int pos){
    struct node* newNode = createNode(data);

    if(head == NULL){
        newNode->next = newNode;
        return newNode;
    }

    if(pos == 1){
        struct node* ptr = head;

        while(ptr->next != head){
            ptr = ptr->next;
        }

        newNode->next = head;
        ptr->next = newNode;

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

    newNode->next = ptr->next;
    ptr->next = newNode;

    return head;
}


/* DELETE START */

struct node* deleteStart(struct node* head){

    if(head == NULL){
        printf("LL is empty\n");
        return head;
    }

    //only one node
    if(head->next == head){
        free(head);
        return NULL;
    }

    struct node* ptr = head;

    //find last node
    while(ptr->next != head){
        ptr = ptr->next;
    }

    struct node* temp = head;

    head = head->next;       //second node becomes head
    ptr->next = head;        //last node points to new head

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

    struct node* ptr = head;
    struct node* prev = NULL;

    while(ptr->next != head){
        prev = ptr;
        ptr = ptr->next;
    }

    //ptr = last node
    //prev = second last node

    prev->next = head;
    free(ptr);

    return head;
}


/* DELETE AT POSITION */

struct node* deleteMiddle(struct node* head, int pos){

    if(head == NULL){
        printf("LL is empty\n");
        return head;
    }

    if(head->next == head && pos == 1){ //only one node present
        free(head);
        return NULL;
    }

    if(pos == 1){
        struct node* ptr = head;

        while(ptr->next != head){       //find last node
            ptr = ptr->next;
        }

        struct node* temp = head;
        head = temp->next;              //next node becomes new head
        ptr->next = head;               //last node points to new head

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

    ptr->next = temp->next;

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

    struct node* prev = NULL;
    struct node* cur = head;
    struct node* nextNode;

    do{
        nextNode = cur->next;
        cur->next = prev;

        prev = cur;
        cur = nextNode;

    }while(cur != head);

    //old head must point to new head
    head->next = prev;

    //prev is old last node = new head
    return prev;
}

/* DISPLAY */

void displayList(struct node* head){

    if(head == NULL){
        printf("LL is empty\n");
        return;
    }

    struct node* ptr = head;

    do{
        printf("%d->", ptr->data);
        ptr = ptr->next;

    }while(ptr != head);

    printf("(HEAD)\n");
}


/* CONCATENATE TWO CLLs */

struct node* concatLists(struct node* head1, struct node* head2){

    if(head1 == NULL){
        return head2;
    }

    if(head2 == NULL){
        return head1;
    }

    struct node* tail1 = head1;
    struct node* tail2 = head2;

    while(tail1->next != head1){
        tail1 = tail1->next;
    }

    while(tail2->next != head2){
        tail2 = tail2->next;
    }

    tail1->next = head2;     //list1 tail -> list2 head
    tail2->next = head1;     //list2 tail -> list1 head

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

    //free every node except head
    while(ptr != head){
        temp = ptr;
        ptr = ptr->next;
        free(temp);
    }

    //free head
    free(head);

    return NULL;
}


/* MAIN */

int main(){

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
                printf("CLL: ");
                displayList(head);
                break;

            case 11:{
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

            case 12:
                printf("Count: %d\n", countNodes(head));
                break;

            case 13:
                head = freeNodes(head);
                printf("List freed\n");
                break;

            case 14:
                head = freeNodes(head);
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
}