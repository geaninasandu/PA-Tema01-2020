#include <bits/stdc++.h>

using namespace std;

struct Weight {
    int weight;
    int reps;

    Weight(int _weight, int _reps) : weight(_weight), reps(_reps) {}
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(find_max_growth());
    }

 private:
    int N, M;
    vector <Weight> weights;

    void read_input() {
        ifstream fin("sala.in");
        fin >> N >> M;
        for (int i = 0, weight, reps; i < N; i++) {
            fin >> weight >> reps;
            weights.push_back(Weight(weight, reps));
        }
        fin.close();
    }

    /**
     * Functia comparator folosita pentru a sorta crescator vectorul weights
     * dupa greutate
     */
    static bool compare_weights(Weight &a, Weight &b) {
        return a.weight > b.weight;
    }

    int find_max_growth() {
        /* Sortam vectorul crescator dupa weight */
        sort(weights.begin(), weights.end(), compare_weights);

        int min_weight = weights[0].weight;
        int total_reps = weights[0].reps;
        int max_growth = 0;

        /* Verificam primele M greutati din vectorul sortat */
        for (int i = 1; i < M; ++i) {
            /* Cautam valoarea minima a greutatii dintre acestea */
            if (weights[i].weight < min_weight)
                min_weight = weights[i].weight;

            /* Adaugam numarul repetitiilor pentru greutatea curenta la
             * numarul total */
            total_reps += weights[i].reps;

            /* Cautam valoarea maxima a produsului dintre greutatea minima si
             * numarul de repetitii */
            if (total_reps * min_weight > max_growth)
                max_growth = total_reps * min_weight;
        }

        /* Returnam valoarea maxima gasita */
        return max_growth;
    }

    void print_output(int result) {
        ofstream fout("sala.out");
        fout << result;
        fout.close();
    }
};

int main() {
    Task *task = new Task();
    task->solve();
    delete task;
    return 0;
}
