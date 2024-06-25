#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHTS 100

struct Flight {
    int number;
    char type[50];
    char from[50];
    char to[50];
    char date[50];
    char time[50];
};

int readFlights(struct Flight flights[]);
void writeFlights(struct Flight flights[], int count);
int checknumberofflight(struct Flight flights[MAX_FLIGHTS],int number,int count);
void printFlight(struct Flight flight);
void addFlight(struct Flight flights[], int *count);
void updateFlight(struct Flight flights[], int count);
void searchByOrigin(struct Flight flights[], int count);
void searchByDestination(struct Flight flights[], int count);
void listFlights(struct Flight flights[], int count);


int main() {
    struct Flight flights[MAX_FLIGHTS];
    int count = 0;
    int choice;

    count = readFlights(flights);

    do {
        printf("\nMENU:\n");
        printf("1. Add a new flight\n");
        printf("2. Update a flight\n");
        printf("3. Search flights by origin\n");
        printf("4. Search flights by destination\n");
        printf("5. List all flights\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character

        switch (choice) {
            case 1:
                addFlight(flights,&count);
                break;
            case 2:
                updateFlight(flights, count);
                break;
            case 3:
                searchByOrigin( flights, count);
                
                break;
            case 4:
                searchByDestination( flights, count);
                break;
            case 5:
               listFlights( flights,  count);
                break;
            case 6:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

int readFlights(struct Flight flights[]) {
    FILE *file = fopen("flights.txt", "r");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return 0;
    }

    int count = 0;
    while (fscanf(file, "%d  %s  %s  %s  %s  %s",
                  &flights[count].number,
                  flights[count].type,
                  flights[count].from,
                  flights[count].to,
                  flights[count].date,
                  flights[count].time) != EOF) {
        count++;
    }

    fclose(file);
    return count;
}

void writeFlights(struct Flight flights[], int count) {
    FILE *file = fopen("flights.txt", "r+");
    if (file == NULL) {
        printf("Unable to open file.\n");
        return;
    }
    int i;
    for ( i = 0; i < count; i++) {
        fprintf(file, "%d   %s   %s   %s   %s   %s  \n",
                flights[i].number,
                flights[i].type,
                flights[i].from,
                flights[i].to,
                flights[i].date,
                flights[i].time);
    }

    fclose(file);
}
int checknumberofflight(struct Flight flights[MAX_FLIGHTS],int number,int count)
{
	int i;
    for( i=0;i<count;i++)
    {
        if(flights[i].number==number)
            return i;
    }
    return -1;
}

void printFlight(struct Flight flight) {
	
    printf("\r %d", flight.number); 
    printf(" %s\n", flight.type);
    printf(" %s\n", flight.from);
    printf(" %s\n", flight.to);
    printf(" %s\n", flight.date);
    printf(" %s\t", flight.time);
    printf("\n");
}

void addFlight(struct Flight flights[], int *count) {
	FILE*file;
    if (*count >= MAX_FLIGHTS) {
        printf("Maximum number of flights reached.\n");
        return;
    }

    struct Flight newFlight;

    printf("Enter the flight number: ");
    scanf("%d", &newFlight.number);
    getchar();

    printf("Enter flight type 1 for Domestic 0 for international flight: ");
    scanf("%s", newFlight.type);
   

    printf("Enter the origin city:");
    scanf("%s", newFlight.from);
    
    printf("Enter the destination city: ");
    scanf("%s", newFlight.to);
   

    printf("Enter the date: ");
    scanf("%s", newFlight.date);
 

    printf("Enter the time: ");
    scanf("%s", newFlight.time);
    file =fopen("flights.txt","a");
  	  	         if (file == NULL) {
                printf("Error: could not open file .");
                
				   }
                  fprintf(file,"\r%d,%s,%s,%s,%s,%s\n",newFlight.number,newFlight.type,newFlight.from,newFlight.to,newFlight.date,newFlight.time);
  	  	        fclose(file);
    flights[*count] = newFlight;
    (*count)++;

    printf("Flight inserted successfully.\n");
}

void updateFlight(struct Flight flights[], int count) {
    printf("Enter flight number to update: ");
            int number;
            int choice;
            scanf("%d",&number);
            int i=checknumberofflight(flights,number,count);
            if(i!=-1)
            {
                printf("Flight Found. Which field wold you like to update ?\n");
                printf(" 1.Type\n"
                        "2. From\n"
                        "3. To\n"
                        "4. Date\n"
                        "5. Time \n");
                printf("Enter you choice (1-5):");
                FILE* file;
                scanf("%d",&choice);
                if(choice==1)
                {
                    char type;
                    printf("Enter new type :");
                    scanf("%c",type);
                    strcpy(flights[i].type,type);
                    fgets(flights[i].type, sizeof(flights[i].type), stdin);
                    flights[i].type[strcspn(flights[i].type, "\n")] = '\0'; 
                    fprintf(file,"%c",type);
                    printf("Flight updated successfully\n");
                }
                else if(choice==2)
                {
                    char from[30];
                    printf("Enter new from :");
                    scanf("%s",from);
                    strcpy(flights[i].from,from);
                    fgets(flights[i].from, sizeof(flights[i].from), stdin);
                    flights[i].from[strcspn(flights[i].from, "\n")] = '\0'; 
                    fprintf(file,"%s",from);
                    printf("Flight updated successfully.\n");
                }
                else if(choice==3)
                {
                    char to[30];
                    printf("Enter new to :");
                    scanf("%s",to);
                    strcpy(flights[i].to,to);
                    fgets(flights[i].to, sizeof(flights[i].to), stdin);
                    flights[i].to[strcspn(flights[i].to, "\n")] = '\0';
                    fprintf(file,"%s",to);
                    printf("Flight updated successfully.\n");
                }
                else if(choice==4)
                {
                    char date[30];
                    printf("Enter new date :");
                    scanf("%s",date);
                    strcpy(flights[i].date,date );
                    fgets(flights[i].date, sizeof(flights[i].date), stdin);
                    flights[i].date[strcspn(flights[i].date, "\n")] = '\0';
					fprintf(file,"%s",date); 
                    printf("Flight updated successfully.\n");

                }
                else if(choice==5)
                {
                    char time[30];
                    printf("Enter new time :");
                    scanf("%s",time);
                    strcpy(flights[i].time,time );
                    fgets(flights[i].time, sizeof(flights[i].time), stdin);
                    flights[i].time[strcspn(flights[i].time, "\n")] = '\0';
					fprintf(file,"%s",time); 
                    printf("Flight updated successfully.\n");
                  
                }
        
                else {
				
                    printf("Invalid input.\n");
                }
    
  	  	        
}
    
} 

void searchByOrigin(struct Flight flights[], int count) {
            char origin[50];
			printf("Enter origin :");
            scanf("%s",origin);
            int i;
            for ( i = 0; i < count; i++)
            {
                if(strcmp(origin,flights[i].from)==0)
                {
                    printf("%d \t %s \t %s \t %s \t %s \t %s \n",flights[i].number,flights[i].type,flights[i].from,flights[i].to,flights[i].date,flights[i].time);
                }
				}
            
        if(strcmp(origin,flights[i].from)!=0) {
        	printf("No flights found from %s. \n",origin);
		}
        
    }


void searchByDestination(struct Flight flights[], int count) {
    char destination[50];
            printf("Enter destination :");
            scanf("%s",destination);
            int i;
            for ( i = 0; i < count; i++)
            {
                if(strcmp(destination,flights[i].to)==0)
                {
                    printf("%d \t %s \t %s \t %s \t %s \t %s \n",flights[i].number,flights[i].type,flights[i].from,flights[i].to,flights[i].date,flights[i].time);
                }
            }
         if(strcmp(destination,flights[i].from)!=0) {
        	printf("No flights found to %s.\n",destination);    
    
}
}

void listFlights(struct Flight flights[], int count) {
	printf("FNUM D-I  FROM  TO  DATE     TIME\n");
    if (count == 0) {
        printf("No flights available.\n");
    } else {
    	int i;
        for ( i = 0; i < count; i++) {
            printFlight(flights[i]);
        }
    }
}
