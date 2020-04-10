#include <bits/stdc++.h>

using namespace std;

/**
 * Structura care retine coordonata de start si end a unei bucati de gard
 */
struct Plank {
    int start;
    int end;

    Plank(int _start, int _end) : start(_start), end(_end) {}
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(count_redundant_planks());
    }

 private:
    int N;
    vector <Plank> planks;

    void read_input() {
        ifstream fin("gard.in");
        fin >> N;
        for (int i = 0, start, end; i < N; i++) {
            fin >> start >> end;
            planks.push_back(Plank(start, end));
        }
        fin.close();
    }

    /**
     * Functie comparator folosita pentru a sorta vectorul de placi crescator
     * dupa campul start; daca cele doua structuri au campul start egal, le
     * sorteaza descrescator dupa campul end
     * @return      true daca a trebuie sa fie inaintea lui b in vectorul
     * sortat; altfel false
     */
    static bool compare_starts(Plank &a, Plank &b) {
        if (a.start == b.start)
            return a.end > b.end;

        return a.start < b.start;
    }

    /**
     * Numara cate placi sunt redundante, folosind Greedy
     * @return      numarul de placi redundante
     */
    int count_redundant_planks() {
        int redundant_planks = 0;

        /* Sortam vectorul de placi crescator dupa campul start */
        sort(planks.begin(), planks.end(), compare_starts);

        /* Retinem ultima placa neredundanta pe care o gasim in vector (in
         * cazul de fata, o setam ca fiind chiar prima placa) */
        Plank last_good_plank = Plank(planks[0].start, planks[0].end);

        /* Parcurgem vectorul si verificam daca gasim placi redundante */
        for (int i = 1; i < N; ++i) {
            /* Daca coordonata end a placii gasite este mai mare decat
             * coordonata end a ultimei placi neredundante, placa curenta nu
             * e inclusa in placa cea initiala, deci e la randul ei
             * neredundanta; updatam asadar variabila last_good_plank */
            /* In caz contrar, crestem numarul de placi redundante */
            if (planks[i].end > last_good_plank.end)
                last_good_plank = planks[i];
            else
                redundant_planks++;
        }

        return redundant_planks;
    }

    void print_output(int result) {
        ofstream fout("gard.out");
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

