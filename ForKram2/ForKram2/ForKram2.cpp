
#include <iostream>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std; // Используем пространство имен std для упрощения кода

int factorial(int n) {
    int result = 1;
    for (int i = 1; i <= n; i++) {
        result *= i; // Вычисляем факториал числа n
    }
    return result;
}

void generate_permutations(vector<int> elements, int start, int end, ofstream& file) {
    // Задача 1: Генерируем все возможные перестановки алфавита
    if (start == end) {
        for (int i = 0; i <= end; i++) {
            file << elements[i] << " "; // Выводим элементы перестановки в файл
        }
        file << "\n";
    }
    else {
        for (int i = start; i <= end; i++) {
            swap(elements[start], elements[i]); // Меняем местами элементы для генерации перестановки
            generate_permutations(elements, start + 1, end, file);
            swap(elements[start], elements[i]); // Возвращаем элементы в исходное состояние
        }
    }
}

void generate_words(vector<int> alphabet, int length, int repeat_count_1, int repeat_count_2, ofstream& file) {
    // Задача 2: Генерируем все возможные слова длины 7 с одним символом, повторяющимся 3 раза, и одним символом, повторяющимся 2 раза
    vector<int> word(length);
    generate_words_recursive(alphabet, length, repeat_count_1, repeat_count_2, word, 0, file);
}

void generate_words_recursive(vector<int> alphabet, int length, int repeat_count_1, int repeat_count_2, vector<int>& word, int index, ofstream& file) {
    if (index == length) {
        int count_1 = 0;
        int count_2 = 0;
        for (int i = 0; i < length; i++) {
            if (word[i] == alphabet[0]) {
                count_1++; // Считаем количество повторений символа 1
            }
            else if (word[i] == alphabet[1]) {
                count_2++; // Считаем количество повторений символа 2
            }
        }
        if (count_1 == repeat_count_1 && count_2 == repeat_count_2) {
            for (int i = 0; i < length; i++) {
                file << word[i] << " "; // Выводим слово в файл
            }
            file << "\n";
        }
    }
    else {
        for (int i = 0; i < alphabet.size(); i++) {
            word[index] = alphabet[i]; // Выбираем символ для слова
            generate_words_recursive(alphabet, length, repeat_count_1, repeat_count_2, word, index + 1, file);
        }
    }
}

void generate_words_6(vector<int> alphabet, int length, int repeat_count, ofstream& file) {
    // Задача 3: Генерируем все возможные слова длины 6 с 3 символами, равными 2
    vector<int> word(length);
    generate_words_recursive_6(alphabet, length, repeat_count, word, 0, file);
}

void generate_words_recursive_6(vector<int> alphabet, int length, int repeat_count, vector<int>& word, int index, ofstream& file) {
    if (index == length) {
        int max_count = 0;
        for (int i = 0; i < alphabet.size(); i++) {
            int count = 0;
            for (int j = 0; j < length; j++) {
                if (word[j] == alphabet[i]) {
                    count++; // Считаем количество повторений символа
                }
            }
            if (count > max_count) {
                max_count = count; // Определяем максимальное количество повторений
            }
        }
        if (max_count == repeat_count) {
            for (int i = 0; i < length; i++) {
                file << word[i] << " "; // Выводим слово в файл
            }
            file << "\n";
        }
    }
    else {
        for (int i = 0; i < alphabet.size(); i++) {
            word[index] = alphabet[i]; // Выбираем символ для слова
            generate_words_recursive_6(alphabet, length, repeat_count, word, index + 1, file);
        }
    }
}


int main() {
    vector<int> alphabet = { 1, 2, 3, 4, 5, 6, 7, 8 }; // Алфавит для генерации слов

    ofstream file_permutations("размещения.txt"); // Файл для записи перестановок
    generate_permutations(alphabet, 0, alphabet.size() - 1, file_permutations);
    file_permutations << "Количество элементов: " << factorial(alphabet.size()) << "\n"; // Выводим количество перестановок
    file_permutations.close();

    ofstream file_words("words.txt"); // Файл для записи слов
    generate_words(alphabet, 7, 3, 2, file_words);
    file_words << "Количество слов: " << 7 * 6 * 5 * 4 * 3 * 2 * 1 << "\n"; // Выводим количество слов
    file_words.close();

    ofstream file_words_6("words_6.txt"); // Файл для записи слов длины 6
    generate_words_6(alphabet, 6, 2, file_words_6);
    file_words_6 << "Количество слов: " << 6 * 5 * 4 * 3 * 2 * 1 << "\n"; // Выводим количество слов
    file_words_6.close();

    return 0;
}
