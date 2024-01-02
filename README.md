# StudentDatabaseManagementSystem

Fourth assignment for Data Structures and Algorithms in C.

December 01, 2023

**1. Overview:**
   - The C assignment is a Student Database Management System that employs a combination of arrays and a binary search tree (BST) to manage student information and grades.
   - It provides functionalities such as adding students, reading/modifying student grades, inserting marks, viewing total and percentage, displaying sorted student info, and displaying student percentage in descending order.

**2. Key Features:**

   - **Structures:**
     - Defines structures for `StudentInfo` and `StudentGrade` to store student information and grades, respectively.
     - Structures are named `StudentInfo` and `StudentGrade`.

   - **Binary Search Tree (BST):**
     - Utilizes a binary search tree for efficient searching and retrieval of student information.
     - Tree nodes are structured to contain both student information and grades.
     - Structure for BST node is named `TreeNode`.

   - **Arrays:**
     - Maintains arrays for storing student information (`infoArray`) and grades (`gradeArray`).
     - Allows for efficient operations like insertion sort and quicksort.

   - **Menu-Driven Interface:**
     - Provides a user-friendly menu for selecting various operations.
     - Allows users to interact with the program through console input.

   - **Dynamic Memory Allocation:**
     - Allocates memory dynamically for new students during insertion operations.
     - Ensures proper memory deallocation during program termination.

   - **Student ID Validation:**
     - Ensures uniqueness of student IDs, prompting users until a unique ID is entered.

   - **Database Limits:**
     - Imposes a maximum limit (`MAXSIZE`) on the number of students that can be added to the database.

   - **Sorting Algorithms:**
     - Implements insertion sort to display student information sorted by ID.
     - Implements quicksort to display student percentages in descending order.

   - **Search Operations:**
     - Performs searches in both arrays and BST to find and display student details efficiently.
     - Counts and displays the number of comparisons made during search operations.

**3. Usage:**
   - Users can add students, read/modify grades, insert marks, view total and percentage, and perform sorting and searching operations through the menu.

**4. Input Validation:**
   - Ensures that only valid numerical and string inputs are accepted.
   - Provides appropriate feedback for incorrect input types.

**5. Error Handling:**
   - Handles scenarios such as a full database, invalid inputs, and non-existent student IDs gracefully.
   - Prompts users with appropriate messages for better interaction.

**6. Continuous Execution:**
   - The program runs continuously until the user chooses to exit, allowing multiple operations in a single run.

**7. Conclusion:**
   - The assignment serves as a basic Student Database Management System, combining array-based and BST-based data structures.
   - It provides fundamental functionalities for managing student information and grades with efficient search and sorting operations.
