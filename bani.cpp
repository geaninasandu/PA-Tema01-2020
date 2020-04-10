#include <bits/stdc++.h>

#define BILLS_NUMBER 5

using namespace std;

class Task {
 public:
    void solve() {
        read_input();
        print_output(count_combinations());
    }

 private:
    int N, instructions_set;
    int number_of_combinations;
    const int kMod = 1e9 + 7;

    void read_input() {
        ifstream fin("bani.in");
        fin >> instructions_set >> N;
        fin.close();
    }

    /**
     * Calculeaza rezultatul ridicarii la putere a numarului 2, folosind Divide
     * et Impera (lab 1)
     * @param exponent      exponentul lui 2
     * @return              rezultatul ridicarii la putere, modulo 1e9 + 7
     */
    long fast_pow_2(int exponent) {
        if (exponent == 0)
            return 1;

        long pow = fast_pow_2(exponent / 2);

        if (exponent % 2 == 0)
            return (1LL * pow * pow) % kMod;

        return (((1LL * pow * pow) % kMod * 2) % kMod);
    }

    /**
     * Returneaza numarul de combinatii de bancnote care pot fi obtinute, in
     * functie de setul de instructiuni dat
     * @return      numarul total de combinatii de bancnote
     */
    long count_combinations() {
        /* Daca setul de instructiuni este 1, deducem o relatie de recurenta
         * care intoarce numarul de combinatii */
        if (instructions_set == 1)
            return (BILLS_NUMBER * fast_pow_2(N - 1)) % kMod;

        /* Daca setul de instructiuni este 2, retinem numarul de bancnote de
         * fiecare tip de la fiecare pas */
        long current_bill_10_count, current_bill_50_count,
                current_bill_100_count, current_bill_200_count,
                current_bill_500_count;

        /* Initial, pentru N = 1, putem combina o bancnota din fiecare */
        long prev_bill_10_count = 1, prev_bill_50_count = 1,
                prev_bill_100_count = 1, prev_bill_200_count = 1,
                prev_bill_500_count = 1;

        /* Pentru fiecare pas, calculam cate combinatii de bancnote din fiecare
         * pot fi obtinute, in functie de bancnotele obtinute la pasul
         * anterior (eg. bancnotele de 10 lei se obtine pentru fiecare
         * bancnota de 50, 100 sau 500 de lei obtinute anterior, asadar
         * numarul bancnotelor de 10 lei de la pasul curent va fi egal cu
         * suma combinatiilor de bancnote precizate mai sus de la pasul
         * anterior) */
        for (int i = 1; i < N; ++i) {
            current_bill_10_count = (prev_bill_50_count + prev_bill_100_count +
                                     prev_bill_500_count) % kMod;
            current_bill_50_count = (prev_bill_10_count + prev_bill_200_count)
                                    % kMod;
            current_bill_100_count = (prev_bill_10_count + prev_bill_100_count +
                                      prev_bill_200_count) % kMod;
            current_bill_200_count = (prev_bill_50_count + prev_bill_500_count)
                                     % kMod;
            current_bill_500_count = prev_bill_200_count % kMod;

            /* Bancnotele de la pasul curent devin bancnotele de la pasul
             * anterior */
            prev_bill_10_count = current_bill_10_count;
            prev_bill_50_count = current_bill_50_count;
            prev_bill_100_count = current_bill_100_count;
            prev_bill_200_count = current_bill_200_count;
            prev_bill_500_count = current_bill_500_count;
        }

        /* La final, numarul total de combinatii care se pot obtine va fi
         * egal cu suma tuturor combinatiilor de bancnote obtinute mai sus */
        long total_combinations = (current_bill_10_count +
                                   current_bill_50_count +
                                   current_bill_100_count +
                                   current_bill_200_count +
                                   current_bill_500_count) % kMod;

        return total_combinations;
    }

    void print_output(int result) {
        ofstream fout("bani.out");
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
