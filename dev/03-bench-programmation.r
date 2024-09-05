source("dev/00-bench-all.r")

# N Fibonacci numbers calculation ----

run_benchmark(programmation_01_r, programmation_01_arma, programmation_01_blaze, programmation_01_eigen, 3500000L * 5L, "programmation-01")
gc()

# Creation of an NxN Hilbert matrix ----

run_benchmark(programmation_02_r, programmation_02_arma, programmation_02_blaze, programmation_02_eigen, 3000L * 5L, "programmation-02")
gc()

# Grand common divisors of N pairs ----

run_benchmark(programmation_03_r, programmation_03_arma, programmation_03_blaze, programmation_03_eigen, 400000L * 5L, "programmation-03")
gc()

# Creation of an NxN Toeplitz matrix ----

run_benchmark(programmation_04_r, programmation_04_arma, programmation_04_blaze, programmation_04_eigen, 500L * 5L, "programmation-04")
gc()

# Escoufier's method on an NxN matrix ----

run_benchmark(programmation_05_r, programmation_05_arma, programmation_05_blaze, programmation_05_eigen, 45L * 5L, "programmation-05")
gc()
