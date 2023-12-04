#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#define MAX_CDS 100
struct CD{
    int id;
    char name[50];
    float duration;
    char content[100];
    bool status;
};
int cdCount = 0;
void printCDList(struct CD cdList[], int size){
    printf("Danh sach CD:\n");
    for (int i = 0; i < size; ++i) {
        printf("%d. %s - %.2f minutes - %s - %s\n", cdList[i].id, cdList[i].name, cdList[i].duration, cdList[i].content, cdList[i].status ? "Available" : "Not Available");
    }
}

void addNewCD(struct CD cdList[], int *size){
    struct CD newCD;
    printf("Nhap ten dia CD: ");
    scanf(" %[^\n]", newCD.name);
    printf("Nhap truong do CD: ");
    scanf(" %[^\n]", newCD.duration);
    printf("Nhap noi dung dia CD: ");
    scanf(" %[^\n]", newCD.content);
    cdList[cdCount++] = newCD;
    printf("dia CD da duoc them vao.\n");
}

void updateCD(struct CD cdList[], int size){
    char searchName[50];
    printf("Nhap ten dia CD muon chinh sua: ");
    scanf(" %[^\n]", searchName);
    int foundIndex = -1;
    for (int i = 0; i < cdCount; i++){
        if (strcmp(cdList[i].name, searchName) == 0){
            foundIndex = i;
            break;
        }
    }
    if (foundIndex != -1){
        printf("Nhap thong tin moi cho dia CD:\n");
        printf("Nhap ten dia CD: ");
        scanf(" %[^\n]", cdList[foundIndex].name);
        printf("Nhap truong do CD: ");
    	scanf(" %[^\n]", cdList[foundIndex].duration);
        printf("Nhap noi dung dia CD: ");
        scanf(" %[^\n]", cdList[foundIndex].content);
        printf("Thong tin lien he duoc cap nhap.\n");
    } else{
        printf("khong tim thay dia CD.\n");
    }
}

void deleteCD(struct CD cdList[], int *size){
    char deleteName[50];
    printf("Nhap ten dia CD muon xoa: ");
    scanf(" %[^\n]", deleteName);
    int foundIndex = -1;
    for (int i = 0; i < cdCount; i++) {
        if (strcmp(cdList[i].name, deleteName) == 0){
            foundIndex = i;
            break;
        }
    }
    if(foundIndex != -1){
        for (int i = foundIndex; i < *size - 1; i++){
            cdList[i] = cdList[i + 1];
        }
        (*size)--;
        printf("Dia CD da duoc xoa.\n");
    } else {
        printf("Khong tim thay dia CD.\n");
    }
}

void insertionSort(struct CD cdList[], int cdCount) {
    for (int i = 1; i < cdCount; i++) {
        struct CD key = cdList[i];
        int j = i - 1;
        while (j >= 0 && strcmp(cdList[j].name, key.name) > 0) {
            cdList[j + 1] = cdList[j];
            j = j - 1;
        }
        cdList[j + 1] = key;
    }
    printf("Danh sach dia CD duoc sap xep.\n");
}

int binarySearch(struct CD cdList[], int size, char searchName[]){
    printf("Nhap ten dia CD can tim kiem: ");
    scanf(" %[^\n]", searchName);
    int left = 0, right = cdCount - 1;
    int foundIndex = -1;
    while (left <= right){
        int mid = (left + right) / 2;
        if (strcmp(cdList[mid].name, searchName) == 0){
            foundIndex = mid;
            break;
        } else if (strcmp(cdList[mid].name, searchName) < 0){
            left = mid + 1;
        }else{
            right = mid - 1;
        }
    }
    if(foundIndex != -1){
        printf("dia CD duoc tim thay: %s - %s\n", cdList[foundIndex].name, cdList[foundIndex].content);
    }else{
        printf("Khong tim thay dia CD.\n");
    }
}

void searchByStatus(struct CD cdList[], int size, bool searchStatus){
    char searchName[50];
    printf("nhap ten dia CD can tim kiem: ");
    scanf(" %[^\n]", searchName);
    int found = 0;
    for(int i = 0; i < cdCount; i++){
        if(strcmp(cdList[i].name, searchName) == 0){
            printf("%s - %s\n", cdList[i].name, cdList[i].content);
            found = 1;
            break;
        }
    }
    if(!found){
        printf("Khong tim thay dia CD.\n");
    }
}

int main(){
    struct CD cdList[MAX_CDS];
    int size = 2;
    struct CD cd1 = {1, "CD1", 30.5, "Content1", true};
    cdList[0] = cd1;
    struct CD cd2 = {2, "CD2", 25.0, "Content2", false};
    cdList[1] = cd2;
    int choice;
    do{
        printf("\n************************MENU**************************\n");
        printf("1. In toan bo danh sach CD\n");
        printf("2. Them moi CD\n");
        printf("3. Cap nhat thong tin CD\n");
        printf("4. Xoa CD\n");
        printf("5. Sap xep danh sach CD theo thoi luong\n");
        printf("6. Tim kiem CD theo ten\n");
        printf("7. Tim kiem CD theo status\n");
        printf("0. Thoat\n");
        printf("*******************************************************\n");
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &choice);
        switch (choice){
            case 1:
                printCDList(cdList, size);
                break;
            case 2:
                addNewCD(cdList, &size);
                break;
            case 3:
                updateCD(cdList, size);
                break;
            case 4:
                deleteCD(cdList, &size);
                break;
            case 5:
                insertionSort(cdList, size);
                printCDList(cdList, size);
                break;
            case 6: {
                char searchName[50];
                printf("Nhap ten CD can tim kiem: ");
                scanf("%s", searchName);
                int index = binarySearch(cdList, size, searchName);
                if (index != -1) {
                    printf("Tim thay CD:\n");
                    printf("%d. %s - %.2f minutes - %s - %s\n", cdList[index].id, cdList[index].name, cdList[index].duration, cdList[index].content, cdList[index].status ? "Available" : "Not Available");
                } else {
                    printf("Khong tim thay CD.\n");
                }
                break;
            }
            case 7:{
                bool searchStatus;
                printf("Nhap status (1: Available, 0: Not Available): ");
                scanf("%d", &searchStatus);
                searchByStatus(cdList, size, searchStatus);
                break;
            }
            case 0:
                printf("Thoat Chuong Trinh!\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long chon lai.\n");
        }
    } while (choice != 0);
    return 0;
}
