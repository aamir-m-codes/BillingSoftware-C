#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct items
{
    int qty;
    float price;
    char items_name[15];
};

typedef struct billing
{
    char name[30];
    char date[15];
    char time[15];
    int items;
    int invoice_number;
    struct items it[40];
} billing;


void bill_header(char name[30], char date[15], char time[15], int invoice_number)
{
    printf("\n\n\t\t\t*****MALIK's super market*****\n\n");
    printf("\t\t\t\t_-_-_-_-_-_-_-_\n");
    printf("\tCustomer\t%s\n", name);
    printf("\tDate\t\t%s\n", date);
    printf("\tTime\t\t%s\n", time);
    printf("\t-------------------------------------------------------------------------------\n");
    printf("\tItems\t\t\t");
    printf("Qty\t\t\t");
    printf("price\t\t\t");
    printf("Total\n");
    printf("\t-------------------------------------------------------------------------------\n");
}

float bill_body(int qty, float price, char items_name[30], float total)
{
    float net = 0.0;
    total = qty * price;
    printf("\t%s\t\t\t", items_name);
    printf("%d\t\t\t", qty);
    printf("%.2f\t\t\t", price);
    printf("%.2f\n", total);
    net += total;
    return net;
}

void bill_footer(float net)
{
    float dis, grand_total;
    printf("\n\tNet total\t\t\t\t\t\t\t\t%.2f\n", net);
    dis = 0.1 * net;
    printf("\t@10 discount\t\t\t\t\t\t\t\t%.2f\n", dis);
    grand_total = net - dis;
    printf("\tFinal total\t\t\t\t\t\t\t\t%.2f\n", grand_total);
    printf("\t-------------------------------------------------------------------------------\n");
}

char * description(const char *str,const char * oldword,const char * newword)
{
    char * resstring;
    int oldlen,newlen,count = 0,i;
    oldlen = strlen(oldword);
    newlen = strlen(newword);
    for( i = 0; str[i] != '\0';i++ )
    {
        if(strstr(&str[i],oldword) == str)
        {
            count++;
        }
        i = i + oldlen - 1;
    }
    resstring = (char * ) malloc(i+count * (newlen - oldlen) + 1);
    i = 0;
    while(*str != '\0')
    {
        if(strstr(str,oldword) == str)
        {
            strcpy(&resstring[i],newword);
            i += newlen;
            str += oldlen;
        }
        else
        {
            resstring[i] = *str;
            i += 1;
            str += 1;
        }
    }
    resstring[i] =  '\0';
    return resstring;
}

void create()
{
    system("cls");
    FILE * p;
    int num;
    char str[100],*retrstring;
    p = fopen("Billing.txt", "r");
    fseek(p,0,SEEK_END);
    num = ftell(p)/sizeof(billing);
    rewind(p);
    fclose(p);
    static int count_invoice = 0;
    count_invoice = num;
    int n;
    billing c1;
    strcpy(c1.date, __DATE__);
    strcpy(c1.time, __TIME__);
    float net = 0.0;
    float total = 0.0;
    char ch = 'n';
    fflush(stdin);
    printf("Enter the name of customer. ");
    scanf("%[^\n]s", &c1.name);
    printf("Enter the numbers of items. ");
    scanf("%d", &n);
    c1.items = n;
    fflush(stdin);
    for (int i = 0; i < n; i++)
    {
        printf("Enter a name of %d item. ", i + 1);
        scanf("%[^\n]s", &c1.it[i].items_name);
        printf("Enter the price of item %d. ", i + 1);
        scanf("%f", &c1.it[i].price);
        printf("Enter the quantity of item %d. ", i + 1);
        scanf("%d", &c1.it[i].qty);
        fflush(stdin);
    }
    count_invoice++;
    c1.invoice_number = count_invoice;
    bill_header(c1.name, c1.date, c1.time, c1.invoice_number);
    for (int i = 0; i < c1.items; i++)
    {
        net += bill_body(c1.it[i].qty, c1.it[i].price, c1.it[i].items_name, total);
    }
    printf("\t-------------------------------------------------------------------------------\n");
    bill_footer(net);
    printf("\n\n");

    FILE * des;
    des = fopen("description.txt","r");
    fgets(str,100,des);
    retrstring = description(str,"{name}",c1.name);
    printf("%s\n\n",retrstring);
    printf("Do you want to save [y/n].\n");
    scanf("%c", &ch);
    if (ch == 'y')
    {
        FILE *ptr;
        ptr = fopen("Billing.txt", "a");
        fwrite(&c1, sizeof(billing), 1, ptr);
        fclose(ptr);
        printf("Saved Successfully !!.\n");
    }
}

void show()
{
    system("cls");
    printf("\n\n\t\t\t+++ +++ All Invoices +++ +++\n\n");
    billing c1;
    FILE *ptr;
    ptr = fopen("Billing.txt", "r");
    while (fread(&c1, sizeof(billing), 1, ptr))
    {
        float total = 0.0, net = 0.0;
        bill_header(c1.name, c1.date, c1.time, c1.invoice_number);
        for (int i = 0; i < c1.items; i++)
        {
            net += bill_body(c1.it[i].qty, c1.it[i].price, c1.it[i].items_name, total);
        }
        printf("\t-------------------------------------------------------------------------------\n");
        bill_footer(net);
    }
    fclose(ptr);
}

void search()
{
    system("cls");
    FILE *ptr;
    ptr = fopen("Billing.txt", "r");
    billing c1;
    int found = 0;
    char new_name[23];
    fflush(stdin);
    printf("Enter the name of customer please.\n");
    scanf("%[^\n]s", new_name);
    while (fread(&c1, sizeof(billing), 1, ptr))
    {
        if (strcmp(new_name, c1.name) == 0)
        {
            found = 1;
            float total = 0.0, net = 0.0;
            printf("\n\n\t\t$$$$$$ %s's Invoice $$$$$$\n\n");
            bill_header(c1.name, c1.date, c1.time, c1.invoice_number);
            for (int i = 0; i < c1.items; i++)
            {
                net += bill_body(c1.it[i].qty, c1.it[i].price, c1.it[i].items_name, total);
            }
            printf("\t-------------------------------------------------------------------------------\n");
            bill_footer(net);
        }
       
    }
    if(found == 0)
    {
        printf("%s's invoice is not exist in record.\n",new_name);
    }
    fclose(ptr);
}

void delete()
{
    system("cls");
    FILE *ptr,*tp;
    billing c1;
    int found = 0;
    char new_name[23];
    fflush(stdin);
    printf("Enter the name of customer.\n");
    scanf("%[^\n]s",new_name);
    ptr = fopen("Billing.txt", "r");
    tp = fopen("temp.txt","w");
    while(fread(&c1,sizeof(billing),1,ptr))
    {
        if(strcmp(new_name,c1.name) == 0)
        {
            found = 1;
        }
        else
        {
            fwrite(&c1,sizeof(billing),1,tp);
        }
    }
    fclose(ptr);
    fclose(tp);
    if(found == 1)
    {
        FILE * ptr,*tp;
        ptr = fopen("Billing.txt","w");
        tp = fopen("temp.txt","r");
        while(fread(&c1,sizeof(billing),1,tp))
        {
            fwrite(&c1,sizeof(billing),1,ptr);
        }
        fclose(ptr);
        fclose(tp);
        printf("%s's Invoice deleted Successfully !!\n",new_name);
    }
    else
    {
        printf("%s's is not exist in record.\n",new_name);
    }
}

void count_record()
{
    system("cls");
    FILE * ptr;
    int n;
    ptr = fopen("Billing.txt","r");
    fseek(ptr,0,SEEK_END);
    n = ftell(ptr)/sizeof(billing);
    rewind(ptr);
    fclose(ptr);
    printf("Total Invoices in record are %d.\n\n",n);
}

int main()
{
    
    char turns ='y';
    while (turns =='y')
    {
    
        system("cls");
        int choice;
        printf("\n\n\t\t_-_-_-_-_-_WELCOME TO MALIK'S super market_-_-_-_-_-_\n\n");
        printf("\t\t1.Creat Invoice.\n");
        printf("\t\t2.Show all Invoices.\n");
        printf("\t\t3.Search Invoice.\n");
        printf("\t\t4.Delete Invoice.\n");
        printf("\t\t5.Count all Invoices in record.\n");
        printf("\t\t6.Exit\n");
        printf("\n\n");
        printf("\t\tEnter your operation.");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            create();
            break;
        case 2:
            show();
            break;
        case 3:
            search();
            break;
        case 4:
            delete();
            break;
        case 5:
            count_record();
            break;
        case 6:
            exit(0);
        default:
            printf("Please enter correct operation.\n");
        }
        printf("Do you want to perform another operation [y/n]. ");
        scanf("%s",&turns);
    }

    printf("\n :) BYE !!\n");
    return 0;
}