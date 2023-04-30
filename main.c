//sleman ghithan 1202009
//for example if there is a way from Akka to Nazareth is 33Km,the there is way from Nazareth to Akka with same distance
//if you need the road to  be one way just delete 203-212 lines .
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INF 99999999//infinite number for nodes
struct Dijk{
    char from [100];//from
    char into [100];//into
    int distance ;//distance between fom and into
};
void fileReader( struct Dijk  [500]);//read the file data
int Max=0;//the number of cities in the graph
int fileMax=0;//number of lines in the file
void findMax(struct Dijk  [500],char  [500] [100]);//count max and file max
void bulidGraph(struct Dijk [500], char[500][100], int graphDistance [Max][Max]);//build the graph and the 2D array
int getIndex(char  [500] [100],char  [100]);//get index of a specific city index in the cities array
int getDistanceBetween(char [100],char  [100],struct Dijk  [500]);//return the distance between two cities
void dijkstra(int [Max][Max],char [500][100],char  [100],int [500],int [Max]);//dijkstra function
int printOutput(int [] , int [500],char  [100],char [100],char  [500] [100],int [500][500] );//print the final output
char output [500];//the output on console
char fileOutput [1000];//the output on file
int main() {
    struct Dijk mainGraph[500];
    char names[500][100];
    char fromN [100];
    char intoN [100];
    int choice = 0;
    int path[500] ;
    int graphDistance[500][500];
    int distance[500];
    while (1) {
        printf("1. Load cities: loads the file and construct the graph\n"
               "2. Enter source city: read the source city and compute the Dijkstra algorithm (single source shortest path)\n"
               "3. Enter destination city: print the full route of the shortest path including the distance between each two cities and the total shortest cost\n"
               "4. Exit: prints the information of step 3 to a file called shortest_path.txt and exits the program\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                fileReader(mainGraph);//read the file
                findMax(mainGraph, names);//find max and file max
                bulidGraph(mainGraph, names, graphDistance);//build the graph
                printf("the file loaded and the graph constructed  successfully\n");
                printf("------------------------------------------------------------------------------------------------------------------------\n\n");
            };break;
            case 2: {
                int isFound=0,firstTime=0;
                while(isFound==0) {
                    int i=0;
                    if(firstTime==0) {
                        fflush(stdin);
                        printf("please enter the source city name carefully\n");
                        scanf("%[a-z,A-Z,0-9,' ']c", fromN);
                        firstTime=1;
                    }
                    while (i < Max) {
                        if (strcmp(fromN, names[i]) == 0) {
                            isFound = 1;
                        }
                        i++;
                    }
                    if(firstTime==1&&isFound==0) {
                        fflush(stdin);
                        printf("sorry,the name you enter it not found in the data base please try again\n");
                        scanf("%[a-z,A-Z,0-9,' ']c", fromN);
                        firstTime=1;
                    }
                }
                printf("the city %s founded successfully\n",fromN);
                dijkstra( graphDistance, names  , fromN ,path,distance);//get the shortest path from source city to all other cities
                int s=0;
                int r= getIndex(names,fromN);
                while(s<Max){
                    if(s!=r) {
                        printf("the shortest path between <%s> and <%s> is:%d\n", names[r], names[s], distance[s]);

                    }
                    s++;
                }
                printf("------------------------------------------------------------------------------------------------------------------------\n\n");
            };break;
            case 3: {
                int isFound=0,firstTime=0;
                while(isFound==0) {
                    int i=0;
                    if(firstTime==0) {
                        fflush(stdin);
                        printf("please enter the destination city name carefully\n");
                        scanf("%[a-z,A-Z,0-9,' ']c", intoN);
                        firstTime=1;
                    }
                    while (i < Max) {
                        if (strcmp(intoN, names[i]) == 0) {
                            isFound = 1;
                        }
                        i++;
                    }
                    if(firstTime==1&&isFound==0) {
                        fflush(stdin);
                        printf("sorry,the name you enter it not found in the data base please try again\n");
                        scanf("%[a-z,A-Z,0-9,' ']c", intoN);
                        firstTime=1;
                    }

                }
                printf("the city %s founded successfully\n",intoN);
                printOutput(distance,  path, fromN , intoN, names ,graphDistance );//print the output
                printf("------------------------------------------------------------------------------------------------------------------------");
            };break;
            case 4: {
                FILE *FileWriter;//file pointer
                FILE *FileReader;
                FileWriter= fopen("shortest_path.txt","a");
                fputs(fileOutput, FileWriter);//append on file
                fclose(FileWriter);
                printf("the output printed in the file successfully\n");
                return 0;
            };break;
        }

    }
    return 0;
}
void fileReader( struct Dijk mainGraph [500]){//read file and load data in the tables
    FILE *fileReader;//file pointer
    fileReader= fopen("cities.txt","r");//open file in read mode
    if(fileReader==NULL){
        printf("error while reading file\n");
        return ;
    }
    else{
        char Read [250];
        int i=0;
        while( fgets(Read,sizeof (Read),fileReader)!=NULL){//read line by line
            char fromN [100];
            char intoN [100];
            int distanceN;
            //trim
            char *token= strtok(Read,"\t");
            strcpy(fromN,token);
            token= strtok(NULL,"\t");
            strcpy(intoN,token);
            token= strtok(NULL,"k");
            distanceN=atoi(token);
            strcpy(mainGraph[i].from,fromN);
            strcpy(mainGraph[i].into,intoN);
            mainGraph[i].distance=distanceN;
            i++;
            fileMax++;

        }

    }
    return;
}
void findMax( struct Dijk mainGraph [500],char names [500] [100]){
    int i=0;
    while (i<fileMax){//get all sources cities and count them
        int found=0,j=0;
        while (j<Max){
            if(strcmp(names [j],mainGraph[i].from)==0){//if it's found before
                found=1;
            }
            j++;
        }
        if(found==0){//if not founded before
            strcpy(names[j],mainGraph[i].from);
            Max++;
        }
        i++;
    }
    i=0;
    while (i<fileMax){//get all distentions cities and count them
        int found=0,j=0;
        while (j<Max){
            if(strcmp(names [j],mainGraph[i].into)==0){//if it's found before
                found=1;
            }
            j++;
        }
        if(found==0){//if not founded before
            strcpy(names[j],mainGraph[i].into);
            Max++;
        }
        i++;
    }

}
void bulidGraph(struct Dijk mainGraph [500],char names [500] [100], int graphDistance [Max][Max]){//put all distances between each two cities in the array
    for(int i=0;i<Max;i++){//first diminution
        for(int j=0;j<Max;j++){//second diminution
            if(i==j){//distance between the city and itself is zero
                graphDistance[i][j]=0;
            }
            else{
                graphDistance[i][j]= getDistanceBetween(names[i],names[j],mainGraph);//get the distance
            }

        }
    }

    for(int i=0;i<Max;i++){//first diminution
        for(int j=0;j<Max;j++) {//second diminution
            if (i == j) {//distance between the city and itself is zero
                graphDistance[i][j] = 0;
            }
            else if(graphDistance[i][j]!=0){
                graphDistance[j][i] = graphDistance[i][j];
            }
        }
    }


}
int getIndex(char names [500] [100],char name [100]){//get the specific index of a city name in cities array
    int i=0;
    while(i<Max){
        if(strcmp(names[i],name)==0){
            return i;
        }
        i++;
    }
    return -1;
}
int getDistanceBetween(char fromN[100],char intoN [100],struct Dijk mainGraph [500]){
    int i=0;
    while (i<fileMax){//while less the file max
        if(strcmp(mainGraph[i].from,fromN)==0&&strcmp(mainGraph[i].into,intoN)==0){//if found
            return mainGraph[i].distance;//return the distance
        }
        i++;
    }
    return 0;//if not found
}
int findMinimum(int distance[], int isVisted[]){
    int min = INF, minimumIndex;
    for (int v = 0; v < Max; v++)//for each
        if (isVisted[v] == 0 && distance[v] <= min)//if it's not visited and the distance less than the minimum
            min = distance[v], minimumIndex = v;//swap
    return minimumIndex;
}
void thePath(int parent[], int j ,char names [500] [100]){//print the path
    if (parent[j] == -1)//final time
        return;
    thePath(parent, parent[j],names);//recursion
    printf("-> %s", names[j]);//print
    char temp [30]="->";
    strcat(temp,names[j]);
    strcat(output,temp);//in the output
}
void printAll(int cost [Max][Max],char names [500][100],char into[100]){//print all data
    printf("\n");
    char temp [500];
    strcpy(temp,output);
    strcpy(fileOutput,output);
    char fromN[100];
    char intoN [100];
    int index1,index2;
    //trim
    char *token= strtok(temp,"\n");
    token= strtok(NULL,"\n");
    token = strtok(NULL, "-> ");
    strcpy(fromN,token);
    strcat(fileOutput,"\nthe distance between each tow cities:\n");
    while (token!=NULL) {//to print the distance between each two cities
        index1=getIndex(names,fromN);
        if(strcmp(intoN,into)==0){
            break;
        }
        token = strtok(NULL, "-> ");
        strcpy(intoN,token);
        index2=getIndex(names,intoN);
        printf("%s->%s:%d KM\n",fromN,intoN,cost[index1][index2]);
        strcat(fileOutput,"\n");
        strcat(fileOutput,fromN);
        strcat(fileOutput,"->");
        strcat(fileOutput,intoN);
        strcat(fileOutput,":");
        char num [25];
        itoa(cost[index1][index2],num,10);
        strcat(fileOutput,num);
        strcat(fileOutput," KM");
        strcat(output,num);
        strcat(output," KM");
        strcpy(fromN,intoN);
    }
}
int printOutput(int dist[], int parent[500],char fromN [100],char intoN[100],char names [500] [100],int cost[500][500] ){
    for (int i = 0; i < Max; i++) {
        if(strcmp(names [i],intoN)==0) {
            strcpy(output,"the total distance between ");
            strcat(output,fromN);
            strcat(output," and ");
            strcat(output,intoN);
            strcat(output," is: ");
            char num [25];
            itoa(dist[i],num,10);
            strcat(output,num);
            strcat(output,"KM ");
            strcat(output," KM\nand the shortest path between them is: \n");
            strcat(output,fromN);
            printf("%s",output);
            thePath(parent, i,names);
            printf("\nthe distance between each tow cities:\n");
            printAll(cost,names,intoN);
            strcat(fileOutput,"\n-------------------------------------------------------------\n");
            printf("\n");
        }
    }
}
void dijkstra(int cost[Max][Max],char names [500] [100] ,char fromN [100],int path[500],int distance[Max]){
    int visted[Max];//to check if the node visited or not
    int s=0;
    while(s<Max){
        visted[s]=0;//initialize all with zero
        path[s]=-1;//initialize all with -1
        distance[s]=INF;//initialize all with infinity
        s++;
    }
    int count,j;
    int index1 = getIndex(names,fromN);//get the index of the source city
    distance[index1]=0;//it's distance is zero
    for ( count = 0; count < Max - 1; count++) {
        int u = findMinimum(distance, visted);//find the minimum distance for all
        visted[u]=1;//set as visited
        for(j=0;j<Max;j++){
            if (!visted[j] && cost[u][j]
                && distance[u] + cost[u][j] < distance[j]) {//if the node not visited yet, and it's less distance than the other one
                path[j]=u;//set pathe as minimum
                distance[j] = distance[u] + cost[u][j];//change to the new distance
            }
        }
    }
}