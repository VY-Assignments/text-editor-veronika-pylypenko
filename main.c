#include<stdio.h>
#include<inttypes.h>
#include<stdlib.h>
#include<string.h>
#define MAX_HISTORY 3

typedef struct {
    char* text_lines[100];
    size_t row_count;
    size_t capacity;
}HistoryState;
HistoryState history[MAX_HISTORY];
int history_ind = -1;
int history_count = 0;
char* global_buffer = NULL;
void text_printing(char** text, size_t row) //просто виводжу текст користувача
{
    if (text == NULL || row == 0) {
        printf("Your text is empty.\n");
        return; }

    for (size_t i = 0; i < row; i++) {
        if (text[i] != NULL) {
            printf("Your current text: %s\n", text[i]);
        }
    }
}
//ф-ця для case1
void append_text(char*** text, size_t* capacity,size_t current_row, const char* buffer) {
    size_t len = strlen(buffer);
    if (current_row >= *capacity) {
        size_t old_capacity = *capacity;
        if (*capacity == 0) { *capacity = 2; }
        else { *capacity *= 2; }

        char** temp = realloc(*text, (*capacity) * sizeof(char*));

        if (temp == NULL) {
            printf("Memory extension failed!\n");
            return;
        }
        *text = temp;
        for (size_t i = old_capacity; i < *capacity; i++)//занулює нові комірки, в яких поки що лежить сміття 
        {
            (*text)[i] = NULL;
        }
    }

    if ((*text)[current_row] == NULL || strlen((*text)[current_row])==0)
    {
        (*text)[current_row] = malloc(len + 1);
        if ((*text)[current_row] == NULL) {
            printf("Malloc failed!\n");
            return;
        }
        strcpy_s((*text)[current_row], len + 1, buffer);
    }
        else {
        //текст є - додаю в кінець
        size_t old_len = strlen((*text)[current_row]);
        char* temp_line = realloc((*text)[current_row], old_len + len + 1);
        if (temp_line == NULL) {
            printf("Realloc failed;(\n");return;
        }
        (*text)[current_row] = temp_line;
        strcat_s((*text)[current_row], old_len + len + 1, buffer);
        }
}
//for case2
void add_line(char*** text, size_t* capacity, size_t* current_row) {
    printf("New line is started.\n ");
    (*current_row)++;
    if (*current_row >= *capacity)
    {
        size_t old_capacity = *capacity;
        if (*capacity == 0) { *capacity = 2; }
        else { *capacity *= 2; }
        char** temp = realloc(*text, (*capacity) * sizeof(char*));
        if (!temp) {
            printf("Memory extension failed!\n");
            (*current_row)--;
            return;
        }
        *text = temp;
        // printf("%p\n", (void*)text); - для перевірки чи створилась комірка

        for (size_t i = old_capacity; i < *capacity; i++)//занулює нові комірки, в яких поки що лежить сміття 
        {
            (*text)[i] = NULL;
        }
    }
    (*text)[*current_row] = (char*)malloc(1);
    if ((*text)[*current_row] != NULL) {
        (*text)[*current_row][0] = '\0';
        printf("New line is started succesfully.\n ");
    }
    else {
        printf("emory extension failed!\n");
        (*current_row)--;
    }
}
//for case 3
void save_file(char** text, size_t row_count)
{
    if (text == NULL || row_count == 0) {
        printf("Your file is empty!\n"); return;
    }
    char filename[256];
    printf("Enter the file name for saving: ");
    getchar();
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        printf("Error filename reading!\n"); return; }
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }
    FILE* file;
    if (fopen_s(&file, filename, "w") != 0 || file == NULL) {
        printf("Some problems with file writinh appeared!\n"); return;
    }
    for (size_t i = 0; i < row_count; i++) {
        if (text[i] != NULL) { fprintf(file, "%s\n", text[i]); }//fprintf - ф-ція для запису у файл
    }

        fclose(file);
        printf("Text has been saved successfully\n");
}
//for case 3
void load_file(char*** text, size_t* capacity, size_t* current_row) {
    char filename[256];
    printf("Enter the file name for loading: ");
    getchar();
    if (fgets(filename, sizeof(filename), stdin) == NULL) {
        printf("Error filename reading!\n"); return;
    }
    size_t len = strlen(filename);
    if (len > 0 && filename[len - 1] == '\n') {
        filename[len - 1] = '\0';
    }
    FILE* file = NULL;
    if (fopen_s(&file, filename, "r") != 0 || file == NULL) {
        printf("Probably your file doesn`t exist!\n"); return;
    }
    if (*text != NULL) {
        for (size_t i = 0; i < *capacity; i++) {
            if ((*text)[i] != NULL) { free((*text)[i]); }
        }
    }
    free(*text);
    //Скидаю менеджер пам'яті
    *text = NULL;
    *capacity = 0;
    *current_row = 0;
    char buffer[256];
    size_t is_new_line = 1;
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        size_t b_len = strlen(buffer);
        int end_with_newline = 0;
        if (b_len > 0 && buffer[b_len - 1] == '\n') {

            buffer[b_len - 1] = '\0';
            end_with_newline = 1;
        }
        if (!is_new_line == 0) {
            append_text(text, capacity, *current_row, buffer);
        }
        else {
            if (*capacity == 0 || (*text)[*current_row] != NULL) {
                if (*capacity != 0) { (*current_row)++; }
                append_text(text, capacity, *current_row, buffer);
            }
            is_new_line = end_with_newline;
        }
    }
        fclose(file);
        if (*text == NULL) {
            *capacity = 2;
            *text = calloc(*capacity, sizeof(char*));
            if (*text != NULL) {
                (*text)[0] = malloc(1);
                if ((*text)[0] != NULL) {
                    (*text)[0][0] = '\0';
                }

            }
        }
        printf("Text has been loaded successfully");
}

    
   // (*text)[*current_row] = NULL;

    //for case 6
void find_str(char** text, size_t row_count, const char* target_str) {
    if (text == NULL || row_count == 0 || target_str == NULL || strlen(target_str) == 0) {
        printf("You enter nothing or there is no text!"); return;
    }
    size_t target_len = strlen(target_str);
    int found_signal = 0;
    for (size_t i = 0; i < row_count; i++) {
        if (text[i] == NULL) {
            continue;
        }

        size_t line_len = strlen(text[i]);
        if (line_len < target_len) continue;
        for (size_t text_ind = 0; text_ind <= line_len - target_len; text_ind++) {
            int match = 1;
            for (size_t sub_ind = 0; sub_ind < target_len; sub_ind++) {
                if (text[i][text_ind + sub_ind] != target_str[sub_ind]) {
                    match = 0;
                    break;
                }
            }
            if (match == 1) {
                printf("The text is in this position: %zu %zu\n", i, text_ind);
                found_signal++;
            }

            if (found_signal==0) {
                printf("Search string was not found!");
            }
        }
    }

    }
    //for case 5
    void insert_text(char** text, size_t row_count, size_t target_row, size_t target_col, const char* buffer) {
        if (text == NULL || target_row >= row_count || text[target_row] == NULL) {
            printf("Your target line doesn`t exist");
            return;
        }
        size_t old_len = strlen(text[target_row]);
        size_t insert_len = strlen(buffer);
        if (target_col > old_len) {
            target_col = old_len;
        }
        char* temp = realloc(text[target_row], old_len + insert_len + 1);
        if (temp == NULL) {
            printf("Realloc failed");
            return;
        }
        text[target_row] = temp;
        memmove(text[target_row] + target_col + insert_len, text[target_row] + target_col, old_len - target_col + 1);
        memcpy(text[target_row] + target_col, buffer, insert_len);
        printf("Text inserted succesfully!\n");
        return;
    }
    //Assignment 2
    void delete_symbols(char** text, size_t row_count, size_t target_row, size_t target_column, size_t count) {
        if (text == NULL || target_row >= row_count || text[target_row] == NULL) {
            printf("Your target line doesn`t exist\n");
            return;
        }
        size_t len = strlen(text[target_row]);
        if (target_column >= len) {
            printf("Target index is out of range!\n");
            return;
        }
        if (target_column + count >= len) {
            count = len - target_column;
        }
        memmove(text[target_row] + target_column, text[target_row] + target_column + count, len - target_column - count + 1);
        printf("Symbols deleted succesfully!\n");
        return;
    }
    void free_history_state(int ind) {
        if (ind >= 0 && ind < MAX_HISTORY) {
            for (size_t i = 0; i <history[ind].capacity; i++)
            {
                if (history[ind].text_lines[i] != NULL) {
                   free(history[ind].text_lines[i]);
                   history[ind].text_lines[i] = NULL;
                }
            }
        }
    }
   
    void save_to_history(char** text, size_t row_count, size_t capacity) {
        for (int i = history_ind + 1; i < history_count; i++)
        {
            free_history_state(i);
        }
        history_count = history_ind + 1;
            if (history_count>=MAX_HISTORY) {
                free_history_state(0);
                for (int i = 1; i < MAX_HISTORY;i++) {
                    history[i - 1] = history[i];
               }
                history_ind--;
                history_count--;
            }
            history_ind++;
            history_count++;
            history[history_ind].row_count = row_count;
            history[history_ind].capacity = capacity;

            for (size_t i = 0; i < capacity; i++)
            {
                if (text != NULL && text[i]!=NULL) {
                    size_t len = strlen(text[i]);
                    history[history_ind].text_lines[i] = malloc(len + 1);
                    if (history[history_ind].text_lines[i] != NULL) {
                        strcpy_s(history[history_ind].text_lines[i], len + 1, text[i]);
                    }
                    else {
                        history[history_ind].text_lines[i] = NULL;
                    }
                }
            }
    }
    void undo(char*** text, size_t* capacity, size_t* current_row) {
        if (history_ind <= 0) {
            printf("Nothing to undo!\n"); return;
        }
        if (*text != NULL) {
            for (size_t i = 0; i < *capacity; i++)
            {
                if ((*text)[i] != NULL) { free((*text)[i]); }
            }
            free(*text);
        }
        history_ind--;
        HistoryState state = history[history_ind];
        *capacity = state.capacity;
        *current_row = (state.row_count > 0) ? state.row_count - 1 : 0;
        *text = malloc((*capacity) * sizeof(char*));
        for (size_t i = 0; i < *capacity; i++)
        {
            if (state.text_lines[i] != NULL) {
                size_t len = strlen(state.text_lines[i]);
                (*text)[i] = malloc(len + 1);
                if ((*text)[i] != NULL) { strcpy_s((*text)[i], len + 1, state.text_lines[i]);
                }
                else {
                    (*text)[i] = NULL;
                }
            }
        }
        printf("Undo successful completed.\n");
    }
    void redo(char*** text, size_t* capacity, size_t* current_row) {
        if (history_ind >= history_count-1) {
            printf("Nothing to redo!\n"); return; 
        }
        if (*text != NULL) {
            for (size_t i = 0; i < *capacity; i++)
            {
                if ((*text)[i] != NULL) { free((*text)[i]); }
            }
            free(*text);
        }
        history_ind++;
        HistoryState state = history[history_ind];
        *capacity = state.capacity;
        *current_row = (state.row_count > 0) ? state.row_count - 1 : 0;
        *text = malloc((*capacity) * sizeof(char*));
        for (size_t i = 0; i < *capacity; i++)
        {
            if (state.text_lines[i] != NULL) {
                size_t len = strlen(state.text_lines[i]);
                (*text)[i] = malloc(len + 1);
                if ((*text)[i] != NULL) {
                    strcpy_s((*text)[i], len + 1, state.text_lines[i]);
                }
                else {
                    (*text)[i] = NULL;
                }
            }
        }
        printf("Redo completed successfully.\n");
    }
    void copy_text(char** text, size_t row_count, size_t target_row, size_t target_column, size_t count) {
        if (text == NULL || target_row >= row_count || text[target_row] == NULL) {
            printf("Your target line doesn`t exist\n");
            return;
        }
        size_t len = strlen(text[target_row]);
        if (target_column >= len) {
            printf("Target index is out of range!\n");
            return;
        }
        if (target_column + count >len) {
            count = len - target_column;
        }
        if (global_buffer!=NULL) {
            free(global_buffer);
        }
        global_buffer = (char*)malloc(count + 1);
        if (global_buffer == NULL) {
            printf("Clipboard memory allocation failed.\n");
            return;
        }
        memmove(global_buffer, text[target_row] + target_column + count, count);
        global_buffer[count] = '\0';
        printf("Copied to clipboard: \"%s\"\n", global_buffer);
        return;
    }
    void cut_text(char** text, size_t row_count, size_t target_row, size_t target_column, size_t count) {
        if (text == NULL || target_row >= row_count || text[target_row] == NULL) {
            printf("Your target line doesn`t exist\n");
            return;
        }
        copy_text(text, row_count, target_row, target_column, count);
        if (global_buffer != NULL && strlen(global_buffer) > 0) {
            delete_symbols(text, row_count, target_column, target_column, count);
            printf("Text cut succesfully!\n");
        }
    }
    void paste_text(char** text, size_t row_count, size_t target_row, size_t target_column, size_t count) {
        if (global_buffer == NULL || target_row >= row_count || text[target_row] == NULL) {
            printf("Your target line doesn`t exist\n");
            return;
        }
        copy_text(text, row_count, target_row, target_column, count);
        if (global_buffer != NULL && strlen(global_buffer) > 0) {
            delete_symbols(text, row_count, target_column, target_column, count);
            printf("Clipboard is empty!\n");
        }
        insert_text(text, row_count, target_row, target_column, global_buffer);
    }
    void insert_with_replacement(char** text, size_t row_count, size_t target_row, size_t target_column, const char* buffer) {
        if (text == NULL || target_row >= row_count || text[target_row] == NULL) {
            printf("Your target line doesn`t exist\n");
            return;
        }
        size_t old_len = strlen(text[target_row]);
        size_t insert_len = strlen(buffer);
        if (target_column > old_len) {
            target_column = old_len;
        }
        if (target_column+insert_len > old_len) {
            char* temp = realloc(text[target_row], old_len + insert_len + 1);
            if (temp == NULL) {
                printf("Realloc failed");
                return;
            }
            text[target_row] = temp;
            text[target_row][target_column + insert_len] = '\0';
        }
        memcpy(text[target_row] + target_column, buffer, insert_len);
        printf("Text inserted with replacement succesfully!\n");
        return;
    }
    int main()
    {
        size_t current_row = 0;
        size_t column = 0;
        size_t capacity = 0;
        char** text = NULL;
        save_to_history(text, 0, capacity);
        while (1) // створила нескінчений цикл, щоб програма не завершувалась після першого введення
        {
            uint8_t choice;
            printf("Choose the command:\n");
            printf("1. Append text symbols to the end\n");
            printf("2. Start the new line\n");
            printf("3. Use files to load/save the information\n");
            printf("4. Print the current text to console\n");
            printf("5. Insert the text by line and symbol index\n");
            printf("6. Search (please note that the text can be found more than once)\n");
            printf("7. (Optional) Clearing the console\n");
            printf("8. Delete command\n");
            printf("9. Undo command\n");
            printf("10. Redo command\n");
            printf("11. Cut command\n");
            printf("12. Paste command\n");
            printf("13. Copy command\n");
            printf("14. Insert with replacement command\n");
            printf("0. Exit\n");
            scanf_s(" %hhu", &choice);// однобайтове ціле число
            switch (choice)
            {
                //fgets - зчитування цілих рядків із пробілами(до того як ентер натиснули)
                //scanf - зчитування окремих слів( до першого пробілу) або чисел(char,int, float)
            case 1: printf("Enter text to append: ");
                char buffer[256];
                //strcpy - ф-ція для копіювання рядків (посимвольно переносить у цільовий буфер)
                getchar(); //для того, щоб прибрати залишковий символ \n, щоб він не впливав на результат fgets (не пропустить введення)
                // ця ф-ція бере 1 символ із потоку stdin

                if (fgets(buffer, sizeof(buffer), stdin) != NULL)
                {
                    size_t len = strlen(buffer);
                    if (len > 0 && buffer[len - 1] == '\n') {
                        buffer[len - 1] = '\0';
                    }
                    else {
                        int c;
                        while ((c = getchar()) != '\n' && c != EOF);
                    }
                    save_to_history(text, current_row + 1, capacity);
                    append_text(&text, &capacity, current_row, buffer);
                }
                break;
            case 2:
                save_to_history(text, current_row + 1, capacity);
                add_line(&text, &capacity, &current_row);break;
            case 3:
                printf("Choose action: 1-Save, 2-Load: ");
                int file_op;
                scanf_s("%d", &file_op);
                if (file_op == 1) {
                    save_file(text, current_row + 1);
                }
                else if (file_op == 2) {
                    save_to_history(text, current_row + 1, capacity);
                    load_file(&text, &capacity, &current_row);
                }
                else {
                    printf("Unknown action\n");
                }
                break;
                //Use files to load/save the information
            case 4:
                text_printing(text, current_row + 1);break;
                break;
            case 5: {
                size_t t_row, t_col;
                char insert_buffer[256];
                printf("Choose line and index: ");
                scanf_s("%zu %zu", &t_row, &t_col);
                printf("enter to insert: ");
                getchar();
                if (fgets(insert_buffer, sizeof(insert_buffer), stdin) != NULL)
                {
                    size_t len = strlen(insert_buffer);
                    if (len > 0 && insert_buffer[len - 1] == '\n') {
                        insert_buffer[len - 1] = '\0';
                    }
                    save_to_history(text, current_row + 1, capacity);
                    insert_text(text, current_row + 1, t_row, t_col, insert_buffer);
                }
                break;
            }
            case 6:printf("Enter text to search: ");
                char search_buffer[256];
                getchar();
                if (fgets(search_buffer, sizeof(search_buffer), stdin) != NULL)
                {
                    size_t len = strlen(search_buffer);
                    if (len > 0 && search_buffer[len - 1] == '\n') {
                        search_buffer[len - 1] = '\0';
                    }
                    find_str(text, current_row + 1, search_buffer);
                }
                break;
                /* case 7:
     #ifdef _WIN32
                     system("cls");
     #else
                     system("clear");
     #endif
                     printf("Console cleared.\n");
                     break;*/
            case 8:
            {
                size_t row_d, column_d, count_d;
                printf("Choose line, index, number of symbols: ");

                if (scanf_s("%zu %zu %zu", &row_d, &column_d, &count_d) == 3) {
                    save_to_history(text, current_row + 1, capacity);
                    delete_symbols(text, current_row + 1, row_d, column_d, count_d);
                }
                else {
                    printf("Invalid input\n");
                }
                break;
            }
            case 0: printf("Exit");break;
            default: printf("Unknown command.\n");
            }
            if (choice == 0) { break; }
        }
        //тут звільняю пам'ять
        if (text != NULL) {
            for (size_t i = 0; i < capacity; i++)//занулює нові комірки, в яких поки що лежить сміття 
            {
                free(text[i]);
            }
            free(text);
        }
        for (int i = 0; i < history_count; i++)
        {
            free_history_state(i);
        }
        return 0;
    }
        
 
    