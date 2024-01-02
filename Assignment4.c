#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAXSIZE 100

// Structure for Students Information
typedef struct StudentInfo *infoNode;
struct StudentInfo {
    int St_ID;  
    char firstName[50];
    char lastName[50];
    int age;
    char courseCode[10];
};

// Structure for Students Grade
typedef struct StudentGrade *gradeNode;
struct StudentGrade {
    int St_ID; 
    int course1;
    int course2;
    int course3;
    int course4;
    int total;
    float percentage;
};

typedef struct TreeNode *node;
//Structure for Tree Node
struct TreeNode {
	struct StudentInfo *StudentInfo;
	struct StudentGrade *StudentGrade;
	struct TreeNode *left;
	struct TreeNode *right;
};


node insertToTree(node t, infoNode info, gradeNode grade) {
    if (t == NULL) {
        struct TreeNode *newnode = malloc(sizeof(struct TreeNode));
        if (newnode == NULL) {
            printf("Out of space\n");
            exit(EXIT_FAILURE); // or handle the error in an appropriate way
        }

        newnode->StudentInfo = info;
        newnode->StudentGrade = grade;
        newnode->left = NULL;
        newnode->right = NULL;
        return newnode;
    } else {
        if (info->St_ID < t->StudentInfo->St_ID)
            t->left = insertToTree(t->left, info, grade);
        else
            t->right = insertToTree(t->right, info, grade);
        return t;
    }
}

bool doesStudentIdExists(infoNode infoArray[], int studentCount, int studentId) {
    for (int i = 0; i < studentCount; ++i) {
        if (infoArray[i]->St_ID == studentId) {
            return true; // Student ID already exists
        }
    }
    return false; // Student ID does not exist
}


void addStudentToInfoArray(infoNode infoArray[], int *studentCount) {
    if (*studentCount >= MAXSIZE) {
        printf("Error: Database is full. Cannot add more students.\n");
        return;
    }

    infoNode newStudent = malloc(sizeof(struct StudentInfo));

    // Prompt for student ID until a unique one is entered
    int studentId;
    do {
        printf("Enter student ID: ");
        if (scanf("%d", &studentId) != 1) {
            printf("Error: Invalid input for student ID.\n");
            while (getchar() != '\n'); // Clear input buffer
            return;
        }

        if (doesStudentIdExists(infoArray, *studentCount, studentId)) {
            printf("Error: Student with ID %d already exists. Please enter a unique ID.\n", studentId);
        } else {
            break; // Unique ID entered
        }
    } while (true);

    newStudent->St_ID = studentId;

    printf("Enter student's first name: ");
    scanf("%s", newStudent->firstName);

    printf("Enter student's last name: ");
    scanf("%s", newStudent->lastName);

    printf("Enter student's age: ");
    scanf("%d", &(newStudent->age));

    printf("Enter course code: ");
    scanf("%s", newStudent->courseCode);

    infoArray[*studentCount] = newStudent;
    (*studentCount)++;

    printf("Student has been successfully added.\n");
}
void markFunc(infoNode infoArray[], gradeNode gradeArray[], int *studentCount, int *gradeCount) {
    int studentId;
    printf("Enter student ID to add grades: ");
    if (scanf("%d", &studentId) != 1) {
        printf("Error: Invalid input for student ID.\n");
        while (getchar() != '\n'); // Clear input buffer
        return;
    }

    // Find the student with the given ID
    int index = -1;
    for (int i = 0; i < *studentCount; ++i) {
        if (infoArray[i]->St_ID == studentId) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Error: Student with ID %d not found.\n", studentId);
        return;
    }
    // Create a new grade node
    gradeNode newGrade = malloc(sizeof(struct StudentGrade));
	
	newGrade->St_ID = studentId;

    printf("Enter grades for student %d:\n", studentId);
    printf("Course 1: ");
    scanf("%d", &(newGrade->course1));

    printf("Course 2: ");
    scanf("%d", &(newGrade->course2));

    printf("Course 3: ");
    scanf("%d", &(newGrade->course3));

    printf("Course 4: ");
    scanf("%d", &(newGrade->course4));

    // Calculate total and percentage
    newGrade->total = newGrade->course1 + newGrade->course2 + newGrade->course3 + newGrade->course4;
    newGrade->percentage = (float)newGrade->total / 4.0;

    // Add the new grade to the gradeArray
    gradeArray[*gradeCount] = newGrade;
    (*gradeCount)++;

    printf("Grades have been successfully added for student %d.\n", studentId);
}


int insertionSort(infoNode infoArray[], int n, int *count_measure) {
    for (int i = 1; i < n; i++) {
        infoNode temp = infoArray[i];
        int j = i;

        while (j > 0 && infoArray[j - 1]->St_ID > temp->St_ID) {
            infoArray[j] = infoArray[j - 1];
            j--;

            (*count_measure)++; // Increment counter for each comparison
        }

        infoArray[j] = temp;
    }

    return *count_measure;
}

// Function to read and display student info
void readAndDisplayStudentInfo(infoNode infoArray[], int studentCount) {
    int studentId;
    printf("Enter student ID to read info: ");
    if (scanf("%d", &studentId) != 1) {
        printf("Error: Invalid input for student ID.\n");
        while (getchar() != '\n'); // Clear input buffer
        return;
    }

    // Search for the student directly
    int index;
    for (index = 0; index < studentCount; ++index) {
        if (infoArray[index]->St_ID == studentId) {
            break;
        }
    }

    if (index == studentCount) {
        printf("Error: Student with ID %d not found.\n", studentId);
        return;
    }

    // Display student info
    printf("Student ID: %d, Name: %s %s, Age: %d, Course Code: %s\n",
           infoArray[index]->St_ID, infoArray[index]->firstName, infoArray[index]->lastName,
           infoArray[index]->age, infoArray[index]->courseCode);
}

// Function to read and modify student grades
void studFunc(infoNode infoArray[], gradeNode gradeArray[], int studentCount) {
    int studentId;
    printf("Enter student ID to modify grades: ");
    if (scanf("%d", &studentId) != 1) {
        printf("Error: Invalid input for student ID.\n");
        while (getchar() != '\n'); // Clear input buffer
        return;
    }

    // Search for the student directly
    int index;
    for (index = 0; index < studentCount; ++index) {
        if (infoArray[index]->St_ID == studentId) {
            break;
        }
    }

    if (index == studentCount) {
        printf("Error: Student with ID %d not found.\n", studentId);
        return;
    }

    // Display current grades
    printf("Current grades for student %d: Course 1: %d, Course 2: %d, Course 3: %d, Course 4: %d\n",studentId, 
	gradeArray[index]->course1, gradeArray[index]->course2, gradeArray[index]->course3, gradeArray[index]->course4);

    // Prompt for modifications
    printf("Enter new grades for student %d:\n", studentId);
    printf("Course 1: ");
    scanf("%d", &(gradeArray[index]->course1));

    printf("Course 2: ");
    scanf("%d", &(gradeArray[index]->course2));

    printf("Course 3: ");
    scanf("%d", &(gradeArray[index]->course3));

    printf("Course 4: ");
    scanf("%d", &(gradeArray[index]->course4));

    // Recalculate total and percentage
    gradeArray[index]->total = gradeArray[index]->course1 + gradeArray[index]->course2
                               + gradeArray[index]->course3 + gradeArray[index]->course4;
    gradeArray[index]->percentage = (float)gradeArray[index]->total / 4.0;

    printf("Grades have been successfully modified for student %d.\n", studentId);
}


int quickSort(gradeNode gradeArray[], int low, int high, int *count_measure) {
    if (low < high) {
        int pivotIndex = (low + high) / 2;
        float pivot = gradeArray[pivotIndex]->percentage;

        int i = low;
        int j = high;

        while (i <= j) {
            while (gradeArray[i]->percentage > pivot) {
                i++;
                (*count_measure)++; // Increment counter for each comparison
            }

            while (gradeArray[j]->percentage < pivot) {
                j--;
                (*count_measure)++; // Increment counter for each comparison
            }

            if (i <= j) {
                gradeNode temp = gradeArray[i];
                gradeArray[i] = gradeArray[j];
                gradeArray[j] = temp;
                i++;
                j--;
            }
        }

        quickSort(gradeArray, low, j, count_measure);
        quickSort(gradeArray, i, high, count_measure);
    }

    return *count_measure;
}

// Function to print the contents of the BST
void printTree(node t) {
    if (t != NULL) {
        printTree(t->left);
        // Print student details
        printf("Student ID: %d, Name: %s %s, Age: %d, Course Code: %s\n",
               t->StudentInfo->St_ID, t->StudentInfo->firstName, t->StudentInfo->lastName,
               t->StudentInfo->age, t->StudentInfo->courseCode);
        printTree(t->right);
    }
}

struct TreeNode* searchInTree(node t, int studentId, int *count_measure) {
    if (t == NULL || t->StudentInfo->St_ID == studentId) {
        (*count_measure)++; // Increment counter for each comparison
        return t;
    }

    if (studentId < t->StudentInfo->St_ID) {
        (*count_measure)++; // Increment counter for each comparison
        return searchInTree(t->left, studentId, count_measure);
    }

    (*count_measure)++; // Increment counter for each comparison
    return searchInTree(t->right, studentId, count_measure);
}

void totalAndPercentage(infoNode infoArray[], gradeNode gradeArray[], int studentCount)
{

    int studentId;
    printf("Enter student ID to view total and percentage: ");
    if (scanf("%d", &studentId) != 1) {
        printf("Error: Invalid input for student ID.\n");
        while (getchar() != '\n'); // Clear input buffer
        return;
    }
	
    // Search for the student directly
    int index;
    for (index = 0; index < studentCount; ++index) {
        if (infoArray[index]->St_ID == studentId) {
            break;
        }
    }

    if (index == studentCount) {
        printf("Error: Student with ID %d not found.\n", studentId);
        return;
    }
	
	// Display total and percentage
    printf("Student ID: %d, Total: %d, Percentage: %.2f%%\n", studentId, gradeArray[index]->total, gradeArray[index]->percentage);
}


int main()
{
   infoNode *newInfo = NULL;
   int studentId, age;
   int option;
   char fName[50+1];
   char lName[50+1];
   char courseCode[10+1];
   int studentCount = 0;
   int gradeCount = 0;
   int count_measure = 0;
   node root = NULL;
   infoNode infoArray[MAXSIZE];
   gradeNode gradeArray[MAXSIZE];
   //Display Menu
   while(1) {

     printf("\n====================================================\n");
     printf("\n1) Add student into the database\n");
     printf("\n2) Read/Modify students grades\n");
     printf("\n3) Insert marks for students\n");
	 printf("\n4) Get total and percentage for student\n");
	 printf("\n5) Display student info sorted by id\n");
     printf("\n6) Display student percentage in decending order\n");
     printf("\n7) Search and view student details\n");
	 printf("\n8)   Quit program....\n");
     if (scanf("%d", &option) != 1) {
        printf("Error: Invalid input. Try again.\n");
        while (getchar() != '\n'); //clear input buffer 
        continue;
     }

     switch (option) {
      case 1:    //Add student
         addStudentToInfoArray(infoArray, &studentCount);
		 root = insertToTree(root, infoArray[studentCount - 1], gradeArray[studentCount - 1]);
         printf("Press any key to continue...");
         getchar();
         while (getchar() != '\n');
         break;
	
	  case 2:    // Read and modify students grades
	    printf("\n==========================\n");
	    printf("1) Read students info\n");
	    printf("2) Modify students grades\n");
	    int subOption;
	    if (scanf("%d", &subOption) != 1) {
	        printf("Error: Invalid input. Try again.\n");
	        while (getchar() != '\n'); // Clear input buffer
	        break;
	    }
	
	    switch (subOption) {
	        case 1:
	            readAndDisplayStudentInfo(infoArray, studentCount);
	            break;
	        case 2:
	            studFunc(infoArray, gradeArray, studentCount);
	            break;
	        default:
	            printf("Invalid sub-option. Please try again.\n");
	    }
	
	    printf("Press any key to continue...");
	    getchar();
	    while (getchar() != '\n');
	    break;

      case 3:    //Insert marks for students
        markFunc(infoArray, gradeArray, &studentCount, &gradeCount);
        printf("Press any key to continue...");
        getchar();
        while (getchar() != '\n');
        break;
		
	  case 4: //Get total and percentage
	    totalAndPercentage(infoArray, gradeArray, studentCount);
	    printf("Press any key to continue...");
        getchar();
        while (getchar() != '\n');
        break;	    	     

      case 5:    //Display student info sorted by id
		insertionSort(infoArray, studentCount, &count_measure);
        printf("Student info sorted by ID:\n");
        for (int i = 0; i < studentCount; i++) {
            printf("Student ID: %d, Name: %s %s\n", infoArray[i]->St_ID, infoArray[i]->firstName, infoArray[i]->lastName);
        }
        printf("Number of comparisons in insertion sort: %d\n", count_measure);
        count_measure = 0; // Reset counter for the next operation        
        printf("Press any key to continue...");
        getchar();
        while (getchar() != '\n');
        break;
                
	  	  
  	  case 6:    // Display student percentage in descending order
		quickSort(gradeArray, 0, gradeCount - 1, &count_measure);
	    printf("Student percentages in descending order:\n");
	    for (int i = 0; i < gradeCount; i++) {
	        printf("Student ID: %d, Percentage: %.2f%%\n", gradeArray[i]->St_ID, gradeArray[i]->percentage);
	    }
		printf("Number of comparisons in quick sort: %d\n", count_measure);
        count_measure = 0; // Reset counter for the next operation
	    printf("Press any key to continue...");
	    getchar();
	    while (getchar() != '\n');
	    break;
	  
	  case 7:    // Search and view student details
        printf("Enter student ID to search: ");
        int searchId;
        if (scanf("%d", &searchId) != 1) {
           printf("Error: Invalid input for student ID.\n");
           while (getchar() != '\n'); // Clear input buffer
           break;
        }

        struct TreeNode* foundNode = searchInTree(root, searchId, &count_measure);
        printf("Number of comparisons in BST search: %d\n", count_measure);
        count_measure = 0; // Reset counter for the next operation

        if (foundNode != NULL) {
           printf("Student found:\n");
           // Print student details
           printf("Student ID: %d, Name: %s %s, Age: %d, Course Code: %s\n",
           foundNode->StudentInfo->St_ID, foundNode->StudentInfo->firstName, foundNode->StudentInfo->lastName,
           foundNode->StudentInfo->age, foundNode->StudentInfo->courseCode);
        } else {
           printf("Student with ID %d not found.\n", searchId);
        }

        // Print the entire tree
        printf("\nBinary Search Tree Contents:\n");
        printTree(root);
	    
		printf("Press any key to continue...");
	    getchar();
	    while (getchar() != '\n');
    	break;

		
	  case 8: //Exit
          return(0);
          break;

      default:
          printf("Invalid Option. Please Try again.");
          while (getchar() != '\n');

      } //End of Switch
   } //End of While

return 0;
}

