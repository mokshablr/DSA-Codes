#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    struct node * prev;
    int data;
    struct node * next;
}NODE;

//function to create new nodes.
NODE * createNode(int data){

    //allocating memory for the new node
    NODE * new = (NODE *)malloc(sizeof(NODE));

    //store value of data parameter into the new node.
    new -> data = data;

    //links to NULL since this node is independent of other nodes during creation.
    new -> next = NULL;
    new -> prev = NULL;    
    //return the address to the newly created link.
    return new;
}

//function to display the linked list.
void display(NODE* head){

    //Check if the list is empty.
    if(head==NULL){
        printf("Empty List!!\n");

        //returns no value since return type is void. Return ends this function and goes back to function call.
        return;
    }

    printf("{");
    while(head!=NULL){

        //print value of each node
        printf("%d <--> ",head->data);

        //traversing through the node.
        head=head->next;
    }
    printf("NULL \b}\n");
    return;
}

//function to insert nodes at the start of the linked list.
NODE * insertFront(NODE * start, int data){

    //calling function createNode(<data>) to create a node with the data to be inserted into the front of the linked list.
    NODE * new = createNode(data);

    //since the new node is the first node, the link of the new node should be to the rest of the existing linked list(aka. the head)
    new -> next = start;

    if(start != NULL){
        start -> prev = new;
    }

    //return the new head which is the new node.
    return new;
}
//Example:
//main:
// head->next->next
// head = new
// new(new head) ->head(old head)-> next->next
//head = insertFront(head, <data>);



//function to insert nodes at the end of the linked list.
//return type is void since we are changing the *actual pointers* directly and so there is nothing to return.
void insertLast(NODE * start, int data){

    //calling function createNode(<data>) to create a node with the data to be inserted into the last of the linked list.
    NODE * new = createNode(data);

    //temp variable to iterate through the linked list. We can just use the start variable to iterate but this is easier to understand!
    // NODE * temp = start;
    while(start->next !=NULL){
        start = start->next;
    }

    //adding new node to the end of the linked list. new node link is NULL.
    start->next = new;
    new->prev = start;
}
//Example:
//head -> next1 -> next2 -> NULL
//    insertLast(head, 500);
//      {
//         NOTE:  Notice that the list elements "next1" and "next2" are the same within and outside the function insertLast.
//                This is because we are using pointers to the "actual nodes".
//                This shows that we are altering the actual values of the linked list and not a copy (like start being a copy for head)        
//                So any changes to the nodes within the function affects it outside the function as well.
//                Therefore, we do not need to return the head again within the function. The nodes change themselves gloablly.
//         start -> next1 -> next2 -> NULL
//         next1 -> start -> next2 -> NULL
//         next1 -> next2 -> start -> NULL
//         next1 -> next2 -> start -> 500 -> NULL
//      }
//head -> next1 -> next2 -> 500 -> NULL


//function to insert nodes at a particular index of the linked list.
void insertIndex(NODE * start, int data, int index){

    //calling function createNode(<data>) to create a node with the data to be inserted into the last of the linked list.
    NODE * new = createNode(data);

    //temp variable to iterate through the linked list. We can just use the start variable to iterate but this is easier to understand!
    //index = 1, temp holds content of first node.
    NODE * temp = start;

    //Since we are the first node, set j=1. 
    //Traverse the list until we are one node before the required node to insert at.
    for(int j = 1; j < index-1; j++){ //can also use j=2 and j<(index)
        
        //check if the index is within the scope of the linked list.
        if(temp -> next != NULL){
            temp = temp->next;
        }
        else{
            printf("Error: Index exceeds that of linked list.");
            return;
        }
    }

    //new link should point to the next link's node(the node which is at the postion we want to insert to).
    //This would shift the node at the position, one node to the right.
    //temp next should point to the new node
    new -> next = temp ->next;
    temp ->next -> prev = new;
    temp -> next = new;
    new -> prev = temp;
}


//Funtion to delete the first node in the list.
NODE * deleteFront(NODE * start){

    //Check if list is empty
    if(start != NULL){
        //temp variable to store the head
        NODE * temp = start;

        //checking if there is more than only one element in the linked list
        //If only 1 element, temp->link would return NULL and condition would be false
        if(temp -> next != NULL){

            //temp now points to the 2nd node on the linked list.
            temp = temp -> next;
        }

        //Free the head(which is what we want this function to do).
        free(start);
        temp->prev = NULL;

        //Temp is now your new head since the original head has been freed/deleted.
        return temp;
    }
    else{
        printf("Empty list!");

        //Since it is empty, head does not change.
        return start;
    }

}

//Function to delete the last node in the linked list.
void deleteLast(NODE * start){

    //Check if list is empty
    if(start == NULL){
        printf("Empty List!\n");
    }
    else if(start-> next != NULL){
        //We require 2 temp vars. One to be the current and the other to be the next nodes of the linked list.
        NODE * temp1 = start;
        NODE * temp2 = start->next;


        //Traverse the linked list until the temp2's link is NULL(till temp2 is the last node.)
        while(temp2 -> next != NULL){
            temp1 = temp1 -> next;
            temp2 = temp2 -> next;
        }

        //Now that temp2 is the last node, free temp2.
        free(temp2);

        //Set the link from temp1(the node before temp2) to NULL. We use NULL since this is the end of the linked list and there are no other nodes after this node.
        temp1->next = NULL;
    }
    else if(start -> next == NULL){
        printf("Only 1 node in list. Try DeleteFront.\n");
    }

}

void deleteIndex(NODE * start, int position){

    //Check is the list is empty.
    if(start != NULL){

        NODE * temp1 = start;
        NODE * temp2 = start->next;

        //If we have to delete the first element, we would have to return the new head. But this function has a void return type.
        //We could either change the return type of the function to (NODE *) or suggest using deleteFront function.
        if(position == 1){
            printf("Use deleteFront function instead!\n");
            return;
        }
        //Check if position is greater than 2. If position is 2, we won't get into either of these if conditions and go directly to line !
        else if(position > 2){

            //temp2 starts at 2nd position, so we use i=2. Traverse list till temp2 reaches the node we want to delete.
            for(int i=2; i < position; i++){

                //Checking if we reach the end of the linked list before reaching the required position to delete. 
                //This would mean that the linked list is smaller than the position specified.
                if(temp2 -> next != NULL){
                    temp1 = temp1 -> next;
                    temp2 = temp2 -> next;
                }
                else{
                    printf("Reached end of list before finding index. Index Out Of Bounds!\n");
                }
            }
        }

        //Default condition. If position=2 it would automatically come here without entering the blocks above.
        //We point the temp1 link to the link of the deleted node. This would skip the node to be deleted in the linked list.
        temp1 ->next = temp2->next;
        temp1->next->prev = temp1;

        //Free temp2 which is the node at the position we want to delete.
        free(temp2);

        //NOTE: Change the links before freeing in this exact order else the code will NOT WORK.
        //If we free before changing the link, temp2->link would be some garbage value since the memory location of temp2 had been freed.
    }
    else{
        printf("Empty list!\n");
    }


}




int main(){
    NODE *head = NULL;
    int run = 1;

    while(run){
        printf("\n\nEnter your choice:\n0. Exit\n\nINSERTION:\n1. Insert Front\n2. Insert Last\n3.Insert at a specified position\n\nDELETION:\n4. Delete Front\n5.Delete Last\n6. Delete at a specified position\n\n7.Display\n");

        int ch, ele, pos;
        scanf("%d", &ch);

        switch(ch){
            case 0:
                run = 0;
                break;

            case 1:
                
                printf("Enter the element to be inserted: ");
                scanf("%d", &ele);
                head = insertFront(head, ele);
                break;

            case 2:
                
                printf("Enter the element to be inserted: ");
                scanf("%d", &ele);
                insertLast(head, ele);
                break;

            case 3:
                printf("\nNOTE: When specifying position, assume first position to be 1 not 0!\n");

                printf("Enter the element to be inserted: ");
                scanf("%d", &ele);
                printf("Enter the position where to insert: ");
                scanf("%d", &pos);
                insertIndex(head, ele, pos);
                break;

            case 4:
                head = deleteFront(head);
                break;

            case 5:
                deleteLast(head);
                break;

            case 6:
                printf("\nNOTE: When specifying position, assume first position to be 1 not 0!\n");
                printf("Enter the position at which to delete: ");
                scanf("%d", &pos);
                deleteIndex(head, pos);
                break;

            case 7:
                printf("The current linked list:\n");
                display(head);
                break;

            default:
                printf("Invalid input!\n");
        }
    }
}
