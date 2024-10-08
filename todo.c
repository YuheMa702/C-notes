#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <direct.h> // For _mkdir on Windows
#include <Windows.h>


#define MAX_CONTENT_SIZE 500
#define MAX_LINE_LENGTH 120
#define MAX_TASK_COUNT 20
#define ACTION_BUF_SIZE 10
/*
This todolist app should support CRUD options
*/

void create_todo_directory() {
    _mkdir("C:\\todolist");
}


typedef struct todo_header todo;
struct todo_header {
    int size; // size = len(centent)
    char content[MAX_CONTENT_SIZE];
    bool finished;
};

typedef struct todo_list_header app;
struct todo_list_header {
    int next; // next = # of tasks = idx of next task
    todo tasks[MAX_TASK_COUNT]; // tasks represented as a fixed-length array
};


void write_task(app* APP, int idx) {
    char buf[MAX_LINE_LENGTH] = "";
    int total_len = 0;
    int line_len = 0;
    strcpy(APP->tasks[idx].content, ""); // Clear content
    printf("Enter task description, type \"END\" in a new line to stop:\n");
    while(1) {
        if (fgets(buf, MAX_LINE_LENGTH, stdin) != NULL) {
            // Calc line length
            line_len = strlen(buf);
            total_len += line_len;
            if (total_len > MAX_CONTENT_SIZE) {
                total_len -= line_len;
                APP->tasks[idx].size = total_len;
                break; // Input exceeds total max length
            }
            if (strncmp(buf, "END", 3) == 0 && buf[3] == '\n') {
                total_len -= line_len;
                APP->tasks[idx].size = total_len;
                break;
            }

            // Add the line to the task description
            strncat(APP->tasks[idx].content, buf, line_len);
        }
    }
}

void set_status(app* APP, int idx, bool status) {
    APP->tasks[idx].finished = status;
}


bool tasks_full(int idx) {
    return idx >= MAX_TASK_COUNT;
}

void add_task(app* APP) {
    int idx = APP->next;
    if (tasks_full(idx)) {
        printf("Maximum number of tasks reached!\n");
        return;
    }
    write_task(APP, idx);
    set_status(APP, idx, false); // Set the status of new task
    (APP->next)++; // Update idx for next todo
}

bool task_exist(app* APP, int idx) {
    return 0 <= idx && idx < APP->next;
}


int get_idx(app* APP) {
    int idx;
    bool got_user_input = false;
    do {
        if (got_user_input) printf("Please reenter a valid idx: ");
        else printf("Please enter the index: ");
        scanf("%d", &idx); // Save the number to idx
        getchar(); // Clear buffer
        got_user_input = true;
    } while (!task_exist(APP, idx));
    return idx;
}


void update_task(app* APP) {
    int idx = get_idx(APP);
    write_task(APP, idx);
}   

void check_task(app* APP) {
    int idx = get_idx(APP);
    set_status(APP, idx, true);
}
void uncheck_task(app* APP) {
    int idx = get_idx(APP);
    set_status(APP, idx, false);
}

void delete_task(app* APP) {
    int idx = get_idx(APP);
    int next = APP->next;
    for (int i = idx; i < next - 1; i++) {
        // Leftshift the elems
        APP->tasks[i] = APP->tasks[i+1];
    }
    (APP->next)--; // Update the next's todo's idx in the todo arr
}

void display(app* APP) {
    printf("Your tasks:\n");
    if (APP->next == 0) printf("You currently have no task\n");
    for (int i = 0; i < APP->next; i++) {
        todo t = APP->tasks[i];
        printf("[%d]", i);
        if (t.finished) printf("(X): "); 
        else printf("( ): ");
        printf("%s", APP->tasks[i].content);
    }
}

void save_tasks(app* APP) {
    FILE *file = fopen("C:\\todolist\\todo.txt", "w");
    if (file == NULL) {
        printf("Error opening file for saving!\n");
        return;
    }
    fprintf(file, "%d\n", APP->next); // Save the number of tasks
    for (int i = 0; i < APP->next; i++) {
        fprintf(file, "%d\n", APP->tasks[i].finished); // Save the task status
        fprintf(file, "%d\n", APP->tasks[i].size); // Save the conetent length
        fprintf(file, "%s", APP->tasks[i].content); // Save the task content
    }
    fclose(file);
}

void load_tasks(app* APP) {
    FILE *file = fopen("C:\\todolist\\todo.txt", "r");
    char* buf = malloc(sizeof(char)*MAX_LINE_LENGTH);
    if (file == NULL) {
        printf("No saved tasks found.\n");
        return;
    }
    fscanf(file, "%d\n", &(APP->next)); // Load the number of tasks
    for (int i = 0; i < APP->next; i++) {
        todo t = {0, "", false}; // temp todo structure
        fscanf(file, "%d\n", &(t.finished)); // Load the task status
        fscanf(file, "%d\n", &(t.size)); // Load the content length
        int size = t.size;
        while (size > 0) {
            // Keep reading until reaching content length
            strcpy(buf, ""); // Clear buf
            fgets(buf, MAX_LINE_LENGTH, file); // Load the task content
            strncat(t.content, buf, MAX_LINE_LENGTH);
            size -= strlen(buf);
            // printf("buf is: %s, size=%d\n", buf, size);
        }
        // printf("%d. status=%d, size=%d, content=\n%s", i, t.finished, t.size, t.content);
        APP->tasks[i] = t; // Copy the data to task[i]
    }
    free(buf);
    fclose(file);
}



int main() {
    create_todo_directory();
    char action[ACTION_BUF_SIZE];
    app* APP = calloc(1, sizeof(app));
    load_tasks(APP);
    while(1) {
        system("cls");
        printf("Welcome to Yuhe's TODOLIST APP!\n");
        printf("Add(a) Edit(e) Delete(d) Check(c) Uncheck(u) Quit(q)\n\n");
        display(APP);
        printf("\nYour action:\n");
        fgets(action, ACTION_BUF_SIZE, stdin);

        switch (action[0])
        {
        case 'a':
            add_task(APP);
            break;
        case 'e':
            update_task(APP);
            break;
        case 'd':
            delete_task(APP);
            break;
        case 'm':
            check_task(APP);
            break;
        case 'u':
            uncheck_task(APP);
            break;
        case 'q':
            Sleep(800);
            printf("Saving your data...");
            Sleep(800);
            save_tasks(APP);
            printf("done!\n");
            free(APP);
            Sleep(600);
            return EXIT_SUCCESS;
        default:
            // Do nothing
            break;
        }
    }
    free(APP);
    return EXIT_SUCCESS;
}