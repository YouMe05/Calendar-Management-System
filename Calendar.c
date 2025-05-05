#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>

//
int IsValidUsername(const char* saveusername){
    // Function to check if the username contains restricted characters
    const char* restrictedChars = "\/:*?\"<>|";
    for (int i = 0; i < strlen(restrictedChars); i++){
        if (strchr(saveusername, restrictedChars[i]) != NULL)
        {
            return 0; // Invalid character found
        }
    }
    return 1; // Username is valid
}

//Login function
int login(char user[]){
    char pass[20],savepass[20],username[20],saveusername[20],passf[20],inputlog[50],filename[20],rfilename[20],ch;
    int acc,validInputlog,count=0;
    FILE *fp;

    //Options
    while(1){
        printf(" ===================================\n        Schedule Disentangle\n ===================================\n");
        printf("\n\t       ------------\n");
        printf("\t(\\__/) | Options  |\n");
        printf("\t( •_•) | 1.Login  |\n");
        printf("\t/ >  > | 2.Signup |\n");
        printf("\t       | 3.Exit   |\n");
        printf("\t       ------------\n\n");
        //input option + check
        do {
            fflush(stdin);
            printf("Select an option: ");
            fgets(inputlog, sizeof(inputlog), stdin);
            validInputlog = 0;

            // Use sscanf to attempt to convert the string to an integer
            if (sscanf(inputlog, "%d", &acc) == 1 && acc==1 || acc==2 || acc==3) {
                    validInputlog = 1; // Set flag to exit the loop
            }
            else {
                printf("!!!!!Invalid input. Please enter a valid integer.!!!!!\n");
            }

        } while (!validInputlog);
        system("cls");

        switch(acc){
        case 1: goto name;
                break;
        case 2:
            sign:
            printf(" ===================================\n        Schedule Disentangle\n ===================================\n\n\n");
            printf(" (\\__/) ==================== (\\__/)\n ( •_•)");
            printf("        SIGNUP        ");
            printf("(•_• )\n / >  > ==================== <  < \\\n\n\n");

            //check \\ / : * ? \" < > | in username
            do{
                char ch;
                int i = 0;
                printf("Enter username : ");
                // Read the username character by character
                while (1)
                {
                    ch = _getch();
                    // Enter key
                    if (ch == 13) {
                        saveusername[i] = '\0'; // Null-terminate the string
                        break;
                    }
                    // Backspace key
                    else if (ch == 8){
                        if (i > 0){
                            i--;
                            printf("\b \b"); // Move the cursor back and erase the character
                        }
                    }
                    // Skip spaces and check for special characters
                    else if (ch != ' ') {
                        saveusername[i++] = ch;
                        printf("%c", ch); // Print the character
                    }
                }
                if (!IsValidUsername(saveusername)){
                    printf("\nCannot use these special characters(\\ / : * ? \" < > |). Please try again. \n");
                }
                else break;
            }while(1);

            //new folder to seperate user
            mkdir(saveusername);
            //clear string
            bzero(filename,20);
            //folder name
            strcat(filename,saveusername);
            strcat(filename,"/");
            strcat(filename,saveusername);
            strcat(filename,".txt");
            fp = fopen(filename,"w");
            //input password + change to *
            printf("\nEnter password : ");
            fflush(stdin);
            int i=0;
            while (1){
                ch = getch();
                if (ch == 13){
                    savepass[i] = '\0';
                    break;
                }
                else if (ch == 8){
                    if (i > 0){
                        i--;
                        printf("\b \b");
                    }
                }
                else if (ch == 9 || ch == 32){
                    continue;
                }
                else{
                    savepass[i++] = ch;
                    printf("*");
                }
            }
            fprintf(fp,"%s",savepass);
            printf("\n");
            fclose(fp);
            system("cls");
            break;
        case 3: exit(0);
        default: printf("\n");break;
        }
    }

name:
    printf(" ===================================\n        Schedule Disentangle\n ===================================\n\n\n");
    printf(" (\\__/) ==================== (\\__/)\n ( •_•)");
    printf("         LOGIN        " );
    printf("(•_• )\n / >  > ==================== <  < \\\n\n\n");
    printf("Enter username : ");
    fflush(stdin);
    //input username
    gets(user);
    //clear string
    bzero(rfilename,20);
    //username
    strcat(rfilename,user);
    strcat(rfilename,"/");
    strcat(rfilename,user);
    strcat(rfilename,".txt");

    FILE *ptr;
    ptr = fopen(rfilename,"r");
    char ans;

    fflush(stdin);
    fgets(passf,sizeof(passf),ptr);
    //confirm (y/n)
    if(ptr == NULL)
    {
        printf("\n**********Incorrect username**********\n");
        printf("           Please try again\n\n");
        while(1){
            printf("Do you want to signup (y/n) : ");
            scanf("%s",&ans);
            if(ans == 'y'||ans == 'Y'){
                printf("\n");
                system("cls");
                goto sign;
                break;
            }
            else if(ans == 'n'||ans == 'N'){
                printf("\n");
                system("cls");
                goto name;
                break;
            }
            else{
                printf("\n");
                system("cls");
            }
        }
    }
    else{
        //input password change to *
        start:
        printf("Enter password : ");
        fflush(stdin);
        int i=0;
        while (1){
            ch = getch();
            if (ch == 13){
                pass[i] = '\0';
                break;
            }
            else if (ch == 8){
                if (i > 0){
                    i--;
                    printf("\b \b");
                }
            }
            else if (ch == 9 || ch == 32){
                continue;
            }
            else{
                pass[i++] = ch;
                printf("*");
            }
        }
    }

    int l = strcmp(passf,pass);
    if(l==0){
        system("cls");
        printf(" ====================================\n        Schedule Disentangle\n ====================================");
        printf("\n***********LOGIN SUCCESSFUL***********\n\n");
    }
    else{
        printf("\n**********INCORRECT PASSWORD**********\n");
        count+=1;
        if(count<3){
            goto start;
        }
        else{
            system("cls");
            goto sign;
        }
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////////

void getInput(int *year, int *month) {
    char inputy[50];
    char inputm[50];
    int validInputYear = 0, validInputMonth = 0;

    // Get input year
    do {
        printf("Enter the year: ");
        fgets(inputy, sizeof(inputy), stdin);
        if (strlen(inputy) <= 10 && sscanf(inputy, "%d", year) == 1 && *year > 0) {
            validInputYear = 1;
        }
        else {
            printf("!!!!!Invalid input.!!!!!\n");
        }
        fflush(stdin);
    } while (!validInputYear);

    // Get input month
    do {
        printf("Enter the month(1-12): ");
        fgets(inputm, sizeof(inputm), stdin);
        if (sscanf(inputm, "%d", month) == 1 && *month > 0 && *month <= 12) {
            validInputMonth = 1;
        }
        else {
            printf("!!!!!Invalid input. Please enter a valid integer.!!!!!\n");
        }
        fflush(stdin);
    } while (!validInputMonth);
}

//days in each month
int TotalDays(int month, int year){
    int days;
    switch (month) {
        case 4:
        case 6:
        case 9:
        case 11:
            days = 30;
            break;
        case 2:
            if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
                days = 29;
            } else {
                days = 28;
            }
            break;
        default:
            days = 31;
    }
    return days;
}

//show calendar
void calendar(int month, int year){
    int day = TotalDays(month, year);
    char *monthNames[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
    int startday =1, currentday=1, i;
    printf("\n%s | %d\n", monthNames[month - 1], year);
    printf("--------------------------------------------------------\n");
    printf("  Sun\t  Mon\t  Tue\t  Wed\t  Thu\t  Fri\t  Sat\n");
    printf("--------------------------------------------------------\n");

    for (i = 1900; i < year; i++) {
        if ((i % 4 == 0 && i % 100 != 0) || (i % 400 == 0)) {
            startday = (startday + 366) % 7;
        }
        else {
            startday = (startday + 365) % 7;
        }
    }

    for (i = 1; i < month; i++) {
        startday = (startday + TotalDays(i, year)) % 7;
    }


    for(i=0; i<startday; i++){
        printf("\t");
    }
    while(currentday<=day){
        printf("%5d\t", currentday);
        if((currentday+startday)%7 == 0)
            printf("\n");
        currentday++;
    }
    printf("\n");
}

//add event
void addEvent( int *month,int *year,char user[]){ //wip
    int day,fn,validInputd = 0;;
    char ans;
    FILE *fp;
    char description[100],inputd[50],rfilename[20];

    int days = TotalDays(*month, *year);

    //input days
    do {
        fflush(stdin);
        printf("Day : ");
        fgets(inputd, sizeof(inputd), stdin);
        validInputd = 0;
        // Use sscanf to attempt to convert the string to an integer
        if (sscanf(inputd, "%d", &day) == 1 && day>0 && day<=days) {
                validInputd = 1; // Set flag to exit the loop
        }
        else {
            printf("!!!!!Invalid input. Please enter a valid integer.!!!!!\n");
        }
    } while (!validInputd);

    printf("Date : %d/%d/%d\n",day,*month,*year);
    //file
    bzero(rfilename,20);
    strcat(rfilename,user);
    strcat(rfilename,"/");
    strcat(rfilename,"event.txt");
    fp = fopen(rfilename,"a");

    //discription can have only 100 letter.
    while(1){
        printf("Input Event : ");
        fflush(stdin);
        gets(description);
        if(strlen(description)<=100) break;
        else printf("Try Again!!!\n");
    }

    //confirm (y/n)
    while(1){
        printf("Confirm to add event (y/n) : ");
        fflush(stdin);
        scanf("%c",&ans);
        if(ans=='y'||ans=='Y'){
            fprintf(fp,"Date : %d/%d/%d\n",day,*month,*year);
            fputs(description,fp);
            fprintf(fp,"\n-----------------------\n");
            fclose(fp);
            printf("Add event success!!!\n");
            break;
        }
        else if(ans=='n'||ans=='N'){
            fclose(fp);
            printf("Add event canceled.\n");
            break;
        }
        else{
            printf("Invalid input. Please enter 'y' or 'n'.\n");
        }
    }
}

//viewevent
void viewEvent(char user[]){
    FILE *fp;
    char ch1,ch2,rfilename[20];
    printf("\t   ----------------\n\t   |  View event  |\n\t   ----------------\n");
    bzero(rfilename,20);
    //file name
    strcat(rfilename,user);
    strcat(rfilename,"/");
    strcat(rfilename,"event.txt");
    fp = fopen(rfilename,"r");
    //have event or not
    ch1 = fgetc(fp);
    printf("%c",ch1);
    if(ch1==EOF) printf("No Event!!!\n");
    //read from file
    else {while(!feof(fp)){
            ch2 = fgetc(fp);
            if(ch2 != EOF)printf("%c",ch2);
            else break;
        }
        fclose(fp);}
}

//deleteevent
int DeleteEvent(int *month, int *year,char user[]) {
    printf("\t  ------------------\n\t  |  Delete event  |\n\t  ------------------\n");

    int dday,dmonth,dyear;
    char sdday[10],sdmonth[10],sdyear[10],rfilename[20],ch1;

    bzero(rfilename,20);
    strcat(rfilename,user);
    strcat(rfilename,"/");
    strcat(rfilename,"event.txt");

    // Open the file in read mode
    FILE *file = fopen(rfilename, "r");

    if (file == NULL) {
    perror("Error opening file");
        return 1;
    }

    // Create a temporary file to store the modified content
    FILE *tempFile = fopen("temp.txt", "w");

    if (tempFile == NULL) {
        perror("Error creating temporary file");
        fclose(file);
        return 1;
    }

    char line[100]; // Adjust the size based on your needs
    int lineCounter = 0;

    char titleToDelete[19],titleToDelete2[19];
    printf("Enter the date of the event to delete (DD/MM/YYYY) : ");
    scanf("%s", titleToDelete);

    //confirm
    while(1){
        char ans;
        printf("Confirm to Delete event (y/n) : ");
        fflush(stdin);
        scanf("%c",&ans);
        if(ans == 'y' || ans == 'Y'){
            //change string to int
            sscanf(titleToDelete, "%d/%d/%d", &dday,&dmonth,&dyear);
            //change int to string
            sprintf(sdday,"%d",dday);
            sprintf(sdmonth, "%d", dmonth);
            sprintf(sdyear, "%d", dyear);
            //clear string
            bzero(titleToDelete2, 19);
            //file name
            strcat(titleToDelete2,sdday);
            strcat(titleToDelete2,"/");
            strcat(titleToDelete2,sdmonth);
            strcat(titleToDelete2,"/");
            strcat(titleToDelete2,sdyear);

            int temp,noevent = 0;

            // Read each line from the original file
            while (fgets(line, sizeof(line), file) != NULL) {
                lineCounter++;

                // Check if the current line should be deleted
                int deleteLine = 0;
                if (strstr(line, titleToDelete2) != NULL){
                   temp = lineCounter;
                   noevent++;
                }
                if(lineCounter>=temp&&lineCounter<=temp+2) deleteLine = 1;

                // Write the line to the temporary file only if it shouldn't be deleted
                if (!deleteLine) {
                    fputs(line, tempFile);
                }
            }
            if(noevent == 0)printf("\n<<No event in this day.>>\n");

            // Close both files
            fclose(file);
            fclose(tempFile);

            if (remove(rfilename) != 0) {
                perror("Error deleting original file");
                return 1;
            }

            // Rename the temporary file to the original file
            if (rename("temp.txt", rfilename) != 0) {
                perror("Error renaming temporary file");
                return 1;
            }

            if(noevent != 0) printf("Lines deleted successfully.\n");
            break;
        }
        else if(ans == 'n'||ans == 'N'){
            fclose(file);
            fclose(tempFile);
            printf("Delete event cancled.\n");
            break;
        }
        else printf("Try Again!!!!\n");
    }

    return 0;
}

int option(int opt, int *continueOpt, int *month, int *year, int *day, char user[]){
    switch (opt) {
        case 1: //addEvent
            system("cls");
            printf(" ====================================\n         Schedule Disentangle\n ====================================\n");
            printf("\t   ---------------\n\t   |  Add Event  |\n\t   ---------------\n");
            addEvent(month,year,user);
            break;
        case 2: //viewEvent
            system("cls");
            printf(" ====================================\n         Schedule Disentangle\n ====================================\n");
            viewEvent(user);
            break;
        case 3: //deleteEvent
            system("cls");
            printf(" ====================================\n         Schedule Disentangle\n ====================================\n");
            viewEvent(user);
            DeleteEvent(month,year,user);
            break;
        case 4: //prevMonth
            system("cls");
            printf("\t   ====================================\n\t           Schedule Disentangle\n\t   ====================================\n");
            printf("\t\t   --------------------\n\t\t   |  Previous month  |\n\t\t   --------------------\n");
                if (*month == 1) {
                *month = 12;
                *year -= 1;
                    if(*year == -1){
                        printf("/nError. Invalid Year./n");
                    }
                    else calendar(*month, *year);
                }
                else {
                *month -= 1;
                calendar(*month, *year);
                }
            break;
        case 5: //nextMonth
            system("cls");
            printf("\t   ====================================\n\t           Schedule Disentangle\n\t   ====================================\n");
            printf("\t\t     ----------------\n\t\t     |  Next month  |\n\t\t     ----------------\n");
            if (*month == 12) {
                *month = 1;
                *year += 1;
            } else {
                *month += 1;
            }
            calendar(*month, *year);
            break;
        case 6: //changeYear
            system("cls");
            printf("\t   ====================================\n\t           Schedule Disentangle\n\t   ====================================\n");
            printf("\t\t     ----------------\n\t\t     |  Change Year  |\n\t\t     ----------------\n");
            getInput(year, month);  // Update year and month with new values
            printf("\n\t   ====================================\n\t           Schedule Disentangle\n\t   ====================================\n");
            calendar(*month, *year);
            return 1; // Indicate that year and month were updated
        case 0: //back
        default:
            *continueOpt = 1;
            char ans;
            while(1){
                fflush(stdin);
                printf("Do you want to logout? (y/n) : ");
                scanf("%c",&ans);
                if(ans == 'y'||ans == 'Y'){
                    printf("-----------------------------Logout-----------------------------\n");
                    *continueOpt = 0;
                    system("cls");
                    break;
                }
                else if(ans == 'n'||ans == 'N'){
                    system("cls");
                    printf("\t   ====================================\n\t           Schedule Disentangle\n\t   ====================================\n");
                    calendar(*month, *year);
                    break;
                }
                else{
                    printf("Try Again!!!\n");
                }
            }
    }
    return *continueOpt;
}

int main(void) {
    int year, month, opt;
    char user[20];
    int finish = 0;

    while (finish == 0) {
        login(user);
        getInput(&year, &month);
        system("cls");

        // Display Calendar
        printf("\t   ====================================\n\t           Schedule Disentangle\n\t   ====================================\n");
        // Call the calendar function
        calendar(month, year);

        int continueOpt = 1; // to loop for option
        while (continueOpt) {
            printf("\nOption: \n1. Add event\n2. View events\n3. Delete event\n4. Previous month\n5. Next month\n6. Change Year\n0. Logout\n\n");

            int validInputOpt = 0;
            char inputopt[50];

            //selectoption + check
            do {
                printf("Select an option: ");
                fflush(stdin);
                fgets(inputopt, sizeof(inputopt), stdin);

                // Use sscanf to attempt to convert the string to an integer
                if (sscanf(inputopt, "%d", &opt) == 1 && opt >= 0 && opt <= 6) {
                    validInputOpt = 1;
                } else {
                    printf("!!!!!Invalid input. Please enter a valid integer.!!!!!\n");
                }

            } while (!validInputOpt);

            // Call the option function
            continueOpt = option(opt, &continueOpt, &month, &year, NULL, user);
        }
    }

    return 0;
}
