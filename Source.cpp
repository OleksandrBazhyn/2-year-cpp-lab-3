#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <vector>

using namespace std;

// Заглушка для функції f
void f(char x, int i) {
    cout << "From set " << x << " have been done " << i << endl;
}

// Структура для зберігання інформації про дію
struct Action {
    char name;
    int index;
};

// Структура для зберігання інформації про стан виконання обчислення
struct State {
    bool is_started;
    bool is_finished;
    mutex lock;
    condition_variable cv;
    vector<Action> actions;
};

// Функція, яка запускає потоки для виконання дій
void launch_threads(State* state) {
    // Запускаємо nt потоків
    for (int i = 0; i < state->actions.size(); i++) {
        thread t([state, i] {
            // Отримуємо дію
            Action action = state->actions[i];

            // Виконуємо дію
            f(action.name, action.index);

            // Повідомляємо про завершення дії
            lock_guard<mutex> lock(state->lock);
            state->is_finished = true;
            state->cv.notify_all();
            });

        // Set the is_started flag to true before starting the thread
        state->is_started = true;

        t.detach();
    }
}

void compute(State* state) {
    // Повідомляємо про запуск обчислення
    cout << "Counting has been started." << endl;

    // Отримуємо список дій, які потрібно виконати
    for (int i = 0; i < state->actions.size(); i++) {
        state->actions.push_back(Action{ 'a', i + 1 });
    }

    // Запускаємо потоки для виконання дій
    launch_threads(state);

    // Чекаємо на завершення обчислення
    while (!state->is_finished) {
        unique_lock<mutex> lock(state->lock);

        // Wait for all threads to finish executing
        state->cv.wait(lock, [state] { return state->is_started && state->actions.size() == state->actions.size(); });
    }

    // Повідомляємо про завершення обчислення
    cout << "Counting has been started." << endl;
}

int main() {
    // Ініціалізуємо стан виконання обчислення
    State state;
    state.is_started = false;
    state.is_finished = false;

    // Створюємо список дій
    for (int i = 0; i < 6; i++) {
        state.actions.push_back(Action{ 'g', i + 1 });
    }

    // Запускаємо обчислення
    compute(&state);

    return 0;
}
