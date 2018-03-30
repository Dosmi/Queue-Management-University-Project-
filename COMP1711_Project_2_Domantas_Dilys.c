/********************************************************************

I declare that the following program was written by me and that I have NOT copied any part of this code from any other source.

Name: Domantas Dilys

Email: sc17dd@leeds.ac.uk

Date: 13/11/2017

*********************************************************************/
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define WRS 60 // WRS stands for 'Waiting Room Size'
#define RN  10 // RN  stands for 'Room Number'

typedef enum {false, true} bool;

// ------------- Global Variables For Functions -------------

int Doctors_In_Rooms=0;    // Total doctors in surgery rooms counter
int RoomWithDoctors[11];  // The array which stores a value 1 if a doctor is in the surgery room and 0 if the room is empty. The size is 11 because room numbers range from 1 to 10
int RoomWithPatient[11]; // The array which stores rooms which contain patients (if a patient is in the room, it stores the patient's ID.
int AvailibleRoom[11];  // The array which contains 10 elements either 1 - indicating the room is ready, or 0 - room is not ready.
int nr;                // Surgery room number
int free_roomNR[9];   // Array of free surgery rooms
int Availible=0;     // true or false (1 or 0) value whether there exists a room which is available
int freeRooms=0;    // variable which stores the number of free rooms (rooms with availible doctors) initially there are no free rooms
char command;      // type of the entered command
int ID;           // patient ID
int password=1111;
int input_password; // user entered password

// ------------ QUEUE Variables --------------:
int first=-1;         // first index of the queue
int last=-1;         // last index of the queue, also set to -1.
int removeindex; // index of the patient, who wants to be removed
int Queue[WRS]; // Queue array of size WRS (Waiting Room Size)
int i; // loop iterative

void RoomAvailible () // function that checks if there is a free room and gives its number
{
    freeRooms=0;
    int i;
    for (i=1;i<=10;i++)
    {
        if(AvailibleRoom[i]==1)
        {
            freeRooms++;
            free_roomNR[freeRooms]=i;
        }
    }
    if (freeRooms>0) // if there is at least one room availible,
        Availible=1; // Availible is true (1)
    else if (freeRooms==0)
        Availible=0;

}
bool IsEmpty () // function to return true if the queue is empty
{
    if((first==-1) && (last==-1)) // if the queue is empty
    {
        return true;
    }
    else return false;
}

bool IsFull () // function to returns true if the queue is full
{
    return (first==last+1)||((first==0)&&(last==WRS-1));
}

int position (int n) // function to return the position of n in the queue, or -1 if n is not in the queue
{
    int i, pos=0;
    if (IsEmpty()==true)
    {
        return 1;
    }
    else if ((((IsEmpty()==false)&&(IsFull()==false))&&((last<WRS-1)&&(last>=first)))) // when the queue is neither empty nor full and first index is less than last index.
    {
        for(i=first; i<=last;i++)
        {
            if (Queue[i]==n)
            {
                pos=i+1-first;
                return pos;
            }
        }
    }
    else if (((IsEmpty()==false)&&(IsFull()==false))&&(last==WRS-1)&&(first!=0))
    {
        for(i=first; i<WRS;i++)
        {
            if (Queue[i]==n)
            {
                pos=i+1-first;
                return pos;
            }
        }

    }
    else if ((IsEmpty()==false)&&(IsFull()==false)&&(last<first))
    {
        for(i=first; i<WRS;i++) // separating the queue into two different testing scenarios: when the patient is in the part where queue has not yet rotated
        {
            if (Queue[i]==n)
            {
                pos=i-(first-1);
                return pos;
            }
        }

        for(i=0; i<=last;i++) // patient in the wrapped around queue part
        {
            if (Queue[i]==n)
            {
                pos=i+1+first;
                return pos;
            }
        }
    }
    else if (IsFull()&&(last<first))
    {
        for(i=first; i<WRS;i++)
        {
            if (Queue[i]==n)
            {
                pos=i-(first-1);
                return pos;
            }
        }

        for(i=0; i<=last;i++)
        {
            if (Queue[i]==n)
            {
                pos=i+1+first;
                return pos;
            }
        }
    }

    else if (IsFull()&&(last>first))
    {
        for(i=first; i<WRS;i++)
        {
            if (Queue[i]==n)
            {
                pos=i+1;
                return pos;
            }
        }
    }
}

void print () // function to print the entire queue
{
    if (IsEmpty()==true)
    {
        printf("The queue is empty.\n");
    }
    else if ((((IsEmpty()==false)&&(IsFull()==false))&&((last<WRS-1)&&(last>=first))))
    {
        for(i=first; i<=last;i++)
        {
            printf("%i ", Queue[i]);
        }
        printf("\n");
    }
    else if (((IsEmpty()==false)&&(IsFull()==false))&&(last==WRS-1)&&(first!=0))
    {
        for(i=first; i<WRS;i++)
        {
            printf("%i ", Queue[i]);
        }

        printf("\n");
    }
    else if ((IsEmpty()==false)&&(IsFull()==false)&&(last<first))
    {
        for(i=first; i<WRS;i++)
        {
            printf("%i ", Queue[i]);
        }

        for(i=0; i<=last;i++)
        {
            printf("%i ", Queue[i]);
        }
        printf("\n");
    }
    else if (IsFull()&&(last<first))
    {
        for(i=first; i<WRS;i++)
        {
            printf("%i ", Queue[i]);
        }

        for(i=0; i<=last;i++)
        {
            printf("%i ", Queue[i]);
        }
        printf("\n");
    }

    else if (IsFull()&&(last>first))
    {
        for(i=first; i<WRS;i++)
        {
            printf("%i ", Queue[i]);
        }

        printf("\n");
    }
}

void clear () // function to clear (initialize) the queue
{
    first = -1;
    last  = -1;
}

void remove_from_queue (int nr) // function to remove n from the queue
{
        if ((((IsEmpty()==false)&&(IsFull()==false))&&((last<WRS-1)&&(last>=first)))) // when the queue is neither empty nor full and first index is less than last index.
            {
                for(i=first; i<=last;i++)
                    {
                        if (Queue[i]==nr)
                        removeindex=i;
                    }
                for(i=removeindex; i<=last;i++)
                    {
                        Queue[i]=Queue[i+1];
                    }
                last--;
            }
        else if (((IsEmpty()==false)&&(IsFull()==false))&&(last==WRS-1)&&(first!=0)) //2
            {
                for(i=first; i<=last;i++)
                    {
                        if (Queue[i]==nr)
                        removeindex=i;
                    }
                for(i=removeindex; i<WRS-1;i++)
                    {
                        Queue[i]=Queue[i+1];
                    }

                Queue[0]=Queue[1];
                last--;

            }
        else if ((IsEmpty()==false)&&(IsFull()==false)&&(last<first))
            {
                for(i=first; i<=WRS-1;i++)
                    {
                        if (Queue[i]==nr)
                        removeindex=i;
                    }
                for(i=removeindex; i<WRS-1;i++)
                    {
                        Queue[i]=Queue[i+1];
                    }

                if (last==0)
                {
                    Queue[WRS-1]=Queue[0];
                    last = WRS-1;
                }
                else
                {   Queue[WRS-1]=Queue[0];
                    for(i=0; i<=last;i++)
                        {
                            Queue[i] =Queue[i+1];
                        }
                    last--;
                }
            }
        else if (IsFull()&&(last<first))
            {
                if (removeindex==0)
                {
                    Queue[removeindex]=Queue[removeindex+1];
                    for(i=0; i<=first-1;i++)
                        {
                            Queue[i]=Queue[i+1];
                        }
                        last--;
                }
                if (removeindex==0)
                {
                    Queue[i]=Queue[i+1];
                }
                for(i=first; i<=WRS-1;i++)
                    {
                        if (Queue[i]==nr)
                        removeindex=i;
                    }
                for(i=0; i<=last;i++)
                    {
                        if (Queue[i]==nr)
                        removeindex=i;
                    }
                for(i=removeindex; i<WRS-1;i++)
                    {
                        Queue[i]=Queue[i+1];
                    }

                if (last==0)
                {
                    Queue[WRS-1]=Queue[0];
                    last = WRS-1;
                }
                else
                {   Queue[WRS-1]=Queue[0];
                    for(i=0; i<=last;i++)
                        {
                            Queue[i] =Queue[i+1];
                        }
                    last--;
                }
            }
        else if (IsFull()&&(last>first))
            {
                for(i=removeindex; i<WRS;i++)
                    {
                        Queue[i]=Queue[i+1];
                    }
                last--;
            }
}

void enqueue () // function to append n to the queue
{
    if (IsEmpty()==true)
        {
            first = 0;
            last  = 0;
            Queue[last]=ID;
            printf("All doctors are busy right now, please relax in the waiting area. You are number 1 in the queue.\n");
        }

    else if ((((IsEmpty()==false)&&(IsFull()==false))&&((last<WRS-1)&&(last>=first))))
        {
            last++;
            Queue[last]=ID;
            printf("All doctors are busy right now, please relax in the waiting area. You are number %i in the queue.\n",last+1-first);
        }

    else if (((IsEmpty()==false)&&(IsFull()==false))&&(last==WRS-1)&&(first!=0))
        {
            last=0;
            Queue[last]=ID;
            printf("All doctors are busy right now, please relax in the waiting area. You are number %i in the queue.\n", WRS-first+1);
        }

    else if ((IsEmpty()==false)&&(IsFull()==false)&&(last<first))
        {
            last++;
            Queue[last]=ID;
            printf("All doctors are busy right now, please relax in the waiting area. You are number %i in the queue.\n", WRS-first+last+1);
        }

    else if (IsFull())
        {
            printf("Sorry, but the queue is full.\n");
        }
}
int dequeue () // function to remove the first item in the queue, and return its value
{
    int removedID;

    if ((IsEmpty()==false)&&(first==last))
        {
            removedID=Queue[first];
            first=-1;
            last =-1;
        }
    if ((IsEmpty()==false)&&(first==WRS-1))
        {
            removedID=Queue[first];
            first=0;
            last--;
        }
    if ((IsEmpty()==false)&&(first!=WRS-1))
        {
            removedID=Queue[first];
            first++;
        }
    if (IsFull()==true)
        {
            first++;
        }

    return removedID;
}

int elementfirst() // function to get the first item without removing it
{
    return Queue[first];
}

int elementlast () // function to get the last item without removing it
{
    return Queue[last];
}


int InRoom(int n) // function which checks whether the patient is already in a surgery room
{
    for (i=0;i<RN;i++) // checks if patient is in the room
    {
        if (RoomWithPatient[i]==n)
        {
            return 1;
        }
    }
    return 0;
}

int InQueue(int n) // function which checks whether the patient is already in a queue
{
    if (IsEmpty()==true)
    {
        return 0;
    }

    for(i=0; i<WRS;i++)
    {
        if (Queue[i]==n) return 1;
    }

    return 0;
}

//---------------------------------------------------- MAIN PROGRAM -----------------------------------------------------

int main()
{
// ------------- Main Function Variables --------------
int i; // loop iterative
int exists = 0; // variable which stores with a value of either 0 if a patient is not already in the queue or in surgery room or 1 if a patient exists
for(i=0;i<9;i++)   // short loop to start the day - no room is ready until a doctor for a room is ready
{
    AvailibleRoom[i]=0;
}

for(i=1;i<=10;i++) // short loop to start the day - no patient is in the surgery room
{
    RoomWithPatient[i]=0;
}

for(i=0;i<WRS;i++)
{
  Queue[i]=0;
}

clear();           // clearing the queue

printf("_______________________________\n");
printf("    WELCOME TO THE SURGERY     \n");
printf("_______________________________\n");
printf("  press 'h' for help command   \n");

while (1<3) // infinite loop, terminated in 'x' command
{
    printf(">>> ");
    scanf(" %c",&command);

    switch (command)
    {
    case 'r' : // command used when a doctor is ready
        scanf("%i", &nr);
        printf("Enter the password: ");
        scanf("%i", &input_password);
        printf("\n");
        if (RoomWithPatient[nr]!=0) printf("The room is already full.\n"); // checks if the room is occupied
        else
        {
        if (input_password==password)
        {
            if ((nr > 0)&&(nr <= RN))
            {
                printf("Free room number: %i\n", nr);
                AvailibleRoom[nr]=1;
                Doctors_In_Rooms++;
                RoomWithDoctors[Doctors_In_Rooms]=nr;
                if ((IsEmpty()==false)&&(first==last))
                {
                    printf("Patient Nr. %i, please proceed to Room Nr. %i\n", Queue[first], nr);
                    RoomWithPatient[nr]=Queue[first];

                    dequeue();

                    AvailibleRoom[nr]=0;
                }
                if ((IsEmpty()==false)&&(first==WRS-1))
                {
                    printf("Patient Nr. %i, please proceed to Room Nr. %i\n", Queue[first], nr);
                    RoomWithPatient[nr]=Queue[first];
                    dequeue();
                    printf("%i ", last);
                    AvailibleRoom[nr]=0;
                }
                if ((IsEmpty()==false)&&(first!=WRS-1))
                {
                    printf("Patient Nr. %i, please proceed to Room Nr. %i\n", Queue[first], nr);
                    RoomWithPatient[nr]=Queue[first];
                    dequeue();
                    AvailibleRoom[nr]=0;
                }
                if (IsFull()==true)
                {
                    printf("Patient Nr. %i, please proceed to Room Nr. %i\n", Queue[first], nr);
                    RoomWithPatient[nr]=Queue[first];
                    dequeue();
                }
            }
            else printf("Invalid room number. Try again.\n");
        }
        else if (input_password!=password)
            printf("Invalid password\n");
        }



        break;

    case 'i' : // command for a patient to check in
        scanf("%i", &ID);
        int exists;

        if ((ID > 99) && (ID<1000))
        {
            if ((InQueue(ID)==1)||(InRoom(ID)==1))
            {
                printf("The patient of ID %i is already in the queue or is in the surgery room. Try again.\n", ID);
                break;
            }
            else
            {
                RoomAvailible();
                printf("Your ID is %i\n", ID);
                if (Availible==1) // If a room is awailible, we can tell the patient to proceed to a free room
                {
                    printf("\nPlease proceed to Room %i\n ", free_roomNR[1]);
                    AvailibleRoom[free_roomNR[1]]=0;                            // The room is no longer empty
                }

                else if (Availible==0)  // If there are no availible rooms, we must add a patient to the queue
                {
                    enqueue();
                }
            }
        }
        else printf("ID has to contain 3 digits. Try again\n");
        break;

    case 'a' : // command used when doctor leaves the room
        scanf("%i", &nr);
        printf("Enter the password: ");
        scanf("%i", &input_password);
        printf("\n");
        if (input_password==password)
        {
            if (RoomWithPatient[nr]==0)
            {
                RoomWithDoctors[nr]=0;
                Doctors_In_Rooms--;
            }
            else printf("The patient has not been discharged yet!\n");
        }
        else printf("Invalid password\n");
        break;

    case 'w' : // command which displays the queue
        printf("Enter the password: ");
        scanf("%i", &input_password);
        printf("\n");
        if (input_password==password)
        {
        printf("The following patients are still waiting to be seen by a doctor: ");
        print();
        }
        else printf("Invalid password.\n");
        break;

    case 'd' : // command which displays all available doctors
        RoomAvailible();
        if (Doctors_In_Rooms!=0)
        {
            printf("There are currently %i doctors in the surgery. They are in rooms: ", Doctors_In_Rooms);
            for (i=0;i<Doctors_In_Rooms;i++)
            {
                if(RoomWithDoctors[i+1]!=0)
                printf("%i, ",RoomWithDoctors[i+1]);
            }
        }
        else printf("There are currently no doctors in surgery rooms.");

        printf("\n");
        break;

    case 'v' : // command which displays numbers of rooms in which doctors are in and do not have patients.
        if (freeRooms!=0)
        {
            printf("%i available surgery rooms: ", freeRooms);
            for (i=1;i<=RN;i++)
            {
                if((RoomWithPatient[i]==0)&&(RoomWithDoctors[i]!=0))
                printf("%i, ",i);
            }
            printf("\n");
        }
        else printf("There are no rooms surgeons are in \n");

        break;

    case 'o' : // check out command
        scanf("%i", &nr);
        printf("Enter the password: ");
        scanf("%i", &input_password);
        printf("\n");
        if (input_password==password)
        {
            for(i=1;i<=10;i++)
            {
                if(RoomWithPatient[i]==nr)
                {
                    RoomWithPatient[i]=0;
                    freeRooms++;
                }
            }
        }
        else printf("Invalid password.\n");
        break;
    case 'l' : // additional function which outputs the patients in rooms.
        for(i=1;i<=10;i++)
        {
            printf("Room %i: ID %i \n",i,RoomWithPatient[i]);
        }
        printf("\n");
        break;

    case 'p' : // position command
        scanf("%i", &nr);
        if (position(nr)!=0)
        printf("You are number %i in the queue.\n", position(nr));
        else  printf("You are not in the queue.\n");
        break;
    case 'q' : // quit command
        scanf("%i", &nr);
        remove_from_queue(nr);
        printf("You have been removed from the queue. Thank you for your visit.\n");
        break;
    case 'h' : // help command
        printf("Patient Commands:\n");
        printf("The i command (patient check in). This command must be used by patients to check in on arrival to the surgery. The i command takes one integer argument that represents the patients idnumber.\n");
        printf("The p command (patient queue position). This command can be used at any time if a patient wants to know his or her position in the waiting queue. This command takes one integer argument that represents the id number of a patient.\n");
        printf("The q command (patient quit). This command can be used if a patient decides to leave the surgery after checking in, and before seeing a doctor. This command takes one integer argument that represents the id number of a patient.\n");
        printf("The d command (available doctors). This command displays the number of doctors currently available at the surgery, and a list of all examination rooms that are currently staffed\n");
        printf("The h command (help). This command displays a list of all available commands and a brief description of each one of them.\n\n");
        printf("Administrator Commands:\n");
        printf("The o command (patient check out) The o command takes one integer argument that represents the patients id number\n");
        printf("The r command (doctor ready). This command must be used by a doctor when they arrive at their room and they are ready to see patients. The command takes one argument representing the number of the examination room of this doctor\n");
        printf("The a command (doctor away). The command takes one argument representing the number of the examination room of this doctor.\n");
        printf("The w command (who is waiting). This command displays the entire waiting queue.\n");
        printf("The x (exit program) command. This command is used to terminate the program.\n\n");
    case 'x' : //command to exit the program
        printf("Enter the password: ");
        scanf("%i", &input_password);
        printf("\n");
        if (input_password==password)
        {
            exit(0);
        }
        else if (input_password!=password)
        {
            printf("Invalid password.\n");
            break;
        }

    default :
        printf("Invalid input.\n");
    }
}

return 0;
}
