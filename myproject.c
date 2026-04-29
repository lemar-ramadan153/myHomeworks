#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 1. تحديد حجم المخزن 
#define SIZE 10 

// 2. تعريف هيكل المخزن الدائري
typedef struct {
    char buffer[SIZE];
    int head;  // مؤشر القراءة
    int tail;  // مؤشر الكتابة
    int count; // عدد العناصر الحالية
} CircularBuffer;

// 3. دالة التهيئة (Initialization)
void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->tail = 0;
    cb->count = 0;
}

// 4. دالة التحقق من الامتلاء
bool isFull(CircularBuffer *cb) {
    return cb->count == SIZE;
}

// 5. دالة التحقق من الفراغ
bool isEmpty(CircularBuffer *cb) {
    return cb->count == 0;
}

// 6. دالة الكتابة في المخزن (Write)
void writeBuffer(CircularBuffer *cb, char data) {
    if (isFull(cb)) {
        printf("\n[Error] Buffer Overflow! Cannot write: %c\n", data);
        return;
    }
    cb->buffer[cb->tail] = data;
    cb->tail = (cb->tail + 1) % SIZE; // التحرك بشكل دائري
    cb->count++;
}

// 7. دالة القراءة من المخزن (Read)
char readBuffer(CircularBuffer *cb) {
    if (isEmpty(cb)) {
        printf("\n[Error] Buffer Underflow!\n");
        return '\0';
    }
    char data = cb->buffer[cb->head];
    cb->head = (cb->head + 1) % SIZE; // التحرك بشكل دائري
    cb->count--;
    return data;
}

int main() {
    CircularBuffer cb;
    init(&cb);

    char name[100];
    const char *suffix = "CE-ESY";

    // أ. أدخل اسمك باستخدام الإدخال القياسي
    printf("Enter your name: ");
    scanf("%99s", name);

    // ب. أضف السلسلة النصية "CE-ESY" إلى الاسم
    strcat(name, suffix);
    printf("Processing string: %s\n", name);
    printf("Buffer Size: %d\n", SIZE);
    printf("--------------------------\n");

    // ج. خزن الناتج داخل المخزن الدائري
    for (int i = 0; i < strlen(name); i++) {
        writeBuffer(&cb, name[i]);
    }

    // د. اقرأ البيانات مرة أخرى من المخزن واعرضها
    printf("Reading from buffer: ");
    while (!isEmpty(&cb)) {
        printf("%c", readBuffer(&cb));
    }

    // هـ. التأكد أن المخزن فارغ بعد ذلك
    if (isEmpty(&cb)) {
        printf("\n--------------------------\nBuffer is now empty.\n");
    }

    return 0;
}
