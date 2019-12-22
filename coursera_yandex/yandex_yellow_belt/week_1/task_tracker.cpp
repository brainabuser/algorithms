#include <iostream>

#include <map>

#include <vector>

#include <tuple>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
    NEW,          // новая
    IN_PROGRESS,  // в разработке
    TESTING,      // на тестировании
    DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
public:
    // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo &GetPersonTasksInfo(const string &person) const {
        return person_to_tasks.at(person);
    }

    // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string &person) {
        ++person_to_tasks[person][TaskStatus::NEW];
    }

    // Обновить статусы по данному количеству задач конкретного разработчика,
    // подробности см. ниже
    tuple<TasksInfo, TasksInfo> PerformPersonTasks(
            const string &person, int task_count) {
        TasksInfo new_tasks, old_tasks;
        if (person_to_tasks.count(person) == 0) {
            return tie(new_tasks, old_tasks);
        }
        int tasks_sum = 0;
        vector<TaskStatus> statuses = {TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING};
        for (const TaskStatus &status : statuses) {
            if (person_to_tasks.at(person).count(status) != 0) {
                tasks_sum += person_to_tasks.at(person).at(status);
            }
        }
        if (task_count > tasks_sum) {
            task_count = tasks_sum;
        }

        TasksInfo tasks = person_to_tasks.at(person);
        for (const TaskStatus &status : statuses) {
            switch (status) {
                case TaskStatus::NEW:
                    if (tasks.count(status) != 0 && tasks.at(status) != 0) {
                        if (tasks.at(status) > task_count) {
                            new_tasks[TaskStatus::IN_PROGRESS] = task_count;
                            tasks.at(status) -= task_count;
                            task_count = 0;
                            old_tasks[status] = tasks.at(status);
                        } else {
                            new_tasks[TaskStatus::IN_PROGRESS] = tasks.at(status);
                            task_count -= tasks.at(status);
                            tasks.erase(status);
                        }
                    } else {
                        tasks.erase(status);
                    }
                    break;
                case TaskStatus::IN_PROGRESS:
                    if (tasks.count(status) != 0 && tasks.at(status) != 0) {
                        if (tasks.at(status) > task_count) {
                            new_tasks[TaskStatus::TESTING] = task_count;
                            tasks.at(status) -= task_count;
                            task_count = 0;
                            old_tasks[status] = tasks.at(status);
                        } else {
                            new_tasks[TaskStatus::TESTING] = tasks.at(status);
                            task_count -= tasks.at(status);
                            tasks.erase(status);
                        }
                    } else {
                        tasks.erase(status);
                    }
                    break;
                case TaskStatus::TESTING:
                    if (tasks.count(status) != 0 && tasks.at(status) != 0) {
                        if (tasks.at(status) > task_count) {
                            new_tasks[TaskStatus::DONE] = task_count;
                            tasks.at(status) -= task_count;
                            task_count = 0;
                            old_tasks[status] = tasks.at(status);
                        } else {
                            new_tasks[TaskStatus::DONE] = tasks.at(status);
                            task_count -= tasks.at(status);
                            tasks.erase(status);
                        }
                    } else {
                        tasks.erase(status);
                    }
                    break;
                case TaskStatus::DONE:
                    break;
            }
        }
        person_to_tasks.at(person) = UpdatePersonToTasks(new_tasks, old_tasks, person_to_tasks.at(person));
        return tie(new_tasks, old_tasks);
    }

private:
    map<string, TasksInfo> person_to_tasks;

    TasksInfo UpdatePersonToTasks(const TasksInfo &new_tasks, const TasksInfo &old_tasks, TasksInfo &tasks) {
        for (const TaskStatus &status: {TaskStatus::NEW, TaskStatus::IN_PROGRESS, TaskStatus::TESTING}) {
            if (new_tasks.count(status) != 0 && old_tasks.count(status) != 0) {
                tasks[status] = new_tasks.at(status) + old_tasks.at(status);
            } else if (new_tasks.count(status) != 0) {
                tasks[status] = new_tasks.at(status);
            } else if (old_tasks.count(status) != 0) {
                tasks[status] = old_tasks.at(status);
            } else {
                tasks.erase(status);
            }
        }
        if (new_tasks.count(TaskStatus::DONE) != 0) {
            tasks[TaskStatus::DONE] += new_tasks.at(TaskStatus::DONE);
        }
        return tasks;
    }
};

void PrintTasksInfo(TasksInfo tasks_info) {
    cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
         ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
         ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
         ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
    return 0;
}
