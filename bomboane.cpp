#include <bits/stdc++.h>

using namespace std;

struct Problem {
    int min_solved;
    int max_solved;

    Problem(int _min_solved, int _max_solved) : min_solved(_min_solved),
                                                max_solved(_max_solved) {}
};

class Task {
 public:
    void solve() {
        read_input();
        print_output(share_candies());
    }

 private:
    int N, M, sum_max_solved = 0, sum_min_solved = 0;
    vector <Problem> problems;
    const int kMod = 1e9 + 7;

    void read_input() {
        ifstream fin("bomboane.in");
        fin >> N >> M;
        for (int i = 0, min_solved, max_solved; i < N; i++) {
            fin >> min_solved >> max_solved;
            problems.push_back(Problem(min_solved, max_solved));
            sum_max_solved += max_solved;
            sum_min_solved += min_solved;
        }
        fin.close();
    }

    /**
     * Calculeaza numarul de moduri prin care se pot impartii bomboanele,
     * adaugand intr-o matrice numarul de combinatii care se pot obtine la
     * fiecare pas pentru o suma de la 0 la numarul total de bomboane
     *
     * @return      ultimul element al matricei, care reprezinta numarul
     * total de moduri de a imparti bomboanele
     */
    int share_candies() {
        /* Daca numarul de bomboane este egal cu suma capetelor superioare
         * sau a capetelor inferioare ale intervalelor, se pot imparti
         * bomboane intr-un singur mod */
        if (sum_max_solved == M || sum_min_solved == M)
            return 1;

        /* Daca sunt prea putine sau prea multe bomboane, nu se pot imparti */
        if (sum_max_solved < M || sum_min_solved > M)
            return 0;

        /* Initializam o matrice de N * M elemente si o umplem cu 0;
         * In matrice vom retine numarul de combinatii care se pot obtine din
         * cele i intervale (i = 0..N - 1) pentru a atinge suma j (j = 0..M)*/
        long combinations_number;
        long dp[N + 1][M + 1];
        memset(dp, 0, sizeof(dp));

        /* Initializam elementele de la i = [min, max] de pe prima linie a
         * matricei cu 1, unde min = capatul inferior al primului interval,
         * respectiv max = capatul superior al acestuia */
        for (int i = problems[0].min_solved; i <= problems[0].max_solved; ++i) {
            dp[0][i] = 1;
        }

        for (int i = 1; i < N; ++i) {
            /* Initializam numarul de combinatii pentru intervalul curent cu 0
             * In variabila combinations_number vom retine suma combinatiilor
             * de la dp[i - 1][j - max] la dp[i - 1][j - min] */
            combinations_number = 0;

            /* Daca minimul de probleme rezolvate este 0, numarul de
             * combinatii pentru a obtine suma 0 va fi egala cu numarul de
             * combinatii de suma 0 al intervalului precendent */
            if (problems[i].min_solved == 0)
                combinations_number = dp[i - 1][0] % kMod;

            /* Adaugam in matricea dp numarul de combinatii pentru suma 0 */
            dp[i][0] = combinations_number;

            for (int j = 1; j <= M; ++j) {
                /* Pentru fiecare coloana a matricii, adaugam in numarul de
                 * combinatii suma combinatiilor dintre [j - max] -> [j - min]
                 * astfel: in loc sa calculam de fiecare data suma dintre
                 * acestea, retinem suma trecuta, din care scadem la pasul
                 * curent valoarea de pe [j - max - 1] si adaugam [j - min]
                 * (daca acestea se afla pe o pozitie cel putin egala cu 0) */
                if (j >= problems[i].max_solved + 1)
                    combinations_number -= dp[i - 1][j - problems[i].max_solved
                                                     - 1] % kMod;

                if (j >= problems[i].min_solved)
                    combinations_number += dp[i - 1][j - problems[i].min_solved]
                                           % kMod;

                /* Adaugam in elementul din matrice suma combinatiilor
                 * obtinute */
                dp[i][j] = combinations_number;
            }
        }

        /* Obtinem pe ultimul element al matricei numarul total de combinatii
         * in care se pot imparti bomboanele */
        return dp[N - 1][M] % kMod;
    }

    void print_output(int result) {
        ofstream fout("bomboane.out");
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
