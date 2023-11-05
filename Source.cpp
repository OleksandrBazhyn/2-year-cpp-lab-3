#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <vector>

using namespace std;

// �������� ��� ������� f
void f(char x, int i) {
    cout << "From set " << x << " have been done " << i << endl;
}

// ��������� ��� ��������� ���������� ��� ��
struct Action {
    char name;
    int index;
};

// ��������� ��� ��������� ���������� ��� ���� ��������� ����������
struct State {
    bool is_started;
    bool is_finished;
    mutex lock;
    condition_variable cv;
    vector<Action> actions;
};

// �������, ��� ������� ������ ��� ��������� ��
void launch_threads(State* state) {
    // ��������� nt ������
    for (int i = 0; i < state->actions.size(); i++) {
        thread t([state, i] {
            // �������� ��
            Action action = state->actions[i];

            // �������� ��
            f(action.name, action.index);

            // ����������� ��� ���������� 䳿
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
    // ����������� ��� ������ ����������
    cout << "Counting has been started." << endl;

    // �������� ������ ��, �� ������� ��������
    for (int i = 0; i < state->actions.size(); i++) {
        state->actions.push_back(Action{ 'a', i + 1 });
    }

    // ��������� ������ ��� ��������� ��
    launch_threads(state);

    // ������ �� ���������� ����������
    while (!state->is_finished) {
        unique_lock<mutex> lock(state->lock);

        // Wait for all threads to finish executing
        state->cv.wait(lock, [state] { return state->is_started && state->actions.size() == state->actions.size(); });
    }

    // ����������� ��� ���������� ����������
    cout << "Counting has been started." << endl;
}

int main() {
    // ���������� ���� ��������� ����������
    State state;
    state.is_started = false;
    state.is_finished = false;

    // ��������� ������ ��
    for (int i = 0; i < 6; i++) {
        state.actions.push_back(Action{ 'g', i + 1 });
    }

    // ��������� ����������
    compute(&state);

    return 0;
}
