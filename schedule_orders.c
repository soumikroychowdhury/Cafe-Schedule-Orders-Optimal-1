#include<stdio.h>
void schedule_orders_a(int *arr,int n,int k){ //function to schedule orders (part a)
    printf("Part (a)\n\n");
    int ordercounters[k][n][2]; //store order counters and details
    int countersprint[k][n];
    int indicesorder[k],indicesprint[k];
    for(int i=0;i<k;i++){ //initialize counters
        indicesorder[i]=0;
        indicesprint[i]=0;
        countersprint[i][0]=0;
        ordercounters[i][0][0]=arr[i];
        ordercounters[i][0][1]=i;
    }
    int j=k,totalwait=0,closetime=0,val=0;
    while(j<n){
        int mn=__INT_MAX__,mi=__INT_MAX__;
        for(int i=0;i<k;i++){ //find which completes first
            if(ordercounters[i][indicesorder[i]][0]<mn){
                mn=ordercounters[i][indicesorder[i]][0];
                mi=i;
            }
        }
        totalwait+=mn; //add to the waiting time
        val=mn+arr[j];
        indicesorder[mi]++;
        indicesprint[mi]++;
        countersprint[mi][indicesprint[mi]]=mn;
        ordercounters[mi][indicesorder[mi]][0]=val; //add the next order
        ordercounters[mi][indicesorder[mi]][1]=j;
        j++;
    }
    printf("Order Schedule (processing time for each order within parentheses)\n");
    for(int i=0;i<k;i++){
        printf("Counter\t %d:\t",i+1);
        for(int j=0;j<=indicesorder[i];j++) printf("%d (%d)\t",ordercounters[i][j][1]+1,ordercounters[i][j][0]-countersprint[i][j]);
        printf("\n");
    }

	for(int i=0;i<k;i++){ //to find the closing time
		if(closetime<ordercounters[i][indicesorder[i]][0]) closetime=ordercounters[i][indicesorder[i]][0];
    }
	printf("Cafe closes at time: %d\n",closetime);
	printf("Total waiting time: %d\n",totalwait);
}
void merge(int arr[][2],int l,int m,int r){ //merge arrays
    int n1=m-l+1,n2=r-m;
    int left[n1][2],right[n2][2]; //temporary arrays
    for(int i=0;i<n1;i++){
        left[i][0]=arr[l+i][0];
        left[i][1]=arr[l+i][1];
    }
    for(int i=0;i<n2;i++){
        right[i][0]=arr[m+1+i][0];
        right[i][1]=arr[m+1+i][1];
    }
    int i=0,j=0,k=l; //compare the elements and sort them in descending/non-increasing order
    while(i<n1&&j<n2){
        if(left[i][0]>=right[j][0]){
            arr[k][0]=left[i][0];
            arr[k][1]=left[i][1];
            i++;
        }
        else{
            arr[k][0]=right[j][0];
            arr[k][1]=right[j][1];
            j++;
        }
        k++;
    }
    while(i<n1){ //if there are elements left in the left array
        arr[k][0]=left[i][0];
        arr[k][1]=left[i][1];
        i++;
        k++;
    }
    while(j<n2){ //if there are elements left in the right array
        arr[k][0]=right[j][0];
        arr[k][1]=right[j][1];
        j++;
        k++;
    }
}
void mergeSort(int arr[][2],int l,int r){ //merge sort
    if(l<r){ //for more than 1 element
        int m=l+(r-l)/2; //mid value
        mergeSort(arr,l,m); //divide
        mergeSort(arr,m+1,r);
        merge(arr,l,m,r); //conquer
    }
}
void schedule_orders_b(int *a,int n,int k){ //function to schedule orders (part b)
    printf("Part (b)\n\n");
    int arr[n][2]; //store original indices before sorting
    for(int i=0;i<n;i++){
        arr[i][0]=a[i];
        arr[i][1]=i;
    }
    mergeSort(arr,0,n-1); //sort in decreasing/non-increasing order
    int ordercounters[k][n][2]; //store order counters and details
    int countersprint[k][n];
    int indicesorder[k],indicesprint[k];
    for(int i=0;i<k;i++){
        indicesorder[i]=0; //initialize counters
        indicesprint[i]=0;
        countersprint[i][0]=0;
        ordercounters[i][0][0]=arr[i][0];
        ordercounters[i][0][1]=arr[i][1];
    }
    int j=k,totalwait=0,closetime=0,val=0;
    while(j<n){ //find which completes first
        int mn=__INT_MAX__,mi=__INT_MAX__;
        for(int i=0;i<k;i++){
            if(ordercounters[i][indicesorder[i]][0]<mn){
                mn=ordercounters[i][indicesorder[i]][0];
                mi=i;
            }
        }
        totalwait+=mn; //add to the waiting time
        val=mn+arr[j][0];
        indicesorder[mi]++;
        indicesprint[mi]++;
        countersprint[mi][indicesprint[mi]]=mn;
        ordercounters[mi][indicesorder[mi]][0]=val; //add the next order
        ordercounters[mi][indicesorder[mi]][1]=arr[j][1];
        j++;
    }
    printf("Order Schedule\n");
    for(int i=0;i<k;i++){
        printf("Counter\t %d:\t",i+1);
        for(int j=0;j<=indicesorder[i];j++) printf("%d (%d)\t",ordercounters[i][j][1]+1,ordercounters[i][j][0]-countersprint[i][j]);
        printf("\n");
    }

	for(int i=0;i<k;i++){ //to find the closing time
		if(closetime<ordercounters[i][indicesorder[i]][0]) closetime=ordercounters[i][indicesorder[i]][0];
    }
	printf("Cafe closes at time: %d\n",closetime);
	printf("Total waiting time: %d\n",totalwait);
}
int wait_time(int ordercounters[][2], int ns, int k, int countersprint[]){ //to calculate waiting time
    int val=0,wait=0;
    for(int j=0;j<ns;j++){
        val=ordercounters[j][0]-countersprint[j];
        wait+=val*(ns-j);
    }
    return wait;
}
void schedule_orders_c(int *a,int n,int k){ //function to schedule orders (part c)
    printf("Part (c)\n\n");
    int arr[n][2]; //store original indices before sorting
    for(int i=0;i<n;i++){
        arr[i][0]=a[i];
        arr[i][1]=i;
    }
    mergeSort(arr,0,n-1); //sort in decreasing/non-increasing order
    int ordercounters[k][n][2]; //store order counters and details
    int countersprint[k][n];
    int indicesorder[k],indicesprint[k];
    for(int i=0;i<k;i++){
        indicesorder[i]=0; //initialize counters
        indicesprint[i]=0;
        countersprint[i][0]=0;
        ordercounters[i][0][0]=arr[i][0];
        ordercounters[i][0][1]=arr[i][1];
    }
    int j=k,totalwait=0,closetime=0,val=0,on=0;
    while(j<n){ //find which completes first
        int mn=__INT_MAX__,mi=__INT_MAX__;
        for(int i=0;i<k;i++){
            if(ordercounters[i][indicesorder[i]][0]<mn){
                mn=ordercounters[i][indicesorder[i]][0];
                mi=i;
            }
        }
        val=mn+arr[j][0]; //add to the waiting time
        indicesorder[mi]++;
        indicesprint[mi]++;
        countersprint[mi][indicesprint[mi]]=mn;
        ordercounters[mi][indicesorder[mi]][0]=val; //add the next order
        ordercounters[mi][indicesorder[mi]][1]=arr[j][1];
        j++;
    }
    for(int i=0;i<k;i++){ //to find max orders in a counter
        int a=indicesorder[i]+1;
        if(on<a) on=a;
    }
    for(int i=0;i<k;i++){ //to reduce the total waiting time
        if(indicesorder[i]+1==on){
            int a=ordercounters[i][0][0],b=ordercounters[i][0][1];
            ordercounters[i][0][0]=ordercounters[i][on-1][0],ordercounters[i][0][1]=ordercounters[i][on-1][1];
            ordercounters[i][on-1][0]=a,ordercounters[i][on-1][1]=b;
            a=countersprint[i][0];
            countersprint[i][0]=countersprint[i][on-1];
            countersprint[i][on-1]=a;
        }
    }
    for(int i=0;i<k;i++) totalwait+=wait_time(ordercounters[i],indicesorder[i],k,countersprint[i]); //to calculate the total waiting time
    printf("Order Schedule\n");
    for(int i=0;i<k;i++){
        printf("Counter\t %d:\t",i+1);
        for(int j=0;j<=indicesorder[i];j++){
            printf("%d (%d)\t",ordercounters[i][j][1]+1,ordercounters[i][j][0]-countersprint[i][j]);
        }
        printf("\n");
    }
	for(int i=0;i<k;i++){ //to find the closing time
        if(indicesorder[i]+1==on){
            if(closetime<ordercounters[i][0][0]) closetime=ordercounters[i][0][0];
        }
		else{
            if(closetime<ordercounters[i][indicesorder[i]][0]) closetime=ordercounters[i][indicesorder[i]][0];
        }
    }
	printf("Cafe closes at time: %d\n",closetime);
	printf("Total waiting time: %d\n",totalwait);
}
void print_schedule(int *arr,int n,int k){ //for part a, b and c
    printf("\n");
    schedule_orders_a(arr,n,k);
    printf("\n----\n\n");
    schedule_orders_b(arr,n,k);
    printf("\n----\n\n");
    schedule_orders_c(arr,n,k);
}
int main(){
    int n,k;
    printf("n = "); //take inputs
    scanf("%d",&n);
    printf("k = ");
    scanf("%d",&k);
    printf("\n");
    int t[n];
    printf("Enter order processing times:\n\n");
    for(int i=0;i<n;i++) scanf("%d",&t[i]);
    print_schedule(t,n,k); //print details
    return 0;
}