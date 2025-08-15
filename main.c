#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct student
{
    int id;
    char name[50];
    char email[80];
    char course[30];
    int year;
    char phone[15];
    float marks;
};

void add_student();
void display_students();
void search_student();
void update_student();
void delete_student();

int main()
{
    int choice;
    
    printf("\n========================================\n");
    printf("   Student Record Management System\n");
    printf("========================================\n");
    
    while(1)
    {
        printf("\n1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);
        
        switch(choice)
        {
            case 1: add_student(); break;
            case 2: display_students(); break;
            case 3: search_student(); break;
            case 4: update_student(); break;
            case 5: delete_student(); break;
            case 6: printf("\nThanks for using!\n"); exit(0);
            default: printf("\nWrong choice! Try again.\n");
        }
    }
    return 0;
}

void add_student()
{
    struct student s;
    FILE *fp;
    
    fp = fopen("students.txt","a");
    if(fp==NULL)
    {
        printf("\nError opening file!\n");
        return;
    }
    
    printf("\nEnter student details:\n");
    printf("ID: ");
    scanf("%d",&s.id);
    printf("Name: ");
    scanf("%s",s.name);
    printf("Email: ");
    scanf("%s",s.email);
    printf("Course: ");
    scanf("%s",s.course);
    printf("Year: ");
    scanf("%d",&s.year);
    printf("Phone: ");
    scanf("%s",s.phone);
    printf("Marks: ");
    scanf("%f",&s.marks);
    
    fprintf(fp,"%d %s %s %s %d %s %.2f\n",s.id,s.name,s.email,s.course,s.year,s.phone,s.marks);
    fclose(fp);
    
    printf("\nStudent added successfully!\n");
}

void display_students()
{
    struct student s;
    FILE *fp;
    int found = 0;
    
    fp = fopen("students.txt","r");
    if(fp==NULL)
    {
        printf("\nNo records found!\n");
        return;
    }
    
    printf("\n=== All Students ===\n");
    printf("ID\tName\t\tEmail\t\t\tCourse\t\tYear\tPhone\t\tMarks\n");
    printf("---------------------------------------------------------------------------------\n");
    
    while(fscanf(fp,"%d %s %s %s %d %s %f",&s.id,s.name,s.email,s.course,&s.year,s.phone,&s.marks)!=EOF)
    {
        printf("%d\t%s\t\t%s\t\t%s\t\t%d\t%s\t\t%.2f\n",s.id,s.name,s.email,s.course,s.year,s.phone,s.marks);
        found = 1;
    }
    
    if(!found)
        printf("No student records found!\n");
    
    fclose(fp);
}

void search_student()
{
    struct student s;
    FILE *fp;
    int search_id, found = 0;
    
    fp = fopen("students.txt","r");
    if(fp==NULL)
    {
        printf("\nNo records found!\n");
        return;
    }
    
    printf("\nEnter student ID to search: ");
    scanf("%d",&search_id);
    
    while(fscanf(fp,"%d %s %s %s %d %s %f",&s.id,s.name,s.email,s.course,&s.year,s.phone,&s.marks)!=EOF)
    {
        if(s.id == search_id)
        {
            printf("\nStudent found!\n");
            printf("ID: %d\n",s.id);
            printf("Name: %s\n",s.name);
            printf("Email: %s\n",s.email);
            printf("Course: %s\n",s.course);
            printf("Year: %d\n",s.year);
            printf("Phone: %s\n",s.phone);
            printf("Marks: %.2f\n",s.marks);
            found = 1;
            break;
        }
    }
    
    if(!found)
        printf("\nStudent with ID %d not found!\n",search_id);
    
    fclose(fp);
}

void update_student()
{
    struct student s;
    FILE *fp, *temp;
    int update_id, found = 0;
    
    fp = fopen("students.txt","r");
    temp = fopen("temp.txt","w");
    
    if(fp==NULL)
    {
        printf("\nNo records found!\n");
        return;
    }
    
    printf("\nEnter student ID to update: ");
    scanf("%d",&update_id);
    
    while(fscanf(fp,"%d %s %s %s %d %s %f",&s.id,s.name,s.email,s.course,&s.year,s.phone,&s.marks)!=EOF)
    {
        if(s.id == update_id)
        {
            printf("\nEnter new details:\n");
            printf("Name: ");
            scanf("%s",s.name);
            printf("Email: ");
            scanf("%s",s.email);
            printf("Course: ");
            scanf("%s",s.course);
            printf("Year: ");
            scanf("%d",&s.year);
            printf("Phone: ");
            scanf("%s",s.phone);
            printf("Marks: ");
            scanf("%f",&s.marks);
            found = 1;
        }
        fprintf(temp,"%d %s %s %s %d %s %.2f\n",s.id,s.name,s.email,s.course,s.year,s.phone,s.marks);
    }
    
    fclose(fp);
    fclose(temp);
    
    remove("students.txt");
    rename("temp.txt","students.txt");
    
    if(found)
        printf("\nStudent updated successfully!\n");
    else
        printf("\nStudent with ID %d not found!\n",update_id);
}

void delete_student()
{
    struct student s;
    FILE *fp, *temp;
    int delete_id, found = 0;
    
    fp = fopen("students.txt","r");
    temp = fopen("temp.txt","w");
    
    if(fp==NULL)
    {
        printf("\nNo records found!\n");
        return;
    }
    
    printf("\nEnter student ID to delete: ");
    scanf("%d",&delete_id);
    
    while(fscanf(fp,"%d %s %s %s %d %s %f",&s.id,s.name,s.email,s.course,&s.year,s.phone,&s.marks)!=EOF)
    {
        if(s.id == delete_id)
        {
            found = 1;
            continue; // skip writing this record
        }
        fprintf(temp,"%d %s %s %s %d %s %.2f\n",s.id,s.name,s.email,s.course,s.year,s.phone,s.marks);
    }
    
    fclose(fp);
    fclose(temp);
    
    remove("students.txt");
    rename("temp.txt","students.txt");
    
    if(found)
        printf("\nStudent deleted successfully!\n");
    else
        printf("\nStudent with ID %d not found!\n",delete_id);
}

